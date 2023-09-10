#ifndef MAZE_H
#define MAZE_H

#include <random>
#include <vector>
#include <iostream>
#include <initializer_list>

//std::string LogLevel[3] = {"\x1B[7;97;32m[LOG]\x1B[0m","\x1B[7;97;33m[WARNING]\x1B[0m","\x1B[7;97;31m[ERROR]\x1B[0m"};

namespace Maze
{
      struct Position
      {
            uint32_t x,y;
            Position() = default;
            inline Position(unsigned int x,unsigned int y){this->x=x;this->y=y;};            
            bool operator==(Position p2){ return (this->x==p2.x and this->y==p2.y);};
            bool operator!=(Position p2){ return !(*this==p2);};
            void operator=(std::initializer_list<int32_t>& p);
      };
      
      class MazeGen{

            public:
                  MazeGen(unsigned int size);
                  MazeGen(Position target_position,unsigned int size);


                  void ShowMaze();
                  char& operator[](Position);
                  void createMaze();
                  char** GetMaze();
                  unsigned int GetSize();
                  Position GetTarget();
                  // ~MazeGen();
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

