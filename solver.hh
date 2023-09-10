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
      
      class Solver{
            public:
                  Solver(Maze::MazeGen);

      };
      solution DisjkstrasAlgo(Maze::MazeGen);
      solution BellmanFord(Maze::MazeGen);
} // namespace Solver

#endif