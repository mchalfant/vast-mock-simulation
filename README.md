# Vast Space Mock Simulation

## Objective
This is a simulation for a lunar Helium-3 space mining operation. It manages and track the 
efficiency of mining trucks and unload stations over a continuous 72-hour operation faster than real time.

## How It Works
The simulation is broken down into three main modules. The Mining Truck, Unloading Station, and Simulation Manager module.

### Simulation Manager
The simulation mananger run through a loop simuation a second of real time into each of the mining trucks and unloading stations
within the simulation. At the end of the simulation the simulation manager can output the result to the terminal or an existing file\
for post analysis.

### Mining Truck
The Mining Truck is responsible for keeping track of what the state the truck is in the simulation. The truck updates it's own
simulation report every second of the simulation. It's efficiency is measured by the following:

`(total time in simulation - time waiting for unloading station) / total time in simulation`

### Mining Unloading Station
The Mining Unloading Station is responsible for how long a truck has to wait and where trucks are queued at. The unloading 
station updates it's own simulation report every second of the simulation. It's efficiency is measured by the following:

`(total time in simulation - time waiting for payloads) / total time in simulation`

## Configuration
Ideally a cli argument would point to a settings file that has all of the necessary file for each test scenario requested.
I would use either getopt or getopt_long for argument parsing if this was meant over for POSIX systems. If this simulation
needs to be cross platform I would use [CLI11](https://github.com/CLIUtils/CLI11).

## Testing
A large amount of testing was done by adding information to the simulation reports. If I had more time I would 
create unit tests using the GoogleTest framework.
