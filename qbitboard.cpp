#include "qbitboard.h"

QBitBoard::QBitBoard(void){
  m_bits = 0;
}

QBitBoard::QBitBoard(int bits){
  m_bits = bits;
}

QBitBoard::QBitBoard(U64& bits){
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
