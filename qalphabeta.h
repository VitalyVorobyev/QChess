#ifndef QALPHABETA_H
#define QALPHABETA_H

#include "qposition.h"

class QAlphaBeta{
public:
  QAlphaBeta(void);
  static double Evaluate(const QPosition& pos, const int depth) { return AlphaBeta(0,0,pos,depth);}

private:
  static double AlphaBeta(double alpha, double beta, QPosition pos, int depth_left);
  static double Quiesce(double alpha, double beta, QPosition pos);
};

#endif // QALPHABETA_H
