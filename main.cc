#include "maze.hh"
#include "solver.hh"
#include <iostream>

using Maze::MazeGen;
using SOLVER::BellmanFord;
using SOLVER::solution;

//"\033[{FORMAT_ATTRIBUTE};{FORGROUND_COLOR};{BACKGROUND_COLOR}m{TEXT}\033[{RESET_FORMATE_ATTRIBUTE}m"
// "Green", "32"
// "Yellow", "33"
// "Red", "31"


int main(int argc, char const *argv[])
{
      int size=21;
      for(int i=0;i<argc-1;i++){
            // std::cout<<((std::string)(argv[i])=="--size")<<std::endl;
            if((std::string)argv[i]=="--size" or argv[i]=="-s"){
                  auto arg = argv[i+1];
            #ifndef NDEBUG
                  std::cerr<<"\x1B[7;32m[LOG] \x1B[0m Setting Size to :"<<arg<<std::endl;
            #endif
            try{
            size = atoi(arg);
            }catch(...){
                  std::cout<<"[ERROR] Unexpected Error"<<std::endl;
            }
            }
      }

      srand(time(0));
      MazeGen m(size);
      m.createMaze();
      m.ShowMaze();
      auto s =SOLVER::BellmanFord(m,m.GetTarget());
      std::cerr<<"\x1B[7;32m[LOG]\x1B[0m Bellman Ford Executed Successfully"<<std::endl;
      
      // for(auto i: s.parent){
      //       std::cout<<i<<std::endl;
      // }
      return 0;
}
