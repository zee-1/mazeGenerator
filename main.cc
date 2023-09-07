#include "maze.hh"
#include <iostream>

using Maze::MazeGen;

int main(int argc, char const *argv[])
{
      int size=21;
      for(int i=0;i<argc-1;i++){
            // std::cout<<((std::string)(argv[i])=="--size")<<std::endl;
            if((std::string)argv[i]=="--size" or argv[i]=="-s"){
                  auto arg = argv[i+1];
            #ifndef NDEBUG
                  std::cerr<<"[LOG] Setting Size to :"<<arg;
            #endif
                  size = atoi(arg);
            }
      }

      srand(time(0));
      // Maze::Position p={(unsigned int)(rand()%(size-1+1)+1),(unsigned int)(rand()%(size-1+1)+1)};
      // Maze::Position curr{0,0};
      // Maze::Position n{0,5};
      // MazeGen m(p,size);
      MazeGen m(size);


      m.createMaze();
      m.ShowMaze();
      return 0;
}
