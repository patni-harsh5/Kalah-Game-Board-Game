//
//  KalahBoard.hpp
//  Kalah game
//
//  Created by HARSH H PATNI on 11/22/18.
//  Copyright © 2018 HARSH H PATNI. All rights reserved.
//

#ifndef KalahBoard_hpp
#define KalahBoard_hpp

#include <stdio.h>
#include<iostream>
using namespace std;

class KalahBoard
{
public:
    int A[6],B[6];
    int kalah_A,kalah_B;
    int winDecider,numberOfSlots;
    int *ptr;
    
    KalahBoard();
    KalahBoard(int[],int[],int,int);
    KalahBoard(KalahBoard *);
    char move_A(int);
    char move_B(int);
    char move(int,char);
    // int evaluation();
    char checkWin();
    void operator=(KalahBoard);
    void displayBoard();
    bool checkLegealMove(char player,int hole);
};


#endif /* KalahBoard_hpp */
