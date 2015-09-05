#include "qbitboard.h"
#include "qlookup.h"
#include <bitset>

const int PopTable[64] = {
  63, 30, 3,  32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1,  54, 9,  57, 0,  35, 62, 31, 40, 4,  49, 5, 52,
  26, 60, 6,  23, 44, 46, 27, 56, 16, 7,  39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};

QBitBoard::QBitBoard(void){
  m_bits = 0;
}

//QBitBoard::QBitBoard(int bits){
//  m_bits = bits;
//}

QBitBoard::QBitBoard(const U64 &bits){
  m_bits = bits;
}

U64 QBitBoard::FirstOne(void){
  return m_bits & -m_bits;
}

U64 QBitBoard::Snoob(void){
  //Next bigger value with the same amount of 1-bits calculation
  const U64 smallest = FirstOne();
  const U64 ripple = m_bits + smallest;
  U64 ones = m_bits ^ ripple;
  ones = (ones >> 2)/smallest;
  return ripple | ones;
}

QBitBoard QBitBoard::operator |(const QBitBoard& qbb){
  return QBitBoard(this->m_bits | qbb.m_bits);
}

QBitBoard QBitBoard::operator &(const QBitBoard& qbb){
  return QBitBoard(this->m_bits & qbb.m_bits);
}

int QBitBoard::PopCount(void){
  int i;
  U64 bb = m_bits;
  for(i=0; bb; i++) bb &= bb-1;
  return i;
}

int QBitBoard::PopFirst(void){
  U64 b = m_bits ^ (m_bits - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  m_bits &= (m_bits - 1);
  return PopTable[(fold * 0x783a9b23) >> 26];
}

void QBitBoard::Print(void){
  U64 bb = m_bits;
//  cout << bitset<64>(bb) << endl;
  for(int i=0; i<8; i++){
    cout << bitset<8>(bb) << endl;
    bb >>= 8;
  }
  return;
}
