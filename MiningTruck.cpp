#include <cmath>

#include "MiningTruck.hpp"

namespace mining_truck {
    static unsigned id = 0;
}

MiningTruck::MiningTruck() {
    id_ = ++mining_truck::id;
    simulation_report_.shortest_mining_time_in_seconds =
        kMaximumLoadingTimeInSeconds;
    simulation_report_.longest_mining_time_in_seconds =
        kMinimumLoadingTimeInSeconds;
}

void MiningTruck::RunFrame(unsigned current_time) {
    Update(current_time);

    frame_count_++;
    simulation_report_.efficiency = (frame_count_ - time_waiting_to_unload_) /
        static_cast<double>(frame_count_);
}

void MiningTruck::Update(unsigned current_time) {
    if (mining_truck_state_ == MiningTruckState::UNKNOWN_ERROR) {
        // TODO: What should we do if truck is in error state
        return;
    }

    if (mining_truck_state_ == MiningTruckState::UNLOADING_HELIUM) {
        // Nothing to do logic is handle in unloading station
        return;
    }

    if (mining_truck_state_ == MiningTruckState::WAITING_TO_UNLOAD) {
        time_waiting_to_unload_++;
        return;
    }

    if (mining_truck_state_ == MiningTruckState::MINING_HELIUM) {
        if ((current_time - last_state_change_timestamp_) >=
            mining_time_duration_) {
            SetState(current_time, MiningTruckState::TRAVELLING_TO_UNLOADING_STATION);
        }
        return;
    }

    // Is it possible for future iterations to have different travel time? If so,
    // this will need to be refactor. However, it meets current requirements.
    if ((current_time - last_state_change_timestamp_) < kTravelTimeInSeconds) {
        return;
    }
    if (mining_truck_state_ == MiningTruckState::TRAVELLING_TO_MINING_SITE) {
        SetState(current_time, MiningTruckState::MINING_HELIUM);
        CalculateMiningTime();
    }
    else {
        // TODO: How to signal
        SetState(current_time, MiningTruckState::READY_TO_UNLOAD);
    }
}

void MiningTruck::CalculateMiningTime() {
    // Unnecessary error checking for initial simulation but good practice in case
    // min/max loading time field becomes configurable as well
    if (kMinimumLoadingTimeInSeconds >= kMaximumLoadingTimeInSeconds) {
        // TODO: Should we log error here?
        mining_time_duration_ = kMinimumLoadingTimeInSeconds;
        return;
    }

    double resolution =
        kMaximumLoadingTimeInSeconds - kMinimumLoadingTimeInSeconds;
    mining_time_duration_ = kMinimumLoadingTimeInSeconds +
        static_cast<unsigned>(std::floor(
            resolution * (static_cast<double>(::rand()) /
                static_cast<double>(RAND_MAX))));

    // Not part of original requirement but good for debugging
    if (mining_time_duration_ >
        simulation_report_.longest_mining_time_in_seconds) {
        simulation_report_.longest_mining_time_in_seconds = mining_time_duration_;
    }
    if (mining_time_duration_ <
        simulation_report_.shortest_mining_time_in_seconds) {
        simulation_report_.shortest_mining_time_in_seconds = mining_time_duration_;
    }
    simulation_report_.number_of_mine_site_visits++;

    simulation_report_.total_mining_time_in_seconds += mining_time_duration_;
    simulation_report_.average_mining_time_in_seconds =
        simulation_report_.total_mining_time_in_seconds /
        simulation_report_.number_of_mine_site_visits;
}

void MiningTruck::SetState(unsigned current_time, MiningTruckState state) {
    // TODO: Add error checking to see if state can transition
    mining_truck_state_ = state;
    last_state_change_timestamp_ = current_time;
}