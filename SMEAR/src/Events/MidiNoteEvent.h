#pragma once
#include <cstdint>

struct MidiNoteEvent {
	uint8_t command;
	uint8_t channel;
	uint8_t pitch;
	uint8_t velocity;
};