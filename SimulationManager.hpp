#pragma once

#include "MiningTruck.hpp"
#include "MiningUnloadingStation.hpp"

#include "common.h"
#include <iostream>
#include <vector>

//Arbituary default values
struct SimulationSettings {
   unsigned int number_of_mining_trucks = 300;
   unsigned int number_of_mining_unload_stations = 3;
};

class SimulationManager {
    public:
       SimulationManager() = default;
       SimulationManager(SimulationSettings simulation_settings){
          SetSimulationSettings(simulation_settings);
       }

       //TODO: would it every be possible for settings to be updated during a simulation?
       void SetSimulationSettings(SimulationSettings simulation_settings) {
          simulation_settings_ = simulation_settings; 

          mining_trucks_.resize(simulation_settings_.number_of_mining_trucks);
          mining_unloading_stations_.resize(simulation_settings_.number_of_mining_unload_stations);
       }

       SimulationStatus RunSimulation();
       void PrintAnalysisReports(std::ostream& output_file = std::cout);

    private:
       bool RunFrame(unsigned current_time);
       void LoadTruckIntoUnloadingStation(unsigned current_time, MiningTruck* mining_truck);

       SimulationSettings simulation_settings_; 
       std::vector<MiningTruck> mining_trucks_;
       std::vector<MiningUnloadingStation> mining_unloading_stations_;
       static const unsigned kAllocatedSimulationTime = 72 * timing::kSecondsPerHour; // Will this ever be configurable in future iterations?
};