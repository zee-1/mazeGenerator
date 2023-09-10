#include "solver.hh"
#include "maze.hh"
#include <exception>

using namespace SOLVER;

std::string LOGLevel[3] = {"\x1B[7;97;32m[LOG]\x1B[0m","\x1B[7;97;33m[WARNING]\x1B[0m","\x1B[7;97;31m[ERROR]\x1B[0m"};
#define LOG(level,message) std::cerr<<LOGLevel[level-1]<<" From "<<__func__<<message<<std::endl;

solution SOLVER::BellmanFord(Maze::MazeGen m){
      auto size = m.GetSize();
      auto maze = m.GetMaze();
      int** distance;
      std::pair<int,int>** parent;
      LOG(1," Allocating space for distace and ancestor matrix.")
      try{
            distance = new int*[size];
            parent = new std::pair<int,int>*[size];
            for(uint32_t i=0; i<size;i++){
                  distance[i] = new int[size];
                  parent[i]   = new std::pair<int,int>[size];
            }
      }catch(std::bad_alloc& ba){
            LOG(3," Failed to allocated Memory!")
      }
      LOG(1," Space Successfully Allocated.")
      LOG(1," Initializing The Distance and Ancestor matrix")
      try{
            for(uint32_t i=0; i<size; i++){
                  for(uint32_t j=0;j<size; j++){
                        distance[i][j]=__INT32_MAX__;
                        parent[i][j] = {-1,-1};
                  }
            }
      }catch(std::exception& e){
            LOG(3,"Unhandled Exception:"<<e.what()<<" ")
      }
      LOG(1," The Distance and Ancestor matrix successfully initialized")

      distance[1][1]=0;

      LOG(1," Calculating Shortest Path")
      try{
            int32_t i,j;
            for(i=1; i<size;i++){
                  for(j=1; j<size; j++){
                        if((i-1)>=0 and (j-1)>=0 and (j+1)<size and (i+1)<size){
                              // UP
                              if((maze[i][j]==' ' or maze[i][j]=='X') and distance[i][j]!=__INT32_MAX__ and \
                              (maze[i][j-1]==' '  or maze[i][j-1]=='X') and \
                              distance[i][j]+1<distance[i][j-1]){
                                    distance[i][j-1] = distance[i][j]+1;

                                    parent[i][j-1] = {i,j};
                              }
                              //DOWN
                              if((maze[i][j]==' ' or maze[i][j]=='X') and distance[i][j]!=__INT32_MAX__ and \
                              (maze[i][j+1]==' ' or  maze[i][j+1]=='X') and \
                              distance[i][j]+1<distance[i][j+1]){
                                    distance[i][j+1] = distance[i][j]+1;
                                    parent[i][j+1] = {i,j};
                              }      
                              

                              //Right
                              if((maze[i][j]==' ' or maze[i][j]=='X') and distance[i][j]!=__INT32_MAX__ and \
                              (maze[i+1][j]==' ' or maze[i+1][j]=='X') and \
                              distance[i][j]+1<distance[i+1][j]){
                                    distance[i+1][j] = distance[i][j]+1;
                                    parent[i+1][j] = {i,j};

                              }
                              
                              //Left
                              if((maze[i][j]==' ' or maze[i][j]=='X') and distance[i][j]!=__INT32_MAX__ and \
                              (maze[i-1][j]==' ' or maze[i-1][j]=='X') and \
                              distance[i][j]+1<distance[i-1][j]){
                                    distance[i-1][j] = distance[i][j]+1;
                                    parent[i-1][j] = {i,j};
                              }

                        }
                  }
            }std::cout<<i<<'-'<<j<<std::endl;
      }catch(std::exception& oor){
            LOG(3," Unexpected Error Occured:"<<oor.what()<<" ")
      }
      LOG(1," Shortest Path")
      solution s = {distance,parent};
      return s;
}