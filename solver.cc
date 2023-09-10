#include "solver.hh"
#include "maze.hh"
#include <exception>
#include <algorithm>

using namespace SOLVER;

std::string LOGLevel[3] = {"\x1B[7;97;32m[LOG]\x1B[0m","\x1B[7;97;33m[WARNING]\x1B[0m","\x1B[7;97;31m[ERROR]\x1B[0m"};
#define LOG(level,message) std::cerr<<LOGLevel[level-1]<<" From "<<__func__<<message<<std::endl;

solution SOLVER::BellmanFord(Maze::MazeGen m,Maze::Position target){
      auto size = m.GetSize();
      auto maze = m.GetMaze();
      int** distance;
      Maze::Position** parent;
      LOG(1," Allocating space for distace and ancestor matrix.")
      try{
            distance = new int*[size];
            parent = new Maze::Position*[size];
            for(int32_t i=0; i<size;i++){
                  distance[i] = new int[size];
                  parent[i]   = new Maze::Position[size];
            }
      }catch(std::bad_alloc& ba){
            LOG(3," Failed to allocated Memory!")
      }
      LOG(1," Space Successfully Allocated.")
      LOG(1," Initializing The Distance and Ancestor matrix")
      try{
            for(int32_t i=0; i<size; i++){
                  for(int32_t j=0;j<size; j++){
                        distance[i][j]=__INT32_MAX__;
                        parent[i][j] = {0,0};
                  }
            }
      }catch(std::exception& e){
            LOG(3,"Unhandled Exception:"<<e.what()<<" ")
      }
      LOG(1," The Distance and Ancestor matrix successfully initialized")

      distance[1][1]=0;

      LOG(1," Calculating Shortest Path")
      try{
            uint32_t i,j;
            for(int32_t n=0;n<(size*size)-1;n++)
            {      for(i=1; i<size;i++){
                        for(j=1; j<size; j++){
                              if((i-1)>=0 and (j-1)>=0 and (j+1)<size and (i+1)<size){
                                    // LEFT
                                    if((maze[i][j]==' ' or maze[i][j]=='X') and distance[i][j]!=__INT32_MAX__ and \
                                    (maze[i][j-1]==' '  or maze[i][j-1]=='X') and \
                                    distance[i][j]+1<distance[i][j-1]){
                                          distance[i][j-1] = distance[i][j]+1;
                                          parent[i][j-1] = Maze::Position(i,j);
                                    }
                                    //RIGHT
                                    if((maze[i][j]==' ' or maze[i][j]=='X') and distance[i][j]!=__INT32_MAX__ and \
                                    (maze[i][j+1]==' ' or  maze[i][j+1]=='X') and \
                                    distance[i][j]+1<distance[i][j+1]){
                                          distance[i][j+1] = distance[i][j]+1;
                                          parent[i][j+1] = Maze::Position(i,j);
                                    }      
                                    

                                    //DOWN
                                    if((maze[i][j]==' ' or maze[i][j]=='X') and distance[i][j]!=__INT32_MAX__ and \
                                    (maze[i+1][j]==' ' or maze[i+1][j]=='X') and \
                                    distance[i][j]+1<distance[i+1][j]){
                                          distance[i+1][j] = distance[i][j]+1;
                                          parent[i+1][j] = Maze::Position(i,j);

                                    }
                                    
                                    //UP
                                    if((maze[i][j]==' ' or maze[i][j]=='X') and distance[i][j]!=__INT32_MAX__ and \
                                    (maze[i-1][j]==' ' or maze[i-1][j]=='X') and \
                                    distance[i][j]+1<distance[i-1][j]){
                                          distance[i-1][j] = distance[i][j]+1;
                                          parent[i-1][j] = Maze::Position(i,j);
                                    }

                              }
                        
                        }
                  #ifndef NVERBOSE
                        for(int i=0; i<size; i++){
                              for(int j=0; j<size; j++){
                                    if(parent[i][j]==Maze::Position(0,0)){
                                          std::cout<<"-"<<"     ";continue;
                                    }
                                    std::cout<<parent[i][j]<<" ";
                              }
                              std::cout<<std::endl;
                        }
                  #endif
                  }
            }
      }catch(std::exception& oor){
            LOG(3," Unexpected Error Occured:"<<oor.what()<<" ")
      }
      LOG(1," Shortest Path Calculated")
      if(parent[target.x][target.y]==Maze::Position(0,0)){
            LOG(1," No path to target Found")
            std::cout<<target<<"->Target Parents:"<<parent[target.x][target.y]<<std::endl;
            for(int i=0; i<size; i++){
      std::cout<<std::endl;
}
            return solution();
            }
      LOG(1,"A test:"<<parent[target.x][target.y])
      std::vector<Maze::Position> PathToTarget;
      std::vector<int> Distance;
      auto curr = target;
      PathToTarget.push_back(curr);
      while (curr!=Maze::Position(1,1)){
            curr = parent[curr.x][curr.y];
            PathToTarget.push_back(curr);
#ifndef NVERBOSE
            std::cout<<"Test:"<<curr<<parent[curr.x][curr.y]<<std::endl;
#endif
            // Distance.push_back(distance[curr.x][curr.y]);
      }
      std::reverse(PathToTarget.begin(),PathToTarget.end());
      std::reverse(Distance.begin(),Distance.end());
#ifndef NVERBOSE
      LOG(1,"[VERBOSE] Path to target:")
      for(auto i: PathToTarget){
            std::cout<<i<<' ';
      }
      std::cout<<std::endl;
      LOG(1,"[VERBOSE] Total cost:"<<distance[target.x][target.y])
      std::cout<<"Parent Mat:"<<std::endl;
#endif

#ifdef PARENTMAT
for(int i=0; i<size; i++){
      for(int j=0; j<size; j++){
            if(parent[i][j]==Maze::Position(0,0)){
                  std::cout<<"-"<<"  ";continue;
            }
            std::cout<<parent[i][j]<<" ";
      }
      std::cout<<std::endl;
}
#endif

      LOG(1," Returning the Path")
      solution s = {Distance,PathToTarget};
      for(int i=0; i<size; i++){
            delete[] distance[i];
            delete[] parent[i];
      }
      delete[] distance;
      delete[] parent;
      LOG(1," Returned")
      return s;
}