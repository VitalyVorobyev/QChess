#include "qmove.h"

QMove::QMove(const U64& from,const U64& to,const int piece, const bool isblack, const int cpiece){
  m_from = from;
  m_to = to;
  m_piece = piece;
  m_cpiece = cpiece;
  m_IsBlack = isblack;
}
