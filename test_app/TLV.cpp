#include <iostream>
#include "TLV.h"

TLV::TLV(){}
TLV::TLV(uint8_t tag_val, uint16_t len, std::vector<uint8_t> val)
{
  tag=tag_val;
  length=len;
  value=val;
}

std::vector<uint8_t> TLV::serialize(){
  std::vector<uint8_t> toReturn;
  uint8_t l1 = (length >> 8);
  uint8_t l2 = length & 0x00FF;
  toReturn.push_back(tag);
  toReturn.push_back(l1);
  toReturn.push_back(l2);
  //toReturn.push_back(length);
   for (auto data : value){
    toReturn.push_back(data);
  }
  return toReturn;
}

TLV TLV::deserialize(std::vector<uint8_t> serialized)
{
  /* 
  std::vector<uint8_t> val;
  uint8_t tag = serialized[0];
  uint8_t len= serialized[1];
  std::vector<uint8_t> val;
  for(int i = 0 ; i < len ; i++)
    val.pushback(serialized[i])
  */
}
