#include "PianoPanel.h"

#include <Newt.h>
#include <imgui/imgui.h>

#include "SmearApplication.h"
#include "Events/Events.h"
#include "CoreLayer.h"
#include "Constants.h"

namespace SMEAR {
	// https://github.com/shric/midi/blob/master/src/Piano.cpp
	bool PianoPanel::IsBlackKey(uint8_t key) {
		return (!((key - 1) % 7 == 0 || (key - 1) % 7 == 3) && key != 51);
	}

	// https://github.com/shric/midi/blob/master/src/Piano.cpp
	void PianoPanel::OnImGuiRender() {
		int keyWidth = 20;

		ImGui::Begin("Piano");
		ImVec2 cursorPosition = ImGui::GetCursorScreenPos();
		ImDrawList* drawList = ImGui::GetWindowDrawList();

		for (int i = 0; i < 61; i++) {
			// TODO(mathias) implement a better system to retrieve color information
			ImU32 color = PianoPanel::IsBlackKey(i) ? IM_COL32(0, 0, 0, 255) : IM_COL32(255, 255, 255, 255);
			
			if (m_KeyStates[i] == true)
				// color = IM_COL32(255, 0, 0, 255) doesn't work for some reason
				color = 0xFF0000FF;

			drawList->AddRectFilled(
				ImVec2(cursorPosition.x + i * keyWidth + keyWidth * 3 / 4, cursorPosition.y),
				ImVec2(cursorPosition.x + i * keyWidth + keyWidth * 5 / 4 + 1, cursorPosition.y + 80),
				color, 0, ImDrawCornerFlags_All);
		}

		ImGui::End();
	}

	void PianoPanel::OnMidiNoteEvent(const MidiNoteEvent& midiNoteEvent) {
		NT_INFO("MIDI note event received from PianoPianel");

		switch (midiNoteEvent.command) {
		case MIDI_NOTE_ON:
			m_KeyStates[midiNoteEvent.pitch] = true;
			break;
		case MIDI_NOTE_OFF:
			m_KeyStates[midiNoteEvent.pitch] = false;
			break;
		default:
			break;
		}
	}

	void PianoPanel::OnAttach() {
		entt::dispatcher* dispatcher = SmearApplication::GetEventDispatcher();
		dispatcher->sink<MidiNoteEvent>().connect<&PianoPanel::OnMidiNoteEvent>(this);
	}

	void PianoPanel::OnDetach() {
		// disconnect from all events
		entt::dispatcher* dispatcher = SmearApplication::GetEventDispatcher();
		dispatcher->sink<MidiNoteEvent>().disconnect(this);
	}
}