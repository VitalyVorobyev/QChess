#ifndef QLOOKUP_H
#define QLOOKUP_H

// Magin BitBoard stuff is taken from
// "Understanding magic bitboards in chess programming" by CHRIS MORETON on AUGUST 7, 2013
// http://www.afewmorelines.com/understanding-magic-bitboards-in-chess-programming/

#include "qbitboard.h"

#define FILE_A 0
#define FILE_B 1
#define FILE_C 2
#define FILE_D 3
#define FILE_E 4
#define FILE_F 5
#define FILE_G 6
#define FILE_H 7

#define RANK_1 0
#define RANK_2 1
#define RANK_3 2
#define RANK_4 3
#define RANK_5 4
#define RANK_6 5
#define RANK_7 6
#define RANK_8 7

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


const U64 MaskRank[8]  ={0x00000000000000FF,
                         0x000000000000FF00,
                         0x0000000000FF0000,
                         0x00000000FF000000,
                         0x000000FF00000000,
                         0x0000FF0000000000,
                         0x00FF000000000000,
                         0xFF00000000000000};

const U64 ClearRank[8] ={0xFFFFFFFFFFFFFF00,
                         0xFFFFFFFFFFFF00FF,
                         0xFFFFFFFFFF00FFFF,
                         0xFFFFFFFF00FFFFFF,
                         0xFFFFFF00FFFFFFFF,
                         0xFFFF00FFFFFFFFFF,
                         0xFF00FFFFFFFFFFFF,
                         0x00FFFFFFFFFFFFFF};

const U64 MaskFile[8]  ={0b1000000010000000100000001000000010000000100000001000000010000000,
                         0b0100000001000000010000000100000001000000010000000100000001000000,
                         0b0010000000100000001000000010000000100000001000000010000000100000,
                         0b0001000000010000000100000001000000010000000100000001000000010000,
                         0b0000100000001000000010000000100000001000000010000000100000001000,
                         0b0000010000000100000001000000010000000100000001000000010000000100,
                         0b0000001000000010000000100000001000000010000000100000001000000010,
                         0b0000000100000001000000010000000100000001000000010000000100000001};

const U64 ClearFile[8] ={0b0111111101111111011111110111111101111111011111110111111101111111,
                         0b1011111110111111101111111011111110111111101111111011111110111111,
                         0b1101111111011111110111111101111111011111110111111101111111011111,
                         0b1110111111101111111011111110111111101111111011111110111111101111,
                         0b1111011111110111111101111111011111110111111101111111011111110111,
                         0b1111101111111011111110111111101111111011111110111111101111111011,
                         0b1111110111111101111111011111110111111101111111011111110111111101,
                         0b1111111011111110111111101111111011111110111111101111111011111110};

const U64 Piece[64] = {0x0000000000000001,0x0000000000000002,0x0000000000000004,0x0000000000000008,0x0000000000000010,0x0000000000000020,0x0000000000000040,0x0000000000000080,0x0000000000000100,0x0000000000000200,0x0000000000000400,0x0000000000000800,0x0000000000001000,0x0000000000002000,0x0000000000004000,0x0000000000008000,0x0000000000010000,0x0000000000020000,0x0000000000040000,0x0000000000080000,0x0000000000100000,0x0000000000200000,0x0000000000400000,0x0000000000800000,0x0000000001000000,0x0000000002000000,0x0000000004000000,0x0000000008000000,0x0000000010000000,0x0000000020000000,0x0000000040000000,0x0000000080000000,0x0000000100000000,0x0000000200000000,0x0000000400000000,0x0000000800000000,0x0000001000000000,0x0000002000000000,0x0000004000000000,0x0000008000000000,0x0000010000000000,0x0000020000000000,0x0000040000000000,0x0000080000000000,0x0000100000000000,0x0000200000000000,0x0000400000000000,0x0000800000000000,0x0001000000000000,0x0002000000000000,0x0004000000000000,0x0008000000000000,0x0010000000000000,0x0020000000000000,0x0040000000000000,0x0080000000000000,0x0100000000000000,0x0200000000000000,0x0400000000000000,0x0800000000000000,0x1000000000000000,0x2000000000000000,0x4000000000000000,0x8000000000000000};
const U64 magicNumberRook[64]    = {0xa180022080400230L,0x40100040022000L,0x80088020001002L,0x80080280841000L, 0x4200042010460008L, 0x4800a0003040080L, 0x400110082041008L, 0x8000a041000880L, 0x10138001a080c010L, 0x804008200480L, 0x10011012000c0L, 0x22004128102200L, 0x200081201200cL, 0x202a001048460004L, 0x81000100420004L, 0x4000800380004500L, 0x208002904001L, 0x90004040026008L, 0x208808010002001L, 0x2002020020704940L, 0x8048010008110005L, 0x6820808004002200L, 0xa80040008023011L, 0xb1460000811044L, 0x4204400080008ea0L, 0xb002400180200184L, 0x2020200080100380L, 0x10080080100080L, 0x2204080080800400L, 0xa40080360080L, 0x2040604002810b1L, 0x8c218600004104L, 0x8180004000402000L, 0x488c402000401001L, 0x4018a00080801004L, 0x1230002105001008L, 0x8904800800800400L, 0x42000c42003810L, 0x8408110400b012L, 0x18086182000401L, 0x2240088020c28000L, 0x1001201040c004L, 0xa02008010420020L, 0x10003009010060L, 0x4008008008014L, 0x80020004008080L, 0x282020001008080L, 0x50000181204a0004L, 0x102042111804200L, 0x40002010004001c0L, 0x19220045508200L, 0x20030010060a900L, 0x8018028040080L, 0x88240002008080L, 0x10301802830400L, 0x332a4081140200L, 0x8080010a601241L, 0x1008010400021L,0x4082001007241L,0x211009001200509L,0x8015001002441801L,0x801000804000603L,0xc0900220024a401L,0x1000200608243L};
const U64 magicNumberBishop[64]  = {0x2910054208004104L,0x2100630a7020180L,0x5822022042000000L,0x2ca804a100200020L,0x204042200000900L,0x2002121024000002L, 0x80404104202000e8L, 0x812a020205010840L, 0x8005181184080048L, 0x1001c20208010101L, 0x1001080204002100L, 0x1810080489021800L, 0x62040420010a00L, 0x5028043004300020L, 0xc0080a4402605002L, 0x8a00a0104220200L, 0x940000410821212L, 0x1808024a280210L, 0x40c0422080a0598L, 0x4228020082004050L, 0x200800400e00100L, 0x20b001230021040L, 0x90a0201900c00L, 0x4940120a0a0108L, 0x20208050a42180L, 0x1004804b280200L, 0x2048020024040010L, 0x102c04004010200L, 0x20408204c002010L, 0x2411100020080c1L, 0x102a008084042100L, 0x941030000a09846L, 0x244100800400200L, 0x4000901010080696L, 0x280404180020L, 0x800042008240100L, 0x220008400088020L, 0x4020182000904c9L, 0x23010400020600L, 0x41040020110302L, 0x412101004020818L, 0x8022080a09404208L, 0x1401210240484800L, 0x22244208010080L, 0x1105040104000210L, 0x2040088800c40081L, 0x8184810252000400L, 0x4004610041002200L, 0x40201a444400810L, 0x4611010802020008L, 0x80000b0401040402L, 0x20004821880a00L, 0x8200002022440100L, 0x9431801010068L, 0x1040c20806108040L, 0x804901403022a40L, 0x2400202602104000L, 0x208520209440204L, 0x40c000022013020L, 0x2000104000420600L, 0x400000260142410L,0x800633408100500L,0x2404080a1410L,0x138200122002900L};
const U64 occupancyMaskRook[64]  = {0x101010101017eL, 0x202020202027cL, 0x404040404047aL, 0x8080808080876L, 0x1010101010106eL, 0x2020202020205eL, 0x4040404040403eL, 0x8080808080807eL, 0x1010101017e00L, 0x2020202027c00L, 0x4040404047a00L, 0x8080808087600L, 0x10101010106e00L, 0x20202020205e00L, 0x40404040403e00L, 0x80808080807e00L, 0x10101017e0100L, 0x20202027c0200L, 0x40404047a0400L, 0x8080808760800L, 0x101010106e1000L, 0x202020205e2000L, 0x404040403e4000L, 0x808080807e8000L, 0x101017e010100L, 0x202027c020200L, 0x404047a040400L, 0x8080876080800L, 0x1010106e101000L, 0x2020205e202000L, 0x4040403e404000L, 0x8080807e808000L, 0x1017e01010100L, 0x2027c02020200L, 0x4047a04040400L, 0x8087608080800L, 0x10106e10101000L, 0x20205e20202000L, 0x40403e40404000L, 0x80807e80808000L, 0x17e0101010100L, 0x27c0202020200L, 0x47a0404040400L, 0x8760808080800L, 0x106e1010101000L, 0x205e2020202000L, 0x403e4040404000L, 0x807e8080808000L, 0x7e010101010100L, 0x7c020202020200L, 0x7a040404040400L, 0x76080808080800L, 0x6e101010101000L, 0x5e202020202000L, 0x3e404040404000L, 0x7e808080808000L, 0x7e01010101010100L, 0x7c02020202020200L, 0x7a04040404040400L, 0x7608080808080800L, 0x6e10101010101000L, 0x5e20202020202000L, 0x3e40404040404000L, 0x7e80808080808000L};
const U64 ccupancyMaskBishop[64] = {0x40201008040200L, 0x402010080400L, 0x4020100a00L, 0x40221400L, 0x2442800L, 0x204085000L, 0x20408102000L, 0x2040810204000L, 0x20100804020000L, 0x40201008040000L, 0x4020100a0000L, 0x4022140000L, 0x244280000L, 0x20408500000L, 0x2040810200000L, 0x4081020400000L, 0x10080402000200L, 0x20100804000400L, 0x4020100a000a00L, 0x402214001400L, 0x24428002800L, 0x2040850005000L, 0x4081020002000L, 0x8102040004000L, 0x8040200020400L, 0x10080400040800L, 0x20100a000a1000L, 0x40221400142200L, 0x2442800284400L, 0x4085000500800L, 0x8102000201000L, 0x10204000402000L, 0x4020002040800L, 0x8040004081000L, 0x100a000a102000L, 0x22140014224000L, 0x44280028440200L, 0x8500050080400L, 0x10200020100800L, 0x20400040201000L, 0x2000204081000L, 0x4000408102000L, 0xa000a10204000L, 0x14001422400000L, 0x28002844020000L, 0x50005008040200L, 0x20002010080400L, 0x40004020100800L, 0x20408102000L, 0x40810204000L, 0xa1020400000L, 0x142240000000L, 0x284402000000L, 0x500804020000L, 0x201008040200L, 0x402010080400L, 0x2040810204000L, 0x4081020400000L, 0xa102040000000L, 0x14224000000000L, 0x28440200000000L, 0x50080402000000L, 0x20100804020000L, 0x40201008040200L};
const int magicNumberShiftsRook[64]   = {52,53,53,53,53,53,53,52,53,54,54,54,54,54,54,53,
                                         53,54,54,54,54,54,54,53,53,54,54,54,54,54,54,53,
                                         53,54,54,54,54,54,54,53,53,54,54,54,54,54,54,53,
                                         53,54,54,54,54,54,54,53,52,53,53,53,53,53,53,52};
const int magicNumberShiftsBishop[64] = {58,59,59,59,59,59,59,58,59,59,59,59,59,59,59,59,
                                         59,59,57,57,57,57,59,59,59,59,57,55,55,57,59,59,
                                         59,59,57,55,55,57,59,59,59,59,57,57,57,57,59,59,
                                         59,59,59,59,59,59,59,59,58,59,59,59,59,59,59,58};

inline U64 soutOne(const U64& x) {return x >> 8;}
inline U64 nortOne(const U64& x) {return x << 8;}
inline U64 eastOne(const U64& x) {return (x << 1) & ClearFile[FILE_A];}
inline U64 noEaOne(const U64& x) {return (x << 9) & ClearFile[FILE_A];}
inline U64 soEaOne(const U64& x) {return (x >> 7) & ClearFile[FILE_A];}
inline U64 westOne(const U64& x) {return (x >> 1) & ClearFile[FILE_H];}
inline U64 soWeOne(const U64& x) {return (x >> 9) & ClearFile[FILE_H];}
inline U64 noWeOne(const U64& x) {return (x << 7) & ClearFile[FILE_H];}
inline U64 rotateLeft(const U64& x, const int s)  {return (x << s) | (x >> (64-s));}
inline U64 rotateRight(const U64& x, const int s) {return (x >> s) | (x << (64-s));}

void PrintLookUpTables(void){
  cout << "WhitePawns: " << WhitePawns << endl;
  return;
}

int FirstNonZeroIndex(const U64& bb){
  int i=0;
  while(bb){ i++; bb >>= 1;}
  return i;
}

void generateOccupancyMasks(U64 occMaskRook[], U64 occMaskBishop[]){
  int i;
  U64 mask;
  for(int bitRef=0; bitRef<=63; bitRef++){
    mask = 0;
    for(i=bitRef+8; i<=55; i+=8)                   mask |= (1L << i);
    for(i=bitRef-8; i>=8;  i-=8)                   mask |= (1L << i);
    for(i=bitRef+1; i%8!=7 && i%8!=0; i++)         mask |= (1L << i);
    for(i=bitRef-1; i%8!=7 && i%8!=0 && i>=0; i--) mask |= (1L << i);
    occMaskRook[bitRef] = mask;

    mask = 0;
    for(i=bitRef+9; i%8!=7 && i%8!=0 && i<=55; i+=9) mask |= (1L << i);
    for(i=bitRef-9; i%8!=7 && i%8!=0 && i>=8;  i-=9) mask |= (1L << i);
    for(i=bitRef+7; i%8!=7 && i%8!=0 && i<=55; i+=7) mask |= (1L << i);
    for(i=bitRef-7; i%8!=7 && i%8!=0 && i>=8;  i-=7) mask |= (1L << i);
    occMaskBishop[bitRef] = mask;
  }
  return;
}

vector<U64> occupancyVariation[64];
vector<U64> occupancyAttackSet[64];
vector<U64> magicMovesRook[64];
vector<U64> magicMovesBishop[64];

void generateOccupancyVariations(const bool isRook){
  int i, j, bitRef;
  U64 mask;
  int variationCount;
  int setBitsInMask[64], setBitsInIndex[64];
  int bitCount[64];

  for(bitRef=0; bitRef<=63; bitRef++){
    mask = isRook ? occupancyMaskRook[bitRef] : occupancyMaskBishop[bitRef];
    setBitsInMask = Bitboards.getSetBits(mask);
    bitCount[bitRef] = Bitboards.countSetBits(mask);
    variationCount = (int)(1L << bitCount[bitRef]);
    for(i=0; i<variationCount; i++){
      occupancyVariation[bitRef][i] = 0;
      // find bits set in index "i" and map them to bits in the 64 bit "occupancyVariation"
      setBitsInIndex = Bitboards.getSetBits(i); // an array of integers showing which bits are set
      for(j=0; setBitsInIndex[j] != -1; j++){
        occupancyVariation[bitRef][i] |= (1L << setBitsInMask[setBitsInIndex[j]]);
      }

      if(isRook){
        for (j=bitRef+8; j<=55 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j+=8);
        if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
        for (j=bitRef-8; j>=8  && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j-=8);
        if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
        for (j=bitRef+1; j%8!=7 && j%8!=0 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j++);
        if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
        for (j=bitRef-1; j%8!=7 && j%8!=0 && j>=0 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j--);
        if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
      } else{
        for (j=bitRef+9; j%8!=7 && j%8!=0 && j<=55 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j+=9);
        if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
        for (j=bitRef-9; j%8!=7 && j%8!=0 && j>=8  && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j-=9);
        if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
        for (j=bitRef+7; j%8!=7 && j%8!=0 && j<=55 && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j+=7);
        if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
        for (j=bitRef-7; j%8!=7 && j%8!=0 && j>=8  && (occupancyVariation[bitRef][i] & (1L << j)) == 0; j-=7);
        if (j>=0 && j<=63) occupancyAttackSet[bitRef][i] |= (1L << j);
      }
    }
  }
}

void generateMagicNumbers(const bool isRook){
  int i, j, bitRef, variationCount;

  Random r = new Random();
  U64 magicNumber = 0;
  int index;
  U64 attackSet;

  for(bitRef=0; bitRef<=63; bitRef++){
    int bitCount = Bitboards.countSetBits(isRook ? occupancyMaskRook[bitRef] : occupancyMaskBishop[bitRef]);
    variationCount = (int)(1L << bitCount);
    boolean fail;
    long usedBy[] = new long[(int)(1L << bitCount)];

    int attempts = 0;

    do{
      magicNumber = r.nextLong() & r.nextLong() & r.nextLong(); // generate a random number with not many bits set
      for (j=0; j<variationCount; j++) usedBy[j] = 0;
      attempts++;

      for (i=0, fail=false; i<variationCount && !fail; i++){
        index = (int)((occupancyVariation[bitRef][i] * magicNumber) >> (64-bitCount));

        // fail if this index is used by an attack set that is incorrect for this occupancy variation
        fail = usedBy[index] != 0 && usedBy[index] != occupancyAttackSet[bitRef][i];

        usedBy[index] = attackSet;
      }
    } while(fail);
    if(isRook){
      magicNumberRook[bitRef] = magicNumber;
      magicNumberShiftsRook[bitRef] = (64-bitCount);
    } else{
      magicNumberBishop[bitRef] = magicNumber;
      magicNumberShiftsBishop[bitRef] = (64-bitCount);
    }
  }
  return;
}

void generateMoveDatabase(const bool isRook){
  U64 validMoves;
  int variations, bitCount;
  int bitRef, i, j, magicIndex;

  for(bitRef=0; bitRef<=63; bitRef++){
    bitCount = isRook ? Bitboards.countSetBits(occupancyMaskRook[bitRef]) : Bitboards.countSetBits(occupancyMaskBishop[bitRef]);
    variations = (int)(1L << bitCount);

    for(i=0; i<variations; i++){
      validMoves = 0;
      if(isRook){
        magicIndex = (int)((occupancyVariation[bitRef][i] * magicNumberRook[bitRef]) >> magicNumberShiftsRook[bitRef]);

        for(j=bitRef+8; j<=63; j+=8)         {validMoves |= (1L << j); if((occupancyVariation[bitRef][i] & (1L << j)) != 0) break; }
        for(j=bitRef-8; j>=0; j-=8)          {validMoves |= (1L << j); if((occupancyVariation[bitRef][i] & (1L << j)) != 0) break; }
        for(j=bitRef+1; j%8!=0; j++)         {validMoves |= (1L << j); if((occupancyVariation[bitRef][i] & (1L << j)) != 0) break; }
        for(j=bitRef-1; j%8!=7 && j>=0; j--) {validMoves |= (1L << j); if((occupancyVariation[bitRef][i] & (1L << j)) != 0) break; }

        magicMovesRook[bitRef][magicIndex] = validMoves;
      } else{
        magicIndex = (int)((occupancyVariation[bitRef][i] * magicNumberBishop[bitRef]) >> magicNumberShiftsBishop[bitRef]);

        for(j=bitRef+9; j%8!=0 && j<=63; j+=9){ validMoves |= (1L << j); if ((occupancyVariation[bitRef][i] & (1L << j)) != 0) break; }
        for(j=bitRef-9; j%8!=7 && j>=0; j-=9){ validMoves |= (1L << j); if ((occupancyVariation[bitRef][i] & (1L << j)) != 0) break; }
        for(j=bitRef+7; j%8!=7 && j<=63; j+=7){
          validMoves |= (1L << j);
          if((occupancyVariation[bitRef][i] & (1L << j)) != 0) break;
        }
        for(j=bitRef-7; j%8!=0 && j>=0; j-=7){
          validMoves |= (1L << j);
          if((occupancyVariation[bitRef][i] & (1L << j)) != 0) break;
        }
        magicMovesBishop[bitRef][magicIndex] = validMoves;
      }
    }
  }
  return;
}

#endif // QLOOKUP_H
