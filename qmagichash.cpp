#include "qmagichash.h"
#include "qlookup.h"

#include <stdlib.h>
#include <bitset>

#include "string.h"

int RBits[64] = {
  12, 11, 11, 11, 11, 11, 11, 12,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  12, 11, 11, 11, 11, 11, 11, 12
};

int BBits[64] = {
  6, 5, 5, 5, 5, 5, 5, 6,
  5, 5, 5, 5, 5, 5, 5, 5,
  5, 5, 7, 7, 7, 7, 5, 5,
  5, 5, 7, 9, 9, 7, 5, 5,
  5, 5, 7, 9, 9, 7, 5, 5,
  5, 5, 7, 7, 7, 7, 5, 5,
  5, 5, 5, 5, 5, 5, 5, 5,
  6, 5, 5, 5, 5, 5, 5, 6
};

//#define BITSCAN_MAGIC C64(0x07EDD5E59A4E28C2)
// X&-X gives the least significant bit because of two's complement encoding
// X&(!X+1) is equivalent to X&-X
// The bit is then run through the magic hashing scheme to index a database
//#define FirstOne(X) BitScanDatabase[(((X)&-(X))*BITSCAN_MAGIC)>>58]
//int BitScanDatabase[64];
// The initialization runs all possible inputs through the
// hashing scheme and places the correct data in the database.
//void initializeFirstOne(){
//    U64 bit = 1;
//    int i = 0;
//    do{
//        BitScanDatabase[(bit*BITSCAN_MAGIC)>>58] = i;
//        i++;
//        bit <<= 1;
//    }while(bit);
//}

U64 QMagicHash::m_rook_magic[64];
U64 QMagicHash::m_bishop_magic[64];
U64 QMagicHash::m_rook_moves[64][4096];
U64 QMagicHash::m_bishop_moves[64][512];

void QMagicHash::FillMagic(void){
  for(int i=0; i<64; i++){
    for(int j=0; j<512;  j++) m_bishop_moves[i][j] = index_to_u64(j,BBits[i],BishopMask(i));
    for(int j=0; j<4096; j++) m_rook_moves[i][j]   = index_to_u64(j,BBits[i],RookMask(i));
  }
  for(int i=0; i<64; i++){
    m_rook_magic[i]   = FindMagic(i,false);
    m_bishop_magic[i] = FindMagic(i,true);
  }
  return;
}

U64 QMagicHash::MagicRook(int sq){ return m_rook_magic[sq];}
U64 QMagicHash::MagicBishop(int sq){ return m_bishop_magic[sq];}
U64 QMagicHash::MagicRookMoves(const U64& occ, const U64& loc){return MagicRookMoves(occ,ffsll(loc));}
U64 QMagicHash::MagicRookMoves(const U64& occ, const int sq){
  return m_rook_moves[sq][Transform(occ,m_rook_magic[sq],RBits[sq])];
}
U64 QMagicHash::MagicBishopMoves(const U64& occ, const U64& loc){return MagicBishopMoves(occ,ffsll(loc));}
U64 QMagicHash::MagicBishopMoves(const U64& occ, const int sq){
  return m_bishop_moves[sq][Transform(occ,m_bishop_magic[sq],BBits[sq])];
}

QMagicHash::QMagicHash(void){}

//unsigned short QMagicHash::GetIndex(QBitBoard& a){
//  return (unsigned short) (a.Bits()*b)>>(64-s);
//}

U64 QMagicHash::RndmU64(void){
  U64 u1, u2, u3, u4;
  u1 = (U64)(random()) & 0xFFFF; u2 = (U64)(random()) & 0xFFFF;
  u3 = (U64)(random()) & 0xFFFF; u4 = (U64)(random()) & 0xFFFF;
  return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

U64 QMagicHash::RndmU64FewBits(void){
  return RndmU64() & RndmU64() & RndmU64();
}

U64 QMagicHash::index_to_u64(int index, int bits, QBitBoard m){
  int i, j;
  U64 result = 0ULL;
  for(i = 0; i < bits; i++) {
    j = m.PopFirst();
    if(index & (1 << i)) result |= (1ULL << j);
  }
  return result;
}

U64 QMagicHash::RookMask(int sq){
  U64 result = 0ULL;
  int rk = sq/8, fl = sq%8, r, f;
  for(r = rk+1; r <= 6; r++) result |= (1ULL << (fl + r*8));
  for(r = rk-1; r >= 1; r--) result |= (1ULL << (fl + r*8));
  for(f = fl+1; f <= 6; f++) result |= (1ULL << (f + rk*8));
  for(f = fl-1; f >= 1; f--) result |= (1ULL << (f + rk*8));
  return result;
}

U64 QMagicHash::BishopMask(int sq){
  U64 result = 0ULL;
  int rk = sq/8, fl = sq%8, r, f;
  for(r=rk+1, f=fl+1; r<=6 && f<=6; r++, f++) result |= (1ULL << (f + r*8));
  for(r=rk+1, f=fl-1; r<=6 && f>=1; r++, f--) result |= (1ULL << (f + r*8));
  for(r=rk-1, f=fl+1; r>=1 && f<=6; r--, f++) result |= (1ULL << (f + r*8));
  for(r=rk-1, f=fl-1; r>=1 && f>=1; r--, f--) result |= (1ULL << (f + r*8));
  return result;
}

U64 QMagicHash::RookAttacks(int sq,const U64& block){
  U64 result = 0ULL;
  int rk = sq/8, fl = sq%8, r, f;
  for(r = rk+1; r <= 7; r++) {
    result |= (1ULL << (fl + r*8));
    if(block & (1ULL << (fl + r*8))) break;
  }
  for(r = rk-1; r >= 0; r--) {
    result |= (1ULL << (fl + r*8));
    if(block & (1ULL << (fl + r*8))) break;
  }
  for(f = fl+1; f <= 7; f++) {
    result |= (1ULL << (f + rk*8));
    if(block & (1ULL << (f + rk*8))) break;
  }
  for(f = fl-1; f >= 0; f--) {
    result |= (1ULL << (f + rk*8));
    if(block & (1ULL << (f + rk*8))) break;
  }
  return result;
}

U64 QMagicHash::BishopAttacks(int sq,const U64& block){
  U64 result = 0ULL;
  int rk = sq/8, fl = sq%8, r, f;
  for(r = rk+1, f = fl+1; r <= 7 && f <= 7; r++, f++) {
    result |= (1ULL << (f + r*8));
    if(block & (1ULL << (f + r * 8))) break;
  }
  for(r = rk+1, f = fl-1; r <= 7 && f >= 0; r++, f--) {
    result |= (1ULL << (f + r*8));
    if(block & (1ULL << (f + r * 8))) break;
  }
  for(r = rk-1, f = fl+1; r >= 0 && f <= 7; r--, f++) {
    result |= (1ULL << (f + r*8));
    if(block & (1ULL << (f + r * 8))) break;
  }
  for(r = rk-1, f = fl-1; r >= 0 && f >= 0; r--, f--) {
    result |= (1ULL << (f + r*8));
    if(block & (1ULL << (f + r * 8))) break;
  }
  return result;
}

int QMagicHash::Transform(const U64& b, const U64& magic, int bits){
  return (int)((b * magic) >> (64 - bits));
}

U64 QMagicHash::FindMagic(int sq, bool IsBishop){
  QBitBoard mask(IsBishop ? BishopMask(sq) : RookMask(sq));
  const int n = mask.PopCount();
  const int size = 1 << n;
  U64 a[size];
  U64 used[size];
  U64 magic;
  const int m = IsBishop ? BBits[sq] : RBits[sq];
  int j, k;
  bool fail = false;

  for(int i=0; i<size; i++) a[i] = IsBishop ? BishopAttacks(sq, m_bishop_moves[sq][i]) : RookAttacks(sq, m_rook_moves[sq][i]);
  for(k = 0; k<1e7; k++){
    magic = RndmU64FewBits();
    QBitBoard bb((mask.Bits() * magic) & 0xFF00000000000000ULL);
    if(bb.PopCount() < 6) continue;
    for(int i = 0; i < size; i++) used[i] = 0ULL;
    for(int i = 0, fail = false; !fail && i < size; i++) {
      j = IsBishop ? Transform(m_bishop_moves[sq][i],magic,m) : Transform(m_rook_moves[sq][i],magic,m);
      if(used[j] == 0ULL) used[j] = a[i];
      else if(used[j] != a[i]) fail = true;
    }
    if(!fail) return magic;
  }
  cout << "***Failed***" << endl;
  return 0ULL;
}
