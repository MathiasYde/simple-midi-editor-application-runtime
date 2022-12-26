#include <Newt.h>
#include <Newt/Core/EntryPoint.h>

#include "CoreLayer.h"
#include "EditorLayer.h"

namespace Newt {

	class app : public Application
	{
	public:
		app(ApplicationCommandLineArgs args)
			: Application(ApplicationSpecification{"SMEAR", "", args})
		{
			PushLayer(new SMEAR::CoreLayer());
			PushLayer(new SMEAR::EditorLayer());
		}

		~app()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new app(args);
	}
}
