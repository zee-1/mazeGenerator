#ifndef SOLVER_H
#define SOLVER_H

#include "maze.hh"
#include <vector>

namespace SOLVER
{
      struct solution
      {
            std::vector<int> distance;
            std::vector<Maze::Position> parent;
      };
      
      class Solver{
            public:
                  Solver(Maze::MazeGen);

      };
      solution DisjkstrasAlgo(Maze::MazeGen);
      solution BellmanFord(Maze::MazeGen,Maze::Position target);
} // namespace Solver

#endif