#include "CoreLayer.h"
#include <libremidi/libremidi.hpp>

#include "spdlog/spdlog.h"
#include <spdlog/fmt/bin_to_hex.h>

namespace SMEAR {
	CoreLayer::CoreLayer() : Layer("CoreLayer") {}

	void CoreLayer::OnAttach() {

		NT_INFO("MIDI - {0} available ports", m_MidiHandle.get_port_count());
		for (int i = 0; i < m_MidiHandle.get_port_count(); i++) {
			std::string name = m_MidiHandle.get_port_name(i);
			NT_INFO("[{0}] {1}", i, name);
		}

		m_MidiHandle.open_port(0);

		m_MidiHandle.set_error_callback(
			[](libremidi::midi_error code, std::string_view info) {
				NT_ERROR("LIBREMIDI ({0}): {1}", code, info);
			});
	}

	void CoreLayer::OnUpdate(TimeStep ts) {
		libremidi::message message;
		if (m_MidiHandle.get_message(message)) {

			uint8_t command = message[0] >> 4;
			uint8_t channel = message[0] & 0x0F;
			uint8_t pitch = message[1] & 0x7F;
			uint8_t velocity = message[2] & 0x7F;

			NT_INFO("Midi event - Command {0}, Channel {1}, Pitch {2}, Velocity {3}", std::to_string(command), std::to_string(channel), std::to_string(pitch), std::to_string(velocity));
		}
	}
}