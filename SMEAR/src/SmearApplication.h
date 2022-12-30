#pragma once

#include "Newt.h"

namespace SMEAR {
	class SmearApplication : public Newt::Application {
	private:
		static SmearApplication* s_Instance;

		entt::dispatcher m_EventDispatcher{};

	public:
		SmearApplication(Newt::ApplicationCommandLineArgs args);
		~SmearApplication();

		static entt::dispatcher* GetEventDispatcher();
	};
}