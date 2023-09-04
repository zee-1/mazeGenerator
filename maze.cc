#include "maze.hh"
#include <iostream>
#include <cassert>
#include <random>

#define log(message) \
      std::cerr << "[log]" << __func__ << message;

using Maze::MazeGen;

//;=================== MazeGen(int)==================
MazeGen::MazeGen(const unsigned int size):size(size),target({(unsigned int)(rand()%this->size),(unsigned int)(rand()%this->size)}){
#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" initiated with parameters-> size:"<<this->size<<std::endl;
#endif
      this->_initMaze();

#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" executed successfully"<<std::endl;
#endif
}


//;================= MazeGen(Position,int)===========
MazeGen::MazeGen(Maze::Position pos, const unsigned int size):size(size),target(pos){
#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" initiated with parameters-> size:"<<this->size<<", Position ->"<<pos.x<<','<<pos.y<<std::endl;
#endif
      
      if(pos.x<0 or pos.x>=this->size or pos.y<0 or pos.y>=this->size){
            std::cerr<<"[ERROR]: From "<<__func__<<" Invalid Postion given {"<<pos.x<<','<<pos.y<<'}'<<std::endl;
            exit(1);
      }

      this->_initMaze();

#ifndef NDEBUG
      std::cerr<<"[LOG]: From "<<__func__<<" executed successfully"<<std::endl;
#endif
}


//;================ _initMaze()===================
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


//;=============== ShowMaze()====================
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


//;============= createMaze()===================
void MazeGen::createMaze(){

      std::default_random_engine generator(time(0));
#ifndef NDEBUG
std::cerr<<"[LOG]: From "<<__func__<<", Starting to create maze..."<<std::endl;
#endif

      Position pos[] = {{1,1},{1,this->size-2},{this->size-2,1},{this->size-2,this->size-2},{}};
      for(ushort i=0; i<4;i++){

            auto curr = pos[i];
            unsigned short moveDecider = 0;
            auto moveCounter = this->size/2;
            unsigned int moveWeightage[4] = {moveCounter,moveCounter,moveCounter,moveCounter};
            while(moveCounter){

                  int whereToMove[4];
                  std::discrete_distribution<int> distribution {3,6,1,6};
                  for(int i=0;i<4;i++)
                  whereToMove[i] = distribution(generator);

                  auto newPos = findMove(curr,whereToMove[moveDecider]);
                  if(0<newPos.x and newPos.x<this->size-1 and 0<newPos.y and newPos.y<this->size-1){
                        if(this->operator[](newPos)==' ') moveDecider++;
                        this->makeMove(curr,newPos);
                        moveWeightage[whereToMove[moveDecider]]--;
                        moveCounter--;
                        curr = newPos;
                        moveDecider=rand()%4;
                        #ifndef NVERBOSE
                        std::cout<<"Current Position:"<<curr<<std::endl;
                        #endif
                  }
                  if (curr==target) continue;
            }
      }
      this->operator[](target)='X';
#ifndef NDEBUG
std::cerr<<"[LOG]: From "<<__func__<<", Maze Created succesfully"<<std::endl;
#endif
}


//;============== moveCursor(Position,int)======
Maze::Position Maze::findMove(Maze::Position p,int x){
/*
: 0== UP
: 1== DOWN
: 2== LEFT
: 3== RIGHT
*/
if(x==0){
      p.y+=2;
}else if(x==1){
      p.y-=2;
}else if(x==2){
      p.x-=2;
}else if(x==3){
      p.x+=2;
}else{
      std::cerr<<"[ERROR] From "<<__func__<<" Invalid Move {"<<x<<"}. Must be in Range 0<=x<=3."<<std::endl;
      exit(1);
}
return p;
}


//;====================== MazeGen::operator[]==============
char &MazeGen::operator[](Maze::Position p){
      auto &ref = (this->_MAZE[p.x][p.y]);
      return ref;
}


//;====================== MazeGen::operator<< ==============
std::ostream& Maze::operator<<(std::ostream& os,Maze::Position p){
      os<<'{'<<p.x<<','<<p.y<<'}';
      return os;
}

//;===================== MazeGen::makeMove(Position,Position)==
void MazeGen::makeMove(Maze::Position curr,Maze::Position new_){
      if(!(curr.x-new_.x)){
            auto start = std::min(curr.y,new_.y),
                   end = std::max(curr.y,new_.y);
            for(int i=start;i<=end;i++){
                  this->_MAZE[curr.x][i]=' ';
            }
      }else if(!(curr.y-new_.y)){
            auto start = std::min(curr.x,new_.x),
                   end = std::max(curr.x,new_.x);
            for(int i=start;i<=end;i++){
                  this->_MAZE[i][curr.y]=' ';
            }
      }else{
            std::cerr<<"[ERROR]: From "<<__func__<<" Invalid move"<<new_<<". \nMove must be in 1 direction."<<std::endl;
      }
}
