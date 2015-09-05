#ifndef QMOVE_H
#define QMOVE_H

#include "qbitboard.h"

class QMove{
public:
  QMove(const U64& from, const U64& to, const short piece, const bool isblack, const short cpiece = -1);
  U64 From(void) const {return m_from;}
  U64 To(void) const {return m_to;}
  bool IsBlack(void) const {return m_IsBlack;}
  int Piece(void) const {return m_piece;}
  int CPiece(void) const {return m_cpiece;}

  void Print(void);
private:
  U64 m_from;
  U64 m_to;
  bool m_IsBlack;
  int m_piece;
  int m_cpiece;
};

#endif // QMOVE_H
