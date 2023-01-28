#include "Panel.h"
#include "Events/Events.h"

namespace SMEAR {
	class PianoPanel : public Panel {
	private:
		uint8_t m_KeyStates[256];
		int m_StartingNote = 36;
		int m_NoteSpan = 61;

		int m_KeyWidth = 20;
		int m_WhiteKeyHeight = 120;
		int m_BlackKeyHeight = 80;

		uint32_t m_KeyHighlightColor = 0xFF0000FF;

	public:
		PianoPanel() = default;

		void OnMidiNoteEvent(const MidiNoteEvent& midiNoteEvent);

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		static bool IsBlackKey(uint8_t key);
	};
}