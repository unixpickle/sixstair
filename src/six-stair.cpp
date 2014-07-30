#include "six-stair.hpp"

namespace SixStair {

SixStair::SixStair() {
  for (uint8_t i = 0; i < 6; i++) {
    Tube * topTube = new Tube(i + 1);
    Tube * bottomTube = new Tube(i + 1);
    
    topTube->last = topLast;
    if (topLast) topLast->next = topTube;
    else topFirst = topTube;
    
    bottomTube->last = bottomTube;
    if (bottomLast) bottomLast->next = bottomTube;
    else bottomFirst = bottomTube;
    
    bottomLast = bottomTube;
    topLast = topTube;
    
    for (uint8_t j = 0; j < i; j++) {
      bottomTube.PushEnd(i);
    }
  }
}

SixStair::SixStair(SixStair && stair) {
  topFirst = stair.topFirst;
  topLast = stair.topLast;
  bottomFirst = stair.bottomFirst;
  bottomLast = stair.bottomLast;
  stair.topFirst = stair.topLast = NULL;
  stair.bottomFirst = stair.bottomLast = NULL;
}

SixStair::~SixStair() {
  if (!topFirst && !bottomFirst) {
    return;
  }
}

SixStair & SixStair::operator=(Stair && stair) {
  topFirst = stair.topFirst;
  topLast = stair.topLast;
  bottomFirst = stair.bottomFirst;
  bottomLast = stair.bottomLast;
  stair.topFirst = stair.topLast = NULL;
  stair.bottomFirst = stair.bottomLast = NULL;
  return *this;
}

void SixStair::Flip() {
  Tube * _topFirst = topFirst;
  Tube * _topLast = topLast;
  topFirst = bottomFirst;
  topLast = bottomLast;
  bottomFirst = _topFirst;
  bottomLast = _topLast;
  
  ApplyGravity();
}

void SixStair::TurnForward(uint8_t count) {
  Tube * oldLast = topLast;
  
  topLast = topLast->last;
  topLast->next = NULL;
  
  topFirst->last = oldLast;
  
  oldLast->last = NULL;
  oldLast->next = topFirst;
  
  topFirst = oldLast;
  
  ApplyGravity();
}

void SixStair::TurnBackward(uint8_t count) {
  Tube * oldFirst = topFirst;
  
  topFirst = topFirst->next;
  topFirst->last = NULL;
  
  topLast->next = oldFirst;
  
  oldFirst->next = NULL;
  oldFirst->last = topLast;
  
  topLast = oldFirst;
  
  ApplyGravity();
}

void SixStair::ApplyGravity() {
  Tube * topTube = topFirst;
  Tube * bottomTube = bottomFirst;
  while (topTube) {
    
    
    topTube = topTube->next;
    bottomTube = bottomTube->next;
  }
}

}
