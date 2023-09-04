#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
namespace Maze
{
      struct Position
      {   int x,y;
            Position() = default;
            inline Position(unsigned int x,unsigned int y){this->x=x;this->y=y;};
            bool operator==(Position p2){ return (this->x==p2.x and this->y==this->y);};
            bool operator!=(Position p2){ return !(*this==p2);};
      };
      
      class MazeGen{

            public:
                  MazeGen(unsigned int size);
                  MazeGen(Position target_position,unsigned int size);


                  void ShowMaze();
                  void createMaze();
                  char& operator[](Position);
            private:
                  const unsigned int size;
                  const Position target;
                  char **_MAZE;
                  void _initMaze();

};
Maze::Position moveCursor(Maze::Position p,int x);
std::ostream& operator<<(std::ostream&,Position);
} // namespace Maze
#endif
