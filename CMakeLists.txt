# Top Level CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(VAST_SIMULATION)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
   MiningTruck.cpp
   MiningUnloadingStation.cpp
   SimulationManager.cpp
)

add_executable(
   mining_simulation
   main.cpp
   ${SOURCES}
)
