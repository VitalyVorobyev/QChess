#include "qmagichash.h"

#define BITSCAN_MAGIC C64(0x07EDD5E59A4E28C2)
// X&-X gives the least significant bit because of two's complement encoding
// X&(!X+1) is equivalent to X&-X
// The bit is then run through the magic hashing scheme to index a database
#define FirstOne(X) BitScanDatabase[(((X)&-(X))*BITSCAN_MAGIC)>>58]
int BitScanDatabase[64];
// The initialization runs all possible inputs through the
// hashing scheme and places the correct data in the database.

void initializeFirstOne(){
    U64 bit = 1;
    int i = 0;
    do{
        BitScanDatabase[(bit*BITSCAN_MAGIC)>>58] = i;
        i++;
        bit <<= 1;
    }while(bit);
}

QMagicHash::QMagicHash(){
}

unsigned short QMagicHash::GetIndex(QBitBoard& a){
  return (unsigned short) (a.Bits()*b)>>(64-s);
}

unsigned short LSBScan(QBitBoard& a){
  return 0;
}
