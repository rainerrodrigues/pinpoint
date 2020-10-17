#include "Experiment.h"
#include "Sampler.h"
#include "Registry.h"

int main(int argc, char *argv[])
{
	settings::settings.readProgArgs(argc, argv);
	Registry::setup();

	settings::settings.validate();

	try	{
		Experiment experiment;

		experiment.run();
		experiment.printResult();
	} catch (const std::exception & e) {
		std::cerr << "[ERROR] " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
