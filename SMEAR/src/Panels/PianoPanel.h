#include "Panel.h"
#include "Events/Events.h"

namespace SMEAR {
	class PianoPanel : public Panel {
	private:
		bool m_KeyStates[256];

	public:
		PianoPanel() = default;

		void OnMidiNoteEvent(const MidiNoteEvent& midiNoteEvent);

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		static bool IsBlackKey(uint8_t key);
	};
}