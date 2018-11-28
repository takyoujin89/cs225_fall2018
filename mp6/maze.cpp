/* Your code here! */
#include "maze.h"
SquareMaze::SquareMaze() {

}
void SquareMaze::makeMaze(int width, int height) {
width_ = width;
height_ = height;
size_ = height_ * width_;
for(int i=0; i<size_; i++){
  walls.push_back(3);
}
//make square maze with all walls filled
DisjointSets path;
path.addelements(size_); //detect cycle
while(path.size(0)<size_){
  int random_wall = rand()%2; //which wall to rmove?
  int random_index = rand()%size_; //where?
  int index = 0;
  if(random_wall==1 || (random_index+1)%width==0){
    index = width;
    //removing down wall
  }
  if(random_index>=(width_*(height_-1))){
    random_wall = 0;
    //removing right wall if bottom row
  }
  int temp = path.find(index);
  int temp2 = path.find(random_index+index);
  if(temp!=temp2){
    path.setunion(temp, temp2);
    if(random_wall==0){
      int x = random_index%width_;
      int y = random_index/width;
      setWall(x,y,0,false);
      //remove right wall
    }
    else{
      int x = random_index%width_;
      int y = random_index/width_;
      setWall(x,y,1,false);
      //remove down wall
    }
  }
}
}
bool SquareMaze::canTravel(int x, int y, int dir) const {
// 0 = no walls
// 1 = right wall
// 2 = down wall
// 3 = down and right walls

//check validity
if(x>=0 && y >=0 && x<=width_-1 && y <=height_-1){
  if(dir==0){
    //if no or down
    if(walls[x+y*width_]==0 || walls[x+y*width_]==2){
      return true;
    }
    return false;
  }
  if(dir==1){
    //if no or right
    if(walls[x+y*width_]==0 || walls[x+y*width_]==1){
      return true;
    }
    return false;
  }
  if(dir==2){
    //if no or down
    if(walls[x+y*width_]==0 || walls[x+y*width_]==2){
      return true;
    }
    return false;
  }
  if(dir==3){
    //if no or right
    if(walls[x+y*width_]==0 || walls[x+y*width_]==1){
      return true;
    }
    return false;
  }
}
return false;
}
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  // 0 = no walls
  // 1 = right wall
  // 2 = down wall
  // 3 = down and right walls
  if(exists){
    if(dir==0){
      //if no or right
      if(walls[x+y*width_]==0 || walls[x+y*width_]==1){
        walls[x+y*width_]=1;
        return;
      }
      //if down
      else{
        walls[x+y*width_]=3; //down aaaaaaaaaaand right
      }
    }
    else{
      //no or down
      if(walls[x+y*width_]==0 || walls[x+y*width_]==2){
        walls[x+y*width_]=2; //down
        return;
      }
      else{
        walls[x+y*width_]=3; //down and right
        return;
      }
    }
  }
  //if trying to delete wall
  else{
    if(dir==0){ //right
      if(walls[x+y*width_]==3){
        walls[x+y*width_]=2;
        return;
      }
      if(walls[x+y*width_]==1){
        walls[x+y*width_]=0;
        return;
      }
    }
    else{ //down
      if(walls[x+y*width_]==3){
        walls[x+y*width_]=1;
        return;
      }
      if(walls[x+y*width_]==2){
        walls[x+y*width_]=0;
        return;
      }
    }
  }
}
vector<int> SquareMaze::solveMaze() { //BFS approach
  vector<int> path;
  map<int, int>steps;
  queue<int> q;
  q.push(0); //starting pooint

//traverse and find the path
  while(!q.empty()){
    int temp = q.front();
    q.pop();
    int x = temp%width_;
    int y = temp/width_;
    if(canTravel(x,y,0)){ //right
      steps.insert(pair<int, int>((x+1)+y*width_, temp));
      q.push((x+1)+y*width_);
    }
    if(canTravel(x,y,1)){ //down
      steps.insert(pair<int, int>(x+(y+1)*width_, temp));
      q.push(x+(y+1)*width_);
    }
    if(canTravel(x,y,2)){ //left
      steps.insert(pair<int,int>((x-1)+y&width_, temp));
      q.push((x-1)+y*width_);
    }
    if(canTravel(x,y,3)){
      steps.insert(pair<int,int>(x+(y-1)*width_, temp));
      q.push(x+(y-1)*width_);
    }

  }
  int d = 0;
  for(int i = 0; i<width_; i++){
    int index = i+(width_+(height_-1)); //bottom cell
    vector<int>best;
    while(index!=0){
      int temp = index - steps[index]; //distance from index to prev. steps
      if(temp==1){
        best.push_back(0); //moved right
      }
      if(temp == width_){
        best.push_back(1); //down
      }
      if(temp == -1){
        best.push_back(2); //left
      }
      if(temp == (-1*width_)){
        best.push_back(3);
      }
      index = steps[index]; //update index
    }
    if(d<(int)best.size()){
      path = best;
      d = best.size();
    }
  }
  reverse(path.begin(), path.end());
  return path;

}

PNG * SquareMaze::drawMaze() const {
  PNG * maize = new PNG(width_*10+1, height_*10+1);
  //blacken top row
  for(int i = 10; i<width_*10+1; i++){
    HSLAPixel& pix = maize->getPixel(i,0);
    pix.h = 0;
    pix.s = 0;
    pix.l = 0;
    pix.a = 0;
  }
  //blacken left
  for(int i = 0; i<height_*10+1; i++){
    HSLAPixel & pix = maize->getPixel(0, i);
    pix.h = 0;
    pix.s = 0;
    pix.l = 0;
    pix.a = 0;
  }
  //color in walls
  for(int i =0; i<width_; i++){
    for(int j = 0; j<height_; j++){
      if(walls[i+j*width_]==1 || walls[i+j*width_]==3){
        for(int k = 0; k<11; k++){
      HSLAPixel& pix = maize->getPixel((i+1)*10, j*10+k);
      pix.h =0;
      pix.s = 0;
      pix.l = 0;
      pix.a = 0;
    }
  }
  if(walls[i+j*width_]==3 || walls[i+j*width_]==2){
    for(int k = 0; k<11; k++){
      HSLAPixel & pix = maize->getPixel(i*10+k, (j+1)*10);
      pix.h = 0;
      pix.s = 0;
      pix.l = 0;
      pix.a = 0;
    }
  }
}
}
return maize;
}
PNG * SquareMaze::drawMazeWithSolution() {
  PNG * maize = drawMaze();
  vector<int> solved = solveMaze();
  int x = 5;
  int y = 5;
  for(unsigned long i = 0; i<solved.size(); i++){
    for(int j = 1; j<11; j++){
      HSLAPixel & pix = maize ->getPixel(x,y);
      pix.h = 0;
      pix.l = 0.5;
      pix.s = 1;
      pix.a = 1;
    if(i==0){ //move right
      x++;
    }
    if(i==1){ //move down
      y++;
    }
    if(i==2){ //move left
      x--;
    }
    if(i==3){ //move up
      y--;
    }
    }
    HSLAPixel & pix = maize ->getPixel(x,y);
    pix.h = 0;
    pix.s = 1;
    pix. l = 0.5;
    pix.a = 1;
}

  for(int k = 0; k<10; k++){
    HSLAPixel & pix = maize->getPixel(x+k-5, y+5);
    pix.h = 0;
    pix.s = 0;
    pix.l = 0;
    pix.a = 0;
  }
  return maize;
}
