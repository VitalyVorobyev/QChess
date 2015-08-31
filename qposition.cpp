#include "qposition.h"

const U64 WhitePawns   = 0b0000000000000000000000000000000000000000000000001111111100000000;
const U64 WhiteRooks   = 0b0000000000000000000000000000000000000000000000000000000010000001;
const U64 WhiteKnights = 0b0000000000000000000000000000000000000000000000000000000001000010;
const U64 WhiteBishops = 0b0000000000000000000000000000000000000000000000000000000000100100;
const U64 WhiteQueens  = 0b0000000000000000000000000000000000000000000000000000000000001000;
const U64 WhiteKing    = 0b0000000000000000000000000000000000000000000000000000000000010000;

const U64 BlackPawns   = 0b0000000011111111000000000000000000000000000000000000000000000000;
const U64 BlackRooks   = 0b1000000100000000000000000000000000000000000000000000000000000000;
const U64 BlackKnights = 0b0100001000000000000000000000000000000000000000000000000000000000;
const U64 BlackBishops = 0b0010010000000000000000000000000000000000000000000000000000000000;
const U64 BlackQueens  = 0b0000100000000000000000000000000000000000000000000000000000000000;
const U64 BlackKing    = 0b0001000000000000000000000000000000000000000000000000000000000000;

QPosition::QPosition(){
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

//int QPosition::MakeMove(const QBitBoard& from,const QBitBoard& to,const int ind){
//    if(turnFlag){// black's move
//        if(!(from.Bits() & boccupancy.Bits())) return -1; // There is no black piece on this square
//        if(to.Bits() & boccupancy.Bits()) return -2; // There is
//    }
//}
