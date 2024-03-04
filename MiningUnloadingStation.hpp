#pragma once

#pragma once
#pragma once

#include <queue>

#include "MiningTruck.hpp"
#include "common.h"

struct UnloadingStationSimulationReport {
    double efficiency = 0;
    unsigned total_time_unloading_helium = 0;
    unsigned helium_payloads_unloaded = 0;

    friend std::ostream& operator<<(
        std::ostream& os, const UnloadingStationSimulationReport& report) {
        return os << std::format(
            "Work Efficiency: {:.3f}%\n"
            "Total Unloading Helium Time: {} seconds\n"
            "Helium Payloads Unloaded: {}",
            report.efficiency * 100.0,
            report.total_time_unloading_helium,
            report.helium_payloads_unloaded)
            << std::endl;
    }
};

class MiningUnloadingStation {
public:
    MiningUnloadingStation();
    void UnloadMiningTruck(unsigned current_time);
    void QueueMiningTruck(unsigned current_time, MiningTruck* mining_truck);
    unsigned GetCurrentWaitTime(unsigned current_time);
    void RunFrame(unsigned current_time);
    unsigned long GetStationId() const { return id_; }
    UnloadingStationSimulationReport GetSimulationReport() const {
        return simulation_report_;
    }

private:
    void Update(unsigned current_time);
    unsigned GetTimeSinceLastStateChange(unsigned current_time,
        MiningTruck* current_truck);
    unsigned long id_ = 0;
    UnloadingStationSimulationReport simulation_report_;

    // Originally wanted to make a waiting_mining_trucks_ as an queue but we'll
    // need random memory access to get total wait time
    std::vector<MiningTruck*> waiting_mining_trucks_;
    MiningTruck* selected_mining_truck_ = nullptr;
    unsigned frame_count_ = 0;
    unsigned total_time_inactive_ = 0;

    // For meeting the MVP it's ok to have const in Unloading class.
    // However, It's currently unknown in future iterations of this simulation
    // will be different trucks with different payload sizes that could affect
    // unloading time. In future iterations it may be better to have a payload
    // weight counter and pass the values into a Unloading Station Class so it can
    // determine unloading time.
    static const unsigned kUnloadingTimeInSeconds = 5 * timing::kSecondsPerMinute;
};
