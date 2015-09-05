#ifndef QPOSITION_H
#define QPOSITION_H

//#include "QBitBoard.h"
#include "qmagichash.h"
#include "qmove.h"

class QPosition{
public:
  QPosition(void);
  void SetInitialPosition(void);
  int MakeMove(const QMove& move);
  int FindMoves(void);

  U64 WKingMov(void) const {return KingMovement(wking(),woccupancy);}
  U64 BKingMov(void) const {return KingMovement(bking(),boccupancy);}

  U64 WKnightMov(void) const {return KnightMovement(wknights(),woccupancy);}
  U64 BKnightMov(void) const {return KnightMovement(bknights(),boccupancy);}

  U64 WPawnMov(void) const {return WhitePawnMovement(wpowns());}
  U64 BPawnMov(void) const {return BlackPawnMovement(bpowns());}

  U64 WRookMov(void) const {return RookMovement(wrooks(),woccupancy);}
  U64 BRookMov(void) const {return RookMovement(brooks(),boccupancy);}

  U64 WBishopMov(void) const {return BishopMovement(wbishops(),woccupancy);}
  U64 BBishopMov(void) const {return BishopMovement(bbishops(),boccupancy);}

  U64 WQueenMov(void) const {return QueenMovement(wquins(),woccupancy);}
  U64 BQueenMov(void) const {return QueenMovement(bquins(),boccupancy);}

  U64 GetBOcc(void) const {return boccupancy;}
  U64 GetWOcc(void) const {return woccupancy;}
  U64 GetOcc(void)  const {return occupancy;}

  void PrintAttacks(void) const;

private:
  U64 KingMovement(const U64 &l, const U64& own_side) const;
  U64 KnightMovement(const U64& king_location, const U64& own_side) const;
  U64 WhitePawnMovement(const U64& location) const;
  U64 BlackPawnMovement(const U64& location) const;
  U64 RookMovement(const U64& location,const U64& own_side) const;
  U64 BishopMovement(const U64& location,const U64& own_side) const;
  U64 QueenMovement(const U64& location,const U64& own_side) const;

  U64 bpieces[6];
  U64 wpieces[6];
  U64 bpowns(void)   const {return bpieces[0];}
  U64 bknights(void) const {return bpieces[1];}
  U64 bbishops(void) const {return bpieces[2];}
  U64 brooks(void)   const {return bpieces[3];}
  U64 bquins(void)   const {return bpieces[4];}
  U64 bking(void)    const {return bpieces[5];}

  U64 wpowns(void)   const {return wpieces[0];}
  U64 wknights(void) const {return wpieces[1];}
  U64 wbishops(void) const {return wpieces[2];}
  U64 wrooks(void)   const {return wpieces[3];}
  U64 wquins(void)   const {return wpieces[4];}
  U64 wking(void)    const {return wpieces[5];}

  U64 boccupancy;
  U64 woccupancy;
  U64 occupancy;

  void SetBOcc(void);
  void SetWOcc(void);
  void SetOcc(void);

  bool turnFlag;// 0 -> white, 1 -> black
  bool wsCastleFlag;
  bool wlCastleFlag;
  bool bsCastleFlag;
  bool blCastleFlag;

  static QMagicHash magic;
  vector<QMove> moves;
};

#endif // QPOSITION_H
