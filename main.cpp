#include "MiningTruck.hpp"
#include "MiningUnloadingStation.hpp"
#include "SimulationManager.hpp"

// TODO: How should we be configurable? Through command line, file, and/or
// ethernet There's a few ways to approach running multiple iterations of the
// simulation.
// 1. Have the main function one function and run a separate test setting the
// simulation values as command line arguments

int main(int argc, char** argv) {
	SimulationSettings simulation_settings;
	// TODO: Get settings here. Ideally, would get settings from CLI
	// but there isn't a cross platform cli parser in c++ standard library.

	SimulationManager simulation_manager(simulation_settings);
	auto simulation_status = simulation_manager.RunSimulation();
	// TODO: Check status here

	// TODO: Command line option to get custom ostream object to write report to
	// output file. Default is std::cout
	simulation_manager.PrintAnalysisReports();

	return 0;
}