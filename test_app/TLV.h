#ifndef _TLV_H
#define	_TLV_H
#include <vector>
#include <iostream>

class TLV{
public:
  TLV();
  TLV(uint8_t tag, uint16_t length, std::vector<uint8_t> value);
  std::vector<uint8_t> serialize();
  TLV deserialize(std::vector<uint8_t> serialized);
  uint8_t getTag(){return tag;}
  uint16_t getLen(){return length;}
  std::vector<uint8_t> getValue(){return value;}
  void setData(std::vector<uint8_t> val){value = val;}
  void setTag(uint8_t tag_val){tag = tag_val;}
  void setLen(uint16_t len){length = len;}

private:
  uint8_t tag;
  uint16_t length;
  std::vector<uint8_t> value;
};

#endif	/* _TLV_H */
