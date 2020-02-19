#ifndef _PACKAGE_H
#define	_PACKAGE_H

#include <iostream>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "TLV.h"


struct __attribute__((__packed__)) package{
  uint8_t stx;
  TLV data;
  uint8_t etx;

  std::vector<uint8_t> getBytes(){
    std::vector<uint8_t> toReturn;
    std::vector<uint8_t> serialized = data.serialize();
    toReturn.push_back(stx);
     for (auto value : serialized){
      toReturn.push_back(value);
    }
    toReturn.push_back(etx);
    return toReturn;
  }
};

#endif	/* _PACKAGE_H */
