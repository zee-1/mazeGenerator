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

            solution operator=(solution&);
      };
      
      class Solver{
            public:
                  Solver(Maze::MazeGen);
                  void ShowSolution(char);
            private:
                  void Solve(solution (f)(Maze::MazeGen,Maze::Position));
                  Maze::Position target;
                  Maze::MazeGen maze;
                  solution sol;

      };
      solution DisjkstrasAlgo(Maze::MazeGen);
      solution BellmanFord(Maze::MazeGen,Maze::Position target);
} // namespace Solver

#endif