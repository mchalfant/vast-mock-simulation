#include "SimulationManager.hpp"
#include <thread>
#include <chrono>

void SimulationManager::LoadTruckIntoUnloadingStation(unsigned current_time, MiningTruck* mining_truck) {
    //TODO: Implement cache to store time so we don't need to iteration over for loop for each truck
    unsigned selected_index = 0;
    unsigned current_index = 0;
    unsigned shortest_time = UINT32_MAX;

    for (auto& mining_unloading_station : mining_unloading_stations_) {
        unsigned current_wait_time = mining_unloading_station.GetCurrentWaitTime(current_time);
        if (current_wait_time < shortest_time) {
            shortest_time = current_wait_time;
            selected_index = current_index;
        }
        current_index++;
    }

    mining_unloading_stations_[selected_index].QueueMiningTruck(current_time, mining_truck);
}

bool SimulationManager::RunFrame(unsigned current_time) {
    //Step 2: Update truck status
    for(auto& mining_truck : mining_trucks_){
       mining_truck.RunFrame(current_time);
       if (mining_truck.GetState() == MiningTruckState::READY_TO_UNLOAD) {
           LoadTruckIntoUnloadingStation(current_time, &mining_truck);
       }
    }

    //Step 2: Check all unloading stations to see if trucks can be freed
    for (auto& mining_unloading_station : mining_unloading_stations_) {
        mining_unloading_station.RunFrame(current_time);
    }

    return true;
}

SimulationStatus SimulationManager::RunSimulation(){
    if(mining_trucks_.empty()) {
        return SimulationStatus::SIMULATION_INVALID_SETTINGS;
    }
    if(mining_unloading_stations_.empty()){
        return SimulationStatus::SIMULATION_INVALID_SETTINGS;
    }

    unsigned current_simulation_time_in_seconds = 0;
    while(current_simulation_time_in_seconds < kAllocatedSimulationTime){
        if(!RunFrame(++current_simulation_time_in_seconds)){
            return SimulationStatus::SIMULATION_ERROR;
        }
        //TODO: Add artifical wait here
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }

    return SimulationStatus::SIMULATION_SUCCESS;
}

void SimulationManager::PrintAnalysisReports(std::ostream& os){
   for(const auto& truck : mining_trucks_){
      os << std::format("Truck {} Analysis Report", truck.GetTruckId()) << std::endl;
      os << truck.GetSimulationReport() << std::endl << std::endl;
   }
}