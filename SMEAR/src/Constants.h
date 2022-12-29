#pragma once

// https://ccrma.stanford.edu/~craig/articles/linuxmidi/misc/essenmidi.html

// System messages (0xF0 to 0xFF)
#define MIDI_START 0xFA
#define MIDI_CONTINUE 0xFB
#define MIDI_STOP 0xFC
#define MIDI_SYSTEM_RESET 0xFF
#define MIDI_SONG_SELECT 0xF3
#define MIDI_ACTIVE_SENSING 0xFE
#define MIDI_SONG_POSITION_POINTER 0xF2

// Channel messages (0x80 to 0xEF)
#define MIDI_NOTE_OFF 0x80
#define MIDI_NOTE_ON 0x90
#define MIDI_AFTERTOUCH 0xA0
#define MIDI_CONTINOUS_CONTROLLER 0xB0
#define MIDI_PATCH_CHANGE 0xC0
#define MIDI_CHANNEL_PRESSURE 0xD0
#define MIDI_PITCH_BEND 0xE0