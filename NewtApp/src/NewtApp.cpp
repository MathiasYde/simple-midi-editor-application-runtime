#include <Newt.h>
#include <Newt/Core/EntryPoint.h>

namespace Newt {

	class NewtApp : public Application
	{
	public:
		NewtApp(ApplicationCommandLineArgs args)
			: Application("Newt App", args)
		{
		}

		~NewtApp()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new NewtApp(args);
	}

}
