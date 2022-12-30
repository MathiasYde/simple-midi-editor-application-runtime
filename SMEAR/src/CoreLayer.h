#pragma once

#include "Newt.h"
#include "libremidi/libremidi.hpp"

namespace SMEAR {
	class CoreLayer : public Newt::Layer {
	private:
		libremidi::midi_in m_MidiHandle;

	public:
		CoreLayer();
		virtual ~CoreLayer() = default;

		virtual void OnAttach() override;
		virtual void OnUpdate(Newt::TimeStep ts) override;
	};
}