#include "qmove.h"

QMove::QMove(const U64& from, const U64& to, const short piece, const bool isblack, const short cpiece){
  m_from = from;
  m_to = to;
  m_piece = piece;
  m_cpiece = cpiece;
  m_IsBlack = isblack;
}

void QMove::Print(void){
  QBitBoard from(m_from);
  QBitBoard to(m_to);
  cout << "From:" << endl;
  from.Print();
  cout << "To:" << endl;
  to.Print();
  cout << "Piece: " << m_piece << ", cPiece: " << m_cpiece;
  if(m_IsBlack) cout << " (black)";
  else          cout << " (white)";
  cout << endl;
  return;
}
