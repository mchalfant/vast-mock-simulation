#pragma once

enum class SimulationStatus {
    SIMULATION_SUCCESS = 0,
    SIMULATION_CANCELLED = 1,
    SIMULATION_INVALID_SETTINGS = 2,
    SIMULATION_ERROR = 3,
    //TODO: Other status codes?
};

namespace timing {
static const unsigned kSecondsPerMinute = 60;
static const unsigned kMinutesPerHour = 60;
static const unsigned kSecondsPerHour = kSecondsPerMinute * kMinutesPerHour;
}