#include "PianoPanel.h"

#include <Newt.h>
#include <imgui/imgui.h>

#include "SmearApplication.h"
#include "Events/Events.h"
#include "CoreLayer.h"
#include "Constants.h"

namespace SMEAR {
	bool PianoPanel::IsBlackKey(uint8_t key) {
		int note = key % 12;
		return note == 1 || note == 3 || note == 6 || note == 8 || note == 10;
	}

	// https://github.com/shric/midi/blob/master/src/Piano.cpp
	void PianoPanel::OnImGuiRender() {
		ImGui::SetNextWindowSizeConstraints(ImVec2(300.0f, 160.0f), ImVec2(m_KeyWidth * m_NoteSpan, 160.0f));
		ImGui::Begin("Piano");
		ImVec2 cursorPosition = ImGui::GetCursorScreenPos();
		ImDrawList* drawList = ImGui::GetWindowDrawList();

		{
			// render white keys
			int currentKey = m_StartingNote;
			for (int i = 0; i < m_NoteSpan; i++) {
				ImU32 color = IM_COL32_WHITE;
				if (m_KeyStates[currentKey] == true) {
					color = m_KeyHighlightColor;
				}

				drawList->AddRectFilled(
					ImVec2(cursorPosition.x + i * m_KeyWidth, cursorPosition.y),
					ImVec2(cursorPosition.x + i * m_KeyWidth + m_KeyWidth, cursorPosition.y + m_WhiteKeyHeight),
					color, 0, ImDrawCornerFlags_All);
				drawList->AddRect(
					ImVec2(cursorPosition.x + i * m_KeyWidth, cursorPosition.y),
					ImVec2(cursorPosition.x + i * m_KeyWidth + m_KeyWidth, cursorPosition.y + m_WhiteKeyHeight),
					IM_COL32_BLACK, 0, ImDrawCornerFlags_All);

				do {
					currentKey += 1;
				} while (IsBlackKey(currentKey));
			}
		}

		{
			// render black keys
			int currentKey = m_StartingNote + 1;
			for (int i = 0; i < m_NoteSpan; i++) {
				if (!IsBlackKey(currentKey)) {
					currentKey += 1;
					continue;
				}

				ImU32 color = IM_COL32_BLACK;
				if (m_KeyStates[currentKey] == true) {
					color = m_KeyHighlightColor;
				}

				drawList->AddRectFilled(
					ImVec2(cursorPosition.x + i * m_KeyWidth + m_KeyWidth * 3 / 4, cursorPosition.y),
					ImVec2(cursorPosition.x + i * m_KeyWidth + m_KeyWidth * 5 / 4, cursorPosition.y + m_BlackKeyHeight),
					color, 0, ImDrawCornerFlags_All);
				drawList->AddRect(
					ImVec2(cursorPosition.x + i * m_KeyWidth + m_KeyWidth * 3 / 4, cursorPosition.y),
					ImVec2(cursorPosition.x + i * m_KeyWidth + m_KeyWidth * 5 / 4, cursorPosition.y + m_BlackKeyHeight),
					IM_COL32_BLACK, 0, ImDrawCornerFlags_All);

				currentKey += 2;
			}
		}

		ImGui::End();
	}

	void PianoPanel::OnMidiNoteEvent(const MidiNoteEvent& midiNoteEvent) {
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