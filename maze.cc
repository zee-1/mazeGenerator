#include "maze.hh"
#include <iostream>
#include <cassert>
#include <random>

#define log(message) \
      std::cerr << "[log]" << __func__ << message;

using Maze::MazeGen;

MazeGen::MazeGen(const unsigned int size):size(size),target({(unsigned int)(rand()%this->size),(unsigned int)(rand()%this->size)}){
#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" initiated with parameters-> size:"<<this->size<<std::endl;
#endif
      this->_initMaze();

#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" executed successfully"<<std::endl;
#endif
}

MazeGen::MazeGen(Maze::Position pos, const unsigned int size):size(size),target(pos){
#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" initiated with parameters-> size:"<<this->size<<", Position ->"<<pos.x<<','<<pos.y<<std::endl;
#endif
      
      if(pos.x<0 or pos.x>this->size or pos.y<0 or pos.y>this->size){
            std::cerr<<"[ERROR]: From "<<__func__<<" Invalid Postion given {"<<pos.x<<','<<pos.y<<'}'<<std::endl;
            exit(1);
      }

      this->_initMaze();

#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" executed successfully"<<std::endl;
#endif
}

void MazeGen::_initMaze(){
#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" initiated with parameters->size:"<<this->size<<", target:"<<target<<std::endl;
#endif
      this->_MAZE = new char*[this->size];
      for(unsigned int i =0; i<this->size; i++){
            this->_MAZE[i] = new char[this->size];
      }

      for(unsigned int i=0; i<this->size; i++){
            for(unsigned int j=0; j<this->size; j++){
                  this->_MAZE[i][j]='*';
            }
      }

      this->_MAZE[this->target.x][this->target.y] = 'X';
#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" executed successfully"<<std::endl;
#endif
}

void MazeGen::ShowMaze(){
#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" Initiated"<<std::endl;
#endif
      for(int i=0;i<this->size; i++){
            for(int j=0; j<this->size; j++){
                  std::cout<<this->_MAZE[i][j]<<" ";
            }
            std::cout<<std::endl;
      }
#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" executed successfully"<<std::endl;
#endif
}

void MazeGen::createMaze(){
      Position curr = {0,0};

      std::default_random_engine generator;
      std::discrete_distribution<int> distribution {1,3,1,3};
#ifndef NDEBUG
std::cerr<<"[LOG]: From "<<__func__<<", Starting to create maze..."<<std::endl;
#endif
      while(curr!=target){

            int whereToMove = distribution(generator);
            auto newPos = moveCursor(curr,whereToMove);
            if(0<=newPos.x<this->size and 0<=newPos.y<this->size)
                  curr = newPos;
                  this->operator[](curr) = ' ';
            if (curr==target) break;
      }
#ifndef NDEBUG
std::cerr<<"[LOG]: From "<<__func__<<", Maze Created succesfully"<<std::endl;
#endif
}

Maze::Position Maze::moveCursor(Maze::Position p,int x){
/*
: 0== UP
: 1== DOWN
: 2== LEFT
: 3== RIGHT
*/
if(x==0){
      p.y+=1;
}else if(x==1){
      p.y-=1;
}else if(x==2){
      p.x-=1;
}else if(x==3){
      p.x+=1;
}else{
      std::cerr<<"[ERROR] From "<<__func__<<" Invalid Move {"<<x<<"}. Must be in Range 0<=x<=3."<<std::endl;
      exit(1);
}
return p;
}

char &MazeGen::operator[](Maze::Position p){
      return this->_MAZE[p.x][p.y];
}

std::ostream& operator<<(std::ostream& os,Maze::Position p){
      os<<'{'<<p.x<<','<<p.y<<'}';
      return os;
}

