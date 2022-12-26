#pragma once

#include "Newt.h"
using namespace Newt;

#include "libremidi/libremidi.hpp"

namespace SMEAR {
	class CoreLayer : public Layer {
	private:
		libremidi::midi_in m_MidiHandle;

	public:
		CoreLayer();
		virtual ~CoreLayer() = default;

		virtual void OnAttach() override;
		virtual void OnUpdate(TimeStep ts) override;
	};
}