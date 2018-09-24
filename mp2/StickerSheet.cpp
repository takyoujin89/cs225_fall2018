#include "StickerSheet.h"
#include <string>
#include <iostream>
using namespace std;
#include "Image.h"



StickerSheet::StickerSheet(const Image &picture, unsigned max){
  arr = new Image[max];
  basePic = picture;
  indexes = new unsigned[max_*2];
  max_ = max;
  numStickers = 1;
  numIndexes = 0;
  for (unsigned int k =0; k<max_*2; k++){
    indexes[k] = -1;
  }
}
StickerSheet::~StickerSheet(){

    kill();
  }


StickerSheet::StickerSheet(const StickerSheet &other){
//  unsigned int k = sizeof(other.arr)/sizeof(other.arr[0]);
copy(other);

}
void StickerSheet::kill(){
  delete[] this->arr;
  delete[] this->indexes;


}
void StickerSheet::copy(const StickerSheet &other){
  basePic = other.basePic;
  max_ = other.max_;
  numStickers = other.numStickers;
  numIndexes = other.numIndexes;

  Image * arr = new Image[max_];
  for (unsigned int i =0; i<max_;i++){
    arr[i] = other.arr[i];
  }
  unsigned * indexes = new unsigned[max_*2];
  for (unsigned int i =0; i<max_*2;i++){
    indexes[i] = other.indexes[i];
  }

}
const StickerSheet& StickerSheet::operator = (const StickerSheet&other){
  kill();
//  unsigned int k = sizeof(other.arr)/sizeof(other.arr[0]);
  copy(other);
return *this;
}
void StickerSheet::changeMaxStickers(unsigned max){
  Image * temp = new Image[max];
  //unsigned int k = sizeof(this->arr)/sizeof(this->arr[0]);
  if (max>=max_){
    for (unsigned int i =0; i< max_; i++){
    temp[i] = arr[i];
  }
}
  if (max<max_){
    for (unsigned int i = 0; i<max; i++){
      temp[i] = arr[i];
    }
  }
  kill();
  arr = temp;


}
int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
//  int k = 0;
//  int max = sizeof(this->arr)/sizeof(this->arr[0]);
  if (numStickers==max_){return -1;}
  arr[numStickers] = sticker;
  indexes[numIndexes] = x;
  numIndexes++;
  indexes[numIndexes] = y;
  numIndexes++;
  numStickers++;
  return numStickers-1;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if ((index<=0)||(index>max_-1))
    return false;
  if ((arr[index].width() == 0)&&(arr[index].height()==0))
      return false;
  indexes[index*2] = x;
  indexes[index*2+1] = y;
  return true;
}
void StickerSheet::removeSticker(unsigned index){
  if ((index<=0)||(index>max_-1))
    return;
  if ((arr[index].width() == 0)&&(arr[index].height()==0))
    return;
    arr[index].resize(0,0);
  indexes[index*2] = -1;
  indexes[index*2+1] = -1;
  return;

}
Image * StickerSheet::getSticker (unsigned index) const{
  Image * ptr;
  if ((index<=0)||(index>max_-1)){
    ptr = NULL;
    return ptr;
  }

  if ((arr[index].width() == 0)&&(arr[index].height()==0)){
    ptr = NULL;
    return ptr;
}
  ptr = &arr[index];
  return ptr;
}
Image StickerSheet::render() const{
    Image *out = new Image(basePic);
    unsigned int totalW = basePic.width();
    unsigned int totalH = basePic.height();
    for (unsigned int i=0; i<max_;i++){
      unsigned w = indexes[i*2] + arr[i].width();
      unsigned h = indexes[i*2+1] + arr[i].height();

      if (w>totalW) totalW=w;
      if (h>totalH) totalH=h;
    }

    out->resize(totalW, totalH);
    for (unsigned int i =0; i<max_;i++){
      for(unsigned int a =0; a<arr[i].width();a++){
        for(unsigned int b =0; b<arr[i].height();b++){
          HSLAPixel & pic = out->getPixel(a,b);
          HSLAPixel & sticker = arr[i].getPixel(a,b);
          if (sticker.a==0){}
          else {
            pic.h = sticker.h;
            pic.l = sticker.l;
            pic.s = sticker.s;
            pic.a = sticker.a;
          }
        }
      }
    }

    Image output = *out;
    return output;
}
