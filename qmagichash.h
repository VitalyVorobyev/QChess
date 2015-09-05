#ifndef QMAGICHASH_H
#define QMAGICHASH_H

#include "qbitboard.h"

class QMagicHash{
public:
  QMagicHash(void);
  static U64 FindMagic(int sq, bool IsBishop);
  static U64 MagicRook(int sq);
  static U64 MagicBishop(int sq);
  static U64 MagicRookMoves(const U64& occ, const U64& loc);
  static U64 MagicRookMoves(const U64& occ, const int sq);
  static U64 MagicBishopMoves(const U64& occ, const U64& loc);
  static U64 MagicBishopMoves(const U64& occ, const int sq);
  static void FillMagic(void);

private:
  static U64 RndmU64(void);
  static U64 RndmU64FewBits(void);
  static U64 index_to_u64(int index, int bits, QBitBoard m);
  static U64 RookMask(int sq);
  static U64 BishopMask(int sq);
  static U64 RookAttacks(int sq,const U64& block);
  static U64 BishopAttacks(int sq, const U64 &block);
  static int Transform(const U64& b, const U64& magic, int bits);

  static U64 m_rook_magic[64];
  static U64 m_bishop_magic[64];
  static U64 m_rook_moves[64][4096];
  static U64 m_bishop_moves[64][512];
};

#endif // QMAGICHASH_H
