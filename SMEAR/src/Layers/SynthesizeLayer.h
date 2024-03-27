#pragma once

#include <string>

#include "Newt.h"
#include "Newt/Core/Timer.h"

struct MidiNoteEvent;
struct tsf;

namespace SMEAR {
	class SynthesizeLayer : public Newt::Layer {
	private:
		tsf* m_tsfHandle = nullptr;
		std::string m_SoundfontFilepath = "assets/soundfonts/wii_grand_piano.sf2";
		unsigned int m_SampleRate = 44100;
		unsigned int m_BufferSize = 512;
		short m_AudioBuffer[512];
		Newt::Timer m_BufferTimer;

	public:
		SynthesizeLayer();
		virtual ~SynthesizeLayer() = default;

		void OnMidiNoteEvent(const MidiNoteEvent& midiNoteEvent);

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnAwake() override;
		virtual void OnUpdate(Newt::TimeStep ts) override;

		virtual void OnImGuiRender() override;
	};
}
