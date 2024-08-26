#  CircuitExplorer:Dijkstra's Algorithm Implementation
## Overview
Dijkstra's Algorithm is a fundamental algorithm used in graph theory and computer science for finding the shortest path between nodes in a graph. This project implements Dijkstra's Algorithm to solve the shortest path problem efficiently.
## Features
- **Graph Representation**: Allows users to represent Circuit with weighted edges.
- **Shortest Path Calculation**: Computes the shortest path between two nodes in a Circuit.
- **Path Visualization**: Visualizes the shortest path on the Circuit.
## Installation Process
To use Dijkstra's Algorithm, follow these steps:
Clone the repository:
```sh
git clone https://github.com/deeppadmani/CircuitExplorer_Dijkstra-s-Algorithm-Implementation.git
```
Navigate to the project directory: 
```sh
cd DMP210005_CE6320_Project
```
## Usage
For Compilation &  run
```sh
make
./iscas [Bech file name] [Src] [Dest]
Ex:
./iscas c17.bench G1gat G22gat
```
Total Bechmarks 
```sh
c17.bench
c432.bench
c499.bench
c880.bench
c1355.bench
c1908.bench
c2670.bench
c5315.bench
c6288.bench
c7552.bench
```
## Example
Consider the following example of finding the shortest path between nodes **G1gat** and **G22gat** in a Circuit:
```sh
INPUT(G1gat)
INPUT(G2gat)
INPUT(G3gat)
INPUT(G6gat)
INPUT(G7gat)
OUTPUT(G22gat)
OUTPUT(G23gat)

G10gat = nand(G1gat, G3gat)
G11gat = nand(G3gat, G6gat)
G16gat = nand(G2gat, G11gat)
G19gat = nand(G11gat, G7gat)
G22gat = nand(G10gat, G16gat)
G23gat = nand(G16gat, G19gat)
```
Output
```sh
Shortest path from G1gat to G22gat is:  --> G1gat --> G10gat --> G22gat
Minimun Distance from G1gat to G22gat is : 2
```
