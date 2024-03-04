#pragma once

#include <format>
#include <iostream>

#include "common.h"

enum class MiningTruckState {
    TRAVELLING_TO_MINING_SITE = 0,
    MINING_HELIUM = 1,
    TRAVELLING_TO_UNLOADING_STATION = 2,
    READY_TO_UNLOAD = 3,
    WAITING_TO_UNLOAD = 4,
    UNLOADING_HELIUM = 5,
    UNKNOWN_ERROR = 7
};

struct MiningTruckSimulationReport {
    double efficiency = 0;
    unsigned shortest_mining_time_in_seconds = 0;
    unsigned longest_mining_time_in_seconds = 0;
    unsigned average_mining_time_in_seconds = 0;
    unsigned total_mining_time_in_seconds = 0;
    unsigned number_of_mine_site_visits = 0;

    friend std::ostream& operator<<(std::ostream& os,
        const MiningTruckSimulationReport& report) {
        return os
            << std::format(
                "Work Efficiency: {:.3f}%\nShortest Mining Time: {} seconds\n"
                "Longest Mining Time: {} seconds\nAverage Mining Time: {} "
                "seconds\n"
                "Total Mining Time: {} seconds\nMine Site Visits: {}",
                report.efficiency * 100.0,
                report.shortest_mining_time_in_seconds,
                report.longest_mining_time_in_seconds,
                report.average_mining_time_in_seconds,
                report.total_mining_time_in_seconds,
                report.number_of_mine_site_visits)
            << std::endl;
    }
};

// TODO: In future iterations of this simulation would we need different mining
// trucks? We would add a virtual destructor if we want to have specialized
// trucks inheriting from this class.

class MiningTruck {
public:
    MiningTruck();

    MiningTruckState GetState() const { return mining_truck_state_; }

    void SetState(unsigned current_time, MiningTruckState state);
    unsigned GetLastStateChangeTimestamp() const {
        return last_state_change_timestamp_;
    }

    MiningTruckSimulationReport GetSimulationReport() const {
        return simulation_report_;
    }
    unsigned long GetTruckId() const { return id_; }

    void RunFrame(unsigned current_time);

private:
    void Update(unsigned current_time);
    void CalculateMiningTime();

    unsigned long id_ = 0;  // Mostly for debugging

    // TODO: If we have different types of truck will they have different loading
    // times?
    static const unsigned kMinimumLoadingTimeInSeconds =
        1 * timing::kSecondsPerHour;
    static const unsigned kMaximumLoadingTimeInSeconds =
        5 * timing::kSecondsPerHour;
    static const unsigned kTravelTimeInSeconds = 30 * timing::kSecondsPerMinute;

    MiningTruckState mining_truck_state_ = MiningTruckState::MINING_HELIUM;
    unsigned last_state_change_timestamp_ = 0;
    unsigned time_waiting_to_unload_ = 0;
    unsigned mining_time_duration_ = 0;
    unsigned frame_count_ = 0;
    unsigned total_time_mining_ = 0;

    MiningTruckSimulationReport simulation_report_;
};