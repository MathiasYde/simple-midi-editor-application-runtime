#include <Newt.h>

#include "CoreLayer.h"
#include "EditorLayer.h"
#include "SmearApplication.h"

namespace SMEAR {
	SmearApplication* SmearApplication::s_Instance = nullptr;

	SmearApplication::SmearApplication(Newt::ApplicationCommandLineArgs args)
		: Newt::Application(Newt::ApplicationSpecification{"SMEAR", "", args}) {
		s_Instance = this;

		PushLayer(new SMEAR::CoreLayer());
		PushLayer(new SMEAR::EditorLayer());
	}

	SmearApplication::~SmearApplication() {}

	entt::dispatcher* SmearApplication::GetEventDispatcher() {
		return &s_Instance->m_EventDispatcher;
	}
}
