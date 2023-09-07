#ifndef MAZE_H
#define MAZE_H

#include <random>
#include <vector>
#include <iostream>
#include <initializer_list>
namespace Maze
{
      struct Position
      {
            int x,y;
            Position() = default;
            inline Position(unsigned int x,unsigned int y){this->x=x;this->y=y;};            
            bool operator==(Position p2){ return (this->x==p2.x and this->y==p2.y);};
            bool operator!=(Position p2){ return !(*this==p2);};
            void operator=(std::initializer_list<int>& p);
      };
      
      class MazeGen{

            public:
                  MazeGen(unsigned int size);
                  MazeGen(Position target_position,unsigned int size);


                  void ShowMaze();
                  char& operator[](Position);
                  void createMaze();
            private:
                  const unsigned int size;
                  const Position target;
                  char **_MAZE;
                  void _initMaze();
                  void makeMove(Position curr,Position new_);

};
Maze::Position findMove(Maze::Position p,int x);
std::ostream& operator<<(std::ostream&,Position);
} // namespace Maze
#endif

