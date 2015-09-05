#include <QApplication>
#include "mainwindow.h"
#include "qmagichash.h"
#include "qposition.h"

int main(int argc, char *argv[]){
  QPosition pos;
  pos.SetInitialPosition();
//  pos.PrintAttacks();
  pos.FindWMoves();
  vector<QMove> moves = pos.Moves();
  for(int i=0; i<(int)moves.size(); i++) moves[i].Print();

//  QMagicHash::FillMagic();
//  cout << "Hello, Qt!" << endl;
//  cout << "Size of U64 = " << sizeof(unsigned long long) << endl;
//  for(int i=0; i<64; i++){
//    QBitBoard rbb(QMagicHash::MagicRook(i));
//    QBitBoard bbb(QMagicHash::MagicBishop(i));
//    cout << i+1 << endl;
//    cout << " rook: " << endl;
//    rbb.Print();
//    cout << " bishop: " << endl;
//    bbb.Print();
//  }
  return 0;
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
