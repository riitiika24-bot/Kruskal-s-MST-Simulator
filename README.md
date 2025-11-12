# Kruskal's MST Simulator

## Project Title
Kruskal's MST Simulator

## Category
Greedy Algorithms / Graphs (ADSA)

## Author
Ritika and deepshikha 

## Project Description
Visualize edge selection in Kruskal’s algorithm. This console-based simulator demonstrates
how Kruskal's algorithm chooses edges in order of increasing weight and uses a Disjoint Set Union
(Union-Find) data structure to detect cycles. The simulator prints step-by-step outputs showing:
- edges considered (sorted by weight),
- whether an edge is selected or skipped (due to cycle),
- the current connected components after each selection,
- the final MST edges and total weight.

## Features
- Manual input mode and example graph mode
- Step-by-step verbose simulation (toggleable)
- ASCII-style component visualization after each selected edge
- Clear console outputs suitable for teaching/demonstration and lab reports

## How to Compile & Run
```
g++ kruskal_simulator.cpp -o kruskal
./kruskal
```

## Example (using the built-in example graph)
The program will load a sample connected graph and run the simulation, showing which edges are selected.
Use manual mode to test your own graphs.

## Files
- kruskal_simulator.cpp : C++ source code for the simulator
- README.md : project description and instructions

## Notes for GitHub upload
- Replace "Your Name Here" in README with your actual name before committing.
- Add screenshots (optional) in a `screenshots/` folder to improve the repository README.

