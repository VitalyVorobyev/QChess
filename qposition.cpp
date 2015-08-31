#include "qposition.h"

QPosition::QPosition()
{
    bpowns = QBitBoard(0);
    bknights = QBitBoard(0);
    bbishops = QBitBoard(0);
    brocks = QBitBoard(0);
    bquins = QBitBoard(0);
    bking = QBitBoard(0);

    wpowns = QBitBoard(0);
    wknights = QBitBoard(0);
    wbishops = QBitBoard(0);
    wrocks = QBitBoard(0);
    wquins = QBitBoard(0);
    wking = QBitBoard(0);

    boccupancy = QBitBoard(0);
    woccupancy = QBitBoard(0);
}

void QPosition::SetBOcc(){
    boccupancy = QBitBoard((U64) bpowns.Bits() | bknights.Bits() | bbishops.Bits() | brocks.Bits() | bquins.Bits() | bking.Bits());
}

void QPosition::SetWOcc(){
    woccupancy = QBitBoard((U64) wpowns.Bits() | wknights.Bits() | wbishops.Bits() | wrocks.Bits() | wquins.Bits() | wking.Bits());
}

void QPosition::SetOcc(){
    SetWOcc();
    SetBOcc();
}

int QPosition::MakeMove(const QBitBoard& from,const QBitBoard& to,const int ind){
    if(turnFlag){// black's move
        if(!(from.Bits() & boccupancy.Bits())) return -1; // There is no black piece on this square
        if(to.Bits() & boccupancy.Bits()) return -2; // There is
    }
}
