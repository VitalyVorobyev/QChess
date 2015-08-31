#ifndef QMAGICHASH_H
#define QMAGICHASH_H

#include "qbitboard.h"

class QMagicHash{
public:
  QMagicHash();
  unsigned short GetIndex(QBitBoard& a);
  unsigned short LSBScan(QBitBoard& a);

private:
  unsigned short s;
  U64 b;
};

#endif // QMAGICHASH_H
