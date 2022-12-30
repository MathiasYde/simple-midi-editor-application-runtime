#include <Newt.h>

#include "Layers/CoreLayer.h"
#include "Layers/EditorLayer.h"
#include "Layers/SynthesizeLayer.h"
#include "SmearApplication.h"

namespace SMEAR {
	SmearApplication* SmearApplication::s_Instance = nullptr;

	SmearApplication::SmearApplication(Newt::ApplicationCommandLineArgs args)
		: Newt::Application(Newt::ApplicationSpecification{"SMEAR", "", args}) {
		s_Instance = this;

		// TODO(mathias) read the default configuration file and load modules accordingly

		PushLayer(new SMEAR::CoreLayer());
		PushLayer(new SMEAR::EditorLayer());
		PushLayer(new SMEAR::SynthesizeLayer());
	}

	SmearApplication::~SmearApplication() {}

	entt::dispatcher* SmearApplication::GetEventDispatcher() {
		return &s_Instance->m_EventDispatcher;
	}
}
