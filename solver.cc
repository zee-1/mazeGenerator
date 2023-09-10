#pragma once

#include "solver.hh"
#include "maze.hh"

using namespace SOLVER;

solution BellmanFord(Maze::MazeGen m){
      auto size = m.GetSize();
      auto maze = m.GetMaze();
      
      int** distance = new int*[size];
      std::pair<int,int>** parent = new std::pair<int,int>*[size];

      for(uint32_t i=0; i<size;i++){
            distance[i] = new int[size];
      }
      for(uint32_t i=0; i<size; i++){
            for(uint32_t j=0;j<size; j++){
                  distance[i][j]=__INT32_MAX__;
                  parent[i][j] = {-1,-1};
            }
      }

      distance[0][0]=0;

      for(uint32_t i=0; i<size;i++){
            for(uint32_t j=0; j<size; j++){
                  if(i-1>=0 and j-1>=0 and j+1<size and i+1<size){
                        // Down
                        if(distance[i][j]!=__INT32_MAX__ and \
                        maze[i][j-1]==' ' and \
                        distance[i][j]+1<distance[i][j-1]){
                              distance[i][j-1] = distance[i][j]+1;
                              parent[i][j-1] = {i,j};
                        }

                        //Up
                        if(distance[i][j]!=__INT32_MAX__ and \
                        maze[i][j+1]==' ' and \
                        distance[i][j]+1<distance[i][j+1]){
                              distance[i][j+1] = distance[i][j]+1;
                              parent[i][j+1] = {i,j};

                        }

                        //Right
                        if(distance[i][j]!=__INT32_MAX__ and \
                        maze[i+1][j]==' ' and \
                        distance[i][j]+1<distance[i+1][j]){
                              distance[i+1][j] = distance[i][j]+1;
                              parent[i+1][j] = {i,j};

                        }
                        
                        //Left
                        if(distance[i][j]!=__INT32_MAX__ and \
                        maze[i-1][j]==' ' and \
                        distance[i][j]+1<distance[i-1][j]){
                              distance[i-1][j] = distance[i][j]+1;
                              parent[i-1][j] = {i,j};
                        }
                  }
            }
      }

      solution s = {distance,parent};
      return s;

}