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

            solution()=default;
            solution(std::vector<int> dist,std::vector<Maze::Position> parent):distance(dist),parent(parent){};
            solution operator=(solution&);
      };
      
      class Solver{
            public:
                  Solver(Maze::MazeGen &Maze);
                  void ShowSolution(char Mode,char AlgoIndex);
            private:
                  void Solve(solution (algo)(Maze::MazeGen&,Maze::Position&));
                  Maze::Position target;
                  Maze::MazeGen maze;
                  solution sol;

      };
      solution DisjkstrasAlgo(Maze::MazeGen&,Maze::Position &target);
      solution BellmanFord(Maze::MazeGen&,Maze::Position &target);
} // namespace Solver

#endif