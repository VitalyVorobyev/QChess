#ifndef QPOSITION_H
#define QPOSITION_H

#include "qbitboard.h"

class QPosition{
public:
  QPosition();
  int MakeMove(const QBitBoard& from,const QBitBoard& to,const int ind);

private:
  QBitBoard bpowns;
  QBitBoard bknights;
  QBitBoard bbishops;
  QBitBoard brocks;
  QBitBoard bquins;
  QBitBoard bking;

  QBitBoard wpowns;
  QBitBoard wknights;
  QBitBoard wbishops;
  QBitBoard wrocks;
  QBitBoard wquins;
  QBitBoard wking;

  QBitBoard boccupancy;
  QBitBoard woccupancy;
  QBitBoard occupancy;

  void SetBOcc(void);
  void SetWOcc(void);
  void SetOcc(void);

  bool turnFlag;// 0 -> white, 1 -> black
};

#endif // QPOSITION_H
