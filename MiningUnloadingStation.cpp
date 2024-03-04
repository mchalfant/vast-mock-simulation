#include "MiningUnloadingStation.hpp"

void MiningUnloadingStation::RunFrame(unsigned current_time){
   if(!selected_mining_truck_){
       return;
   }

   unsigned last_state_change_timestamp = selected_mining_truck_->GetLastStateChangeTimestamp();
   if((current_time - last_state_change_timestamp) >= kUnloadingTimeInSeconds){
      UnloadMiningTruck(current_time);
   }
}

unsigned MiningUnloadingStation::GetTimeSinceLastStateChange(unsigned current_time, MiningTruck* current_truck) {
    unsigned time_since_last_state_change = current_time - current_truck->GetLastStateChangeTimestamp();
    if (time_since_last_state_change >= kUnloadingTimeInSeconds) {
        return 0;
    }
    return kUnloadingTimeInSeconds - time_since_last_state_change;
}

unsigned MiningUnloadingStation::GetCurrentWaitTime(unsigned current_time) {
    unsigned wait_time = 0;
    if (waiting_mining_trucks_.empty() && !selected_mining_truck_) {
        return wait_time;
    }

    for (const auto& waiting_mining_truck : waiting_mining_trucks_) {
        wait_time += kUnloadingTimeInSeconds;
    }

    return wait_time + GetTimeSinceLastStateChange(current_time, selected_mining_truck_);
}

void MiningUnloadingStation::UnloadMiningTruck(unsigned current_time){
   if(!selected_mining_truck_){
       return;
   }

   selected_mining_truck_->SetState(current_time, MiningTruckState::TRAVELLING_TO_MINING_SITE);
   if(waiting_mining_trucks_.empty()){
      selected_mining_truck_ = NULL;
      return;
   }

   selected_mining_truck_ = waiting_mining_trucks_.front();
   selected_mining_truck_->SetState(current_time, MiningTruckState::UNLOADING_HELIUM);

   waiting_mining_trucks_.erase(waiting_mining_trucks_.begin());
   for (auto& waiting_mining_truck : waiting_mining_trucks_) {
       //Updating state with it's current state but an updated timestamp to prevent 
       //trucks pre maturely exiting the queue
       waiting_mining_truck->SetState(current_time, MiningTruckState::WAITING_TO_UNLOAD);
   }
}

void MiningUnloadingStation::QueueMiningTruck(unsigned current_time, MiningTruck* mining_truck){
   if(!selected_mining_truck_){
      mining_truck->SetState(current_time, MiningTruckState::UNLOADING_HELIUM);
      selected_mining_truck_ = mining_truck;
   } else {
      mining_truck->SetState(current_time, MiningTruckState::WAITING_TO_UNLOAD);
      waiting_mining_trucks_.push_back(mining_truck);
   }
}