#include "PianoPanel.h"

#include <Newt.h>
#include <imgui/imgui.h>

#include "SmearApplication.h"
#include "Events/Events.h"
#include "Layers/CoreLayer.h"
#include "Constants.h"

#include <algorithm>

#define IMGUI_INPUTINT(label, field, min, max) if (ImGui::InputInt(label, &field, 1, 1)) { field = std::clamp(field, min, max); }

namespace SMEAR {
	bool PianoPanel::IsBlackKey(uint8_t key) {
		int note = key % 12;
		return note == 1 || note == 3 || note == 6 || note == 8 || note == 10;
	}

	void PianoPanel::DrawConfigMenu() {
		// TODO: ImGui::Columns doesn't seem to respect these constraints
		ImGui::SetNextWindowSizeConstraints(
			ImVec2(100.0f, -1),
			ImVec2(240.0f, -1)
		);

		ImGui::BeginChild("Piano Panel Config");

		if (ImGui::Button("Reset to defaults")) {
			m_MidiChannel = 0;
			m_NoteSpan = 61;
			m_StartingNote = 36;
		}

		IMGUI_INPUTINT("Channel", m_MidiChannel, 0, 15);
		IMGUI_INPUTINT("Span", m_NoteSpan, 0, 255);
		IMGUI_INPUTINT("Starting note", m_StartingNote, 0, 255);

		ImGui::EndChild();
	}

	// https://github.com/shric/midi/blob/master/src/Piano.cpp
	void PianoPanel::OnImGuiRender() {
		// TODO: this window still need a bit more of vertical padding
		float frameHeight = ImGui::GetFrameHeightWithSpacing();

		ImGui::SetNextWindowSizeConstraints(
			ImVec2(300.0f, m_WhiteKeyHeight + frameHeight),
			ImVec2(m_KeyWidth * m_NoteSpan, m_WhiteKeyHeight + frameHeight)
		);

		ImGui::Begin("Piano");
		ImGui::Columns(2);

		DrawConfigMenu();

		ImGui::NextColumn();

		ImVec2 cursorPosition = ImGui::GetCursorScreenPos();
		ImDrawList* drawList = ImGui::GetWindowDrawList();

		{
			// render white keys
			int currentKey = m_StartingNote;
			for (int i = 0; i < m_NoteSpan; i++) {
				ImU32 color = IM_COL32_WHITE;
				if (m_KeyStates[currentKey] > 0) {
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
				if (m_KeyStates[currentKey] > 0) {
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
		if (midiNoteEvent.channel != m_MidiChannel) { return; }

		switch (midiNoteEvent.command) {
		case MIDI_NOTE_ON:
			m_KeyStates[midiNoteEvent.pitch] = midiNoteEvent.velocity;
			break;
		case MIDI_NOTE_OFF:
			m_KeyStates[midiNoteEvent.pitch] = 0;
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