#include "Newt.h"
#include "Newt/Core/EntryPoint.h"

#include "SmearApplication.h"

namespace Newt {
	Application* CreateApplication(ApplicationCommandLineArgs args) {
		return new SMEAR::SmearApplication(args);
	}
}