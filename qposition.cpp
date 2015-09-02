#include "qposition.h"
#include "qlookup.h"

QPosition::QPosition(void){
  bpowns   = QBitBoard(0);
  bknights = QBitBoard(0);
  bbishops = QBitBoard(0);
  brocks   = QBitBoard(0);
  bquins   = QBitBoard(0);
  bking    = QBitBoard(0);

  wpowns   = QBitBoard(0);
  wknights = QBitBoard(0);
  wbishops = QBitBoard(0);
  wrocks   = QBitBoard(0);
  wquins   = QBitBoard(0);
  wking    = QBitBoard(0);

  boccupancy = QBitBoard(0);
  woccupancy = QBitBoard(0);
  occupancy  = QBitBoard(0);
}

void QPosition::SetBOcc(void){
  boccupancy = bpowns | bknights | bbishops | brocks | bquins | bking;
}

void QPosition::SetWOcc(void){
  woccupancy = wpowns | wknights | wbishops | wrocks | wquins | wking;
}

void QPosition::SetOcc(void){
  SetWOcc();
  SetBOcc();
  occupancy = woccupancy | boccupancy;
}

QBitBoard QPosition::KingMovement(const U64& l, const U64& own_side){
  const U64 legal_moves = (soutOne(l) | nortOne(l) | eastOne(l) | noEaOne(l) | soEaOne(l) | westOne(l) | soWeOne(l) | noWeOne(l)) & ~own_side;
  return QBitBoard(legal_moves);
}

QBitBoard QPosition::KnightMovement(const U64& location, const U64& own_side){
  const U64 clearAB = ClearFile[FILE_A] & ClearFile[FILE_B];
  const U64 clearGH = ClearFile[FILE_G] & ClearFile[FILE_H];

  const U64 spot1 = (location & clearAB)           << 6;
  const U64 spot2 = (location & ClearFile[FILE_A]) << 15;
  const U64 spot3 = (location & ClearFile[FILE_H]) << 17;
  const U64 spot4 = (location & clearGH)           << 10;

  const U64 spot5 = (location & clearGH)           >> 6;
  const U64 spot6 = (location & ClearFile[FILE_H]) >> 15;
  const U64 spot7 = (location & ClearFile[FILE_A]) >> 17;
  const U64 spot8 = (location & clearAB)           >> 10;

  const U64 moves = spot1 | spot2 | spot3 | spot4 | spot5 | spot6 | spot7 | spot8;
  return QBitBoard(moves & ~own_side);
}

QBitBoard QPosition::WhitePawnMovement(const U64& location){
  // check the single space infront of the white pawn
  const U64 one_step = (location << 8 ) & ~occupancy.Bits();
  // for all moves that came from rank 2 (home row) and passed the above filter,
  // thereby being on rank 3, check and see if I can move forward one more
  const U64 two_steps = ((one_step & MaskRank[RANK_3]) << 8) & ~occupancy.Bits();
  // the union of the movements dictate the possible moves forward available
  const U64 valid_steps = one_step | two_steps;
  // next we calculate the pawn attacks
  // check the left side of the pawn, minding the underflow File A
  const U64 left_attack   = (location & ClearFile[FILE_A]) << 7;
  const U64 right_attack  = (location & ClearFile[FILE_H]) << 9;
  const U64 valid_attacks = (left_attack | right_attack) & boccupancy.Bits();

  return QBitBoard(valid_steps | valid_attacks);
}

QBitBoard QPosition::RookMovement(const U64& location,const U64& own_side){
  const int pos = FirstNonZeroIndex(location);
  const U64 blockers = boccupancy & occupancyMaskRook[pos];
  const int index = (int)(blockers * magicNumberRook[pos]) >> magicNumberShiftsRook[pos];
  return QBitBoard(magicMovesRook[pos][index] & ~own_side);
}

QBitBoard QPosition::BlackPawnMovement(const U64& location){
  // check the single space infront of the white pawn
  const U64 one_step = (location >> 8 ) & ~occupancy.Bits();
  // for all moves that came from rank 2 (home row) and passed the above filter,
  // thereby being on rank 3, check and see if I can move forward one more
  const U64 two_steps = ((one_step & MaskRank[RANK_6]) >> 8) & ~occupancy.Bits();
  // the union of the movements dictate the possible moves forward available
  const U64 valid_steps = one_step | two_steps;
  // next we calculate the pawn attacks
  // check the left side of the pawn, minding the underflow File A
  const U64 left_attack   = (location & ClearFile[FILE_H]) >> 7;
  const U64 right_attack  = (location & ClearFile[FILE_A]) >> 9;
  const U64 valid_attacks = (left_attack | right_attack) & woccupancy.Bits();

  return QBitBoard(valid_steps | valid_attacks);
}

//int QPosition::MakeMove(const QBitBoard& from,const QBitBoard& to,const int ind){
//    if(turnFlag){// black's move
//        if(!(from.Bits() & boccupancy.Bits())) return -1; // There is no black piece on this square
//        if(to.Bits() & boccupancy.Bits()) return -2; // There is
//    }
//}
