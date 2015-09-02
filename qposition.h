#ifndef QPOSITION_H
#define QPOSITION_H

#include "qbitboard.h"

class QPosition{
public:
  QPosition(void);
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

  QBitBoard KingMovement(const U64 &l, const U64& own_side);
  QBitBoard KnightMovement(const U64& king_location, const U64& own_side);
  QBitBoard WhitePawnMovement(const U64& location);
  QBitBoard BlackPawnMovement(const U64& location);

  bool turnFlag;// 0 -> white, 1 -> black
};

#endif // QPOSITION_H
