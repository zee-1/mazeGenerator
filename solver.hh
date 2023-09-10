#ifndef SOLVER_H
#define SOLVER_H

#include "maze.hh"
#include <vector>

namespace SOLVER
{
      struct solution
      {
            int **distance;
            std::pair<int,int> **parent;
      };
      
      solution DisjkstrasAlgo(Maze::MazeGen);
      solution BellmanFord(Maze::MazeGen);
      class Solver{
            public:
                  Solver(Maze::MazeGen);

      };
} // namespace Solver

#endif