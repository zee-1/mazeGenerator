#include "maze.hh"
#include <iostream>

using Maze::MazeGen;

int main(int argc, char const *argv[])
{
      Maze::Position p{5,5};
      Maze::Position curr{0,0};
      Maze::Position n{0,5};
      MazeGen m(p,12);

      m.createMaze();
      m.makeMove(curr,n);
      m.ShowMaze();
      return 0;
}
