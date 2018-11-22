//
//  GameTree.hpp
//  Kalah game
//
//  Created by HARSH H PATNI on 11/22/18.
//  Copyright © 2018 HARSH H PATNI. All rights reserved.
//

#ifndef GameTree_hpp
#define GameTree_hpp

#include <stdio.h>
#include<iostream>
#include"KalahBoard.hpp"
using namespace std;

class GameTree
{
public:
    int heuristic_value;
    char player;
    KalahBoard board_status;
    int number_of_children;
    GameTree *children[6];
    
    GameTree();
    GameTree(char);
    void create_node(char);
    void set_heuristic_value(int);
    void add_all_children();
    bool deepenough(int);
    void print(GameTree *,int);
    int evaluation();
    int get_hole_number();
    void copyBoardStatus(KalahBoard kb);
};


#endif /* GameTree_hpp */
