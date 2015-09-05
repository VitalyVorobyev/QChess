#include "qposition.h"
#include "qlookup.h"

#include "string.h"

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

QPosition::QPosition(void){}

void QPosition::SetInitialPosition(void){
  bpieces[0] = U64(BlackPawns);
  bpieces[1] = U64(BlackKnights);
  bpieces[2] = U64(BlackBishops);
  bpieces[3] = U64(BlackRooks);
  bpieces[4] = U64(BlackQueens);
  bpieces[5] = U64(BlackKing);

  wpieces[0] = U64(WhitePawns);
  wpieces[1] = U64(WhiteKnights);
  wpieces[2] = U64(WhiteBishops);
  wpieces[3] = U64(WhiteRooks);
  wpieces[4] = U64(WhiteQueens);
  wpieces[5] = U64(WhiteKing);

  SetOcc();
  return;
}

void QPosition::SetBOcc(void){
  boccupancy = bpowns() | bknights() | bbishops() | brooks() | bquins() | bking();
}

void QPosition::SetWOcc(void){
  woccupancy = wpowns() | wknights() | wbishops() | wrooks() | wquins() | wking();
}

void QPosition::SetOcc(void){
  SetWOcc();
  SetBOcc();
  occupancy = woccupancy | boccupancy;
}

U64 QPosition::KingMovement(const U64& l, const U64& own_side) const{
  const U64 legal_moves = (soutOne(l) | nortOne(l) | eastOne(l) | noEaOne(l) | soEaOne(l) | westOne(l) | soWeOne(l) | noWeOne(l)) & ~own_side;
  return U64(legal_moves);
}

U64 QPosition::KnightMovement(const U64& location, const U64& own_side) const{
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
  return U64(moves & ~own_side);
}

U64 QPosition::WhitePawnMovement(const U64& location) const{
  // check the single space infront of the white pawn
  const U64 one_step = (location << 8 ) & ~occupancy;
  // for all moves that came from rank 2 (home row) and passed the above filter,
  // thereby being on rank 3, check and see if I can move forward one more
  const U64 two_steps = ((one_step & MaskRank[RANK_3]) << 8) & ~occupancy;
  // the union of the movements dictate the possible moves forward available
  const U64 valid_steps = one_step | two_steps;
  // next we calculate the pawn attacks
  // check the left side of the pawn, minding the underflow File A
  const U64 left_attack   = (location & ClearFile[FILE_A]) << 7;
  const U64 right_attack  = (location & ClearFile[FILE_H]) << 9;
  const U64 valid_attacks = (left_attack | right_attack) & boccupancy;

  return U64(valid_steps | valid_attacks);
}

U64 QPosition::RookMovement(const U64& location,const U64& own_side) const {
  const int pos = ffsll(location);
  const U64 blockers = occupancy & occupancyMaskRook[pos];
  return U64(QMagicHash::MagicRookMoves(blockers,pos) & ~own_side);
}

U64 QPosition::BishopMovement(const U64& location,const U64& own_side) const {
  const int pos = ffsll(location);
  const U64 blockers = occupancy & occupancyMaskBishop[pos];
  return U64(QMagicHash::MagicBishopMoves(blockers,pos) & ~own_side);
}

U64 QPosition::QueenMovement(const U64& location,const U64& own_side) const {
  return BishopMovement(location,own_side) & RookMovement(location,own_side);
}

U64 QPosition::BlackPawnMovement(const U64& location) const {
  // check the single space infront of the white pawn
  const U64 one_step = (location >> 8 ) & ~occupancy;
  // for all moves that came from rank 2 (home row) and passed the above filter,
  // thereby being on rank 3, check and see if I can move forward one more
  const U64 two_steps = ((one_step & MaskRank[RANK_6]) >> 8) & ~occupancy;
  // the union of the movements dictate the possible moves forward available
  const U64 valid_steps = one_step | two_steps;
  // next we calculate the pawn attacks
  // check the left side of the pawn, minding the underflow File A
  const U64 left_attack   = (location & ClearFile[FILE_H]) >> 7;
  const U64 right_attack  = (location & ClearFile[FILE_A]) >> 9;
  const U64 valid_attacks = (left_attack | right_attack) & woccupancy;

  return U64(valid_steps | valid_attacks);
}

void QPosition::PrintAttacks(void) const{
  QBitBoard wbocc(GetOcc());
  cout << "Position:" << endl;
  wbocc.Print();
  QBitBoard wpmov(WPawnMov());
  cout << "White pawn moves:" << endl;
  wpmov.Print();
  QBitBoard bpmov(BPawnMov());
  cout << "Black pawn moves:" << endl;
  bpmov.Print();
  QBitBoard wkmov(WKingMov());
  cout << "Whilte king moves:" << endl;
  wkmov.Print();
  QBitBoard bkmov(BKingMov());
  cout << "Black king moves:" << endl;
  bkmov.Print();
  QBitBoard wknmov(WKnightMov());
  cout << "Whilte knight moves:" << endl;
  wknmov.Print();
  QBitBoard bknmov(BKnightMov());
  cout << "Black knight moves:" << endl;
  bknmov.Print();
  QBitBoard wbmov(WBishopMov());
  cout << "Whilte bishop moves:" << endl;
  wbmov.Print();
  QBitBoard bbmov(BBishopMov());
  cout << "Black bishop moves:" << endl;
  bbmov.Print();
  QBitBoard wrmov(WRookMov());
  cout << "Whilte rook moves:" << endl;
  wrmov.Print();
  QBitBoard brmov(BRookMov());
  cout << "Black rook moves:" << endl;
  brmov.Print();
  QBitBoard wqmov(WQueenMov());
  cout << "Whilte queen moves:" << endl;
  wqmov.Print();
  QBitBoard bqmov(BQueenMov());
  cout << "Black queen moves:" << endl;
  bqmov.Print();
  return;
}

int QPosition::MakeMove(const QMove& move){
  const U64 FromToBB = move.From() ^ move.To();
  if(turnFlag){// black's move
    if(!(move.From() & boccupancy)) return -1; // There is no black piece on this square
    if(move.To() & boccupancy) return -2; // There is
    bpieces[move.Piece()] ^= FromToBB;
    boccupancy ^= FromToBB;
    if(move.CPiece()){
      wpieces[move.Piece()] ^= move.To();
      woccupancy ^= move.To();
    }
  } else{// white's move
    if(!(move.From() & woccupancy)) return -1;
    if(move.To() & woccupancy) return -2;
    wpieces[move.Piece()] ^= FromToBB;
    woccupancy ^= FromToBB;
    if(move.CPiece()){
      bpieces[move.Piece()] ^= move.To();
      boccupancy ^= move.To();
    }
  }
  return 0;
}

int QPosition::FindMoves(void){
  QBitBoard wpmov(WhitePawnMovement(wpowns()));
  QBitBoard wp(wpowns());
  const int nwp = wpmov.PopCount();
  for(int i=0; i<nwp; i++){
    const int loc = wpieces[0]
  }
}
