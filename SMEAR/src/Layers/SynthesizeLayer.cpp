#include "SynthesizeLayer.h"

#define TSF_IMPLEMENTATION
#include "tsf.h"

#include "SmearApplication.h"
#include "Events/MidiNoteEvent.h"
#include "Constants.h"

namespace SMEAR {
	SynthesizeLayer::SynthesizeLayer() : Newt::Layer("SynthesizeLayer") {}

	void SynthesizeLayer::OnMidiNoteEvent(const MidiNoteEvent& midiNoteEvent) {
		switch (midiNoteEvent.command) {
		case MIDI_NOTE_ON:
			tsf_note_on(m_tsfHandle, 0, midiNoteEvent.pitch, 1.0f);
			break;
		case MIDI_NOTE_OFF:
			tsf_note_off(m_tsfHandle, 0, midiNoteEvent.pitch);
			break;
		default:
			break;
		}
	}

	void SynthesizeLayer::OnAttach() {
		m_tsfHandle = tsf_load_filename(m_SoundfontFilepath.c_str());
		if (m_tsfHandle == nullptr) {
			NT_ERROR("m_tsfHandle is not initialized");
			return;
		}

		tsf_set_output(m_tsfHandle, TSF_MONO, m_SampleRate, 0);
		m_BufferTimer = Newt::Timer((float)m_BufferSize / m_SampleRate);

		NT_INFO("Initialized TinySoundFont with samplerate of {0} and buffer size of {1}, resulting in {2} seconds of delay", m_SampleRate, m_BufferSize, (float)m_BufferSize / m_SampleRate);

		// register midi event callback
		entt::dispatcher* dispatcher = SmearApplication::GetEventDispatcher();
		dispatcher->sink<MidiNoteEvent>().connect<&SynthesizeLayer::OnMidiNoteEvent>(this);
	}

	void SynthesizeLayer::OnDetach() {
		// disconnect from all events
		entt::dispatcher* dispatcher = SmearApplication::GetEventDispatcher();
		dispatcher->sink<MidiNoteEvent>().disconnect(this);
	}

	void SynthesizeLayer::OnAwake() {}

	void SynthesizeLayer::OnUpdate(Newt::TimeStep ts) {
		// re-render the audio buffer every BufferSize/SampleRate
		if (m_BufferTimer.Update(ts)) {
			m_BufferTimer.Reset();

			tsf_render_short(m_tsfHandle, m_AudioBuffer, m_BufferSize, 0);
		}
	}

	void SynthesizeLayer::OnImGuiRender() {}
}
