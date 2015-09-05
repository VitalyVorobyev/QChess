#ifndef QBITBOARD_H
#define QBITBOARD_H

#include <iostream>
using namespace std;

typedef unsigned long long U64;
typedef unsigned short U16;

//#define C64(x) x##ULL
//#define U64FULL C64(0xFFFFFFFFFFFFF)
//#define A2H2RAW C64(0xFF30)

class QBitBoard{
public:
  QBitBoard(void);
  QBitBoard(const U64 &bits);
  U64& Bits(void){return m_bits;}

  int PopCount(void);

  U64 FirstOne(void);
  int PopFirst(void);
  U64 Snoob(void);
  QBitBoard operator | (const QBitBoard& qbb);
  QBitBoard operator &(const QBitBoard& qbb);

  void Print(void);
private:
  U64 m_bits;
};

#endif // QBITBOARD_H
