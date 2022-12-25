#include <Newt.h>
#include <Newt/Core/EntryPoint.h>

namespace Newt {

	class SMEAR : public Application
	{
	public:
		SMEAR(ApplicationCommandLineArgs args)
			: Application(ApplicationSpecification{"SMEAR", "", args})
		{
		}

		~SMEAR()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new SMEAR(args);
	}

}
