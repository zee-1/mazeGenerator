#include "maze.hh"
#include <iostream>

using Maze::MazeGen;

int main(int argc, char const *argv[])
{
      Maze::Position p{1,10};
      MazeGen m(p,10);

      m.createMaze();
      m.ShowMaze();
      return 0;
}