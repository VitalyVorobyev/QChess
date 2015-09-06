#include "qalphabeta.h"

QAlphaBeta::QAlphaBeta(void){}

double QAlphaBeta::AlphaBeta(double alpha, double beta, QPosition pos, int depth_left){
  if(depth_left == 0) return Quiesce(alpha,beta,pos);
  vector<QMove> moves = pos.FindMoves();
  const int NMov = moves.size();
  for(int i=0; i<NMov; i++){
    pos.MakeMove(moves[i]);
    const double score = -AlphaBeta(-beta,-alpha,pos,depth_left-1);
    if(score >= beta) return beta;
    if(score > alpha) alpha = score;
  }
  return alpha;
}

double QAlphaBeta::Quiesce(double alpha, double beta, QPosition pos){
  double stand_pat = pos.Evaluate();
  if(stand_pat >= beta) return beta;
  if(alpha < stand_pat) alpha = stand_pat;
  vector<QMove> moves = pos.FindMoves();
  vector<int> cap_ind = pos.Captures();
  const int NCap = cap_ind.size();
  for(int i=0; i<NCap; i++){
    pos.MakeMove(moves[cap_ind[i]]);
    const double score = -Quiesce(-beta,-alpha,pos);
    pos.UnmakeMove(moves[cap_ind[i]]);
    if(score >= beta) return beta;
    if(score > alpha) alpha = score;
  }
  return alpha;
}
