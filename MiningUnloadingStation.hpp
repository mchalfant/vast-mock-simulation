#pragma once

#pragma once
#pragma once

#include "common.h"
#include "MiningTruck.hpp"
#include <queue>

class MiningUnloadingStation {
   public:
      void UnloadMiningTruck(unsigned current_time);
      void QueueMiningTruck(unsigned current_time, MiningTruck* mining_truck);
      unsigned GetCurrentWaitTime(unsigned current_time);
      void RunFrame(unsigned current_time);

    private:
        unsigned GetTimeSinceLastStateChange(unsigned current_time, MiningTruck* current_truck);

       //Originally wanted to make a waiting_mining_trucks_ as an queue but we'll need random memory access to get total wait time
       std::vector<MiningTruck*> waiting_mining_trucks_;
       MiningTruck* selected_mining_truck_ = nullptr;

       // For meeting the MVP it's ok to have const in Unloading class.
       // However, It's currently unknown in future iterations of this simulation will be 
       // different trucks with different payload sizes that could affect unloading time.
       // In future iterations it may be better to have a payload weight counter and 
       // pass the values into a Unloading Station Class so it can determine unloading time.
       static const unsigned kUnloadingTimeInSeconds = 5 * timing::kSecondsPerMinute;
};
