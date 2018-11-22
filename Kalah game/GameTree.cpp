//
//  GameTree.cpp
//  Kalah game
//
//  Created by HARSH H PATNI on 11/22/18.
//  Copyright © 2018 HARSH H PATNI. All rights reserved.
//

#include "GameTree.hpp"
#include <cstdlib>
#include <ctime>
using namespace std;
//extern int  ALGO_FLAG;

extern int nodes_generated,nodes_expanded,steps;

GameTree::GameTree()
{
    heuristic_value = -1000;
    player='n';
    number_of_children = 0;
    for(int i=0;i<6;i++)
    {
        children[i] = NULL;
    }
}

GameTree::GameTree(char p)
{
    player = p;
    heuristic_value = -1000;
    number_of_children = 0;
    for(int i=0;i<6;i++)
    {
        children[i] = NULL;
    }
}

void GameTree::create_node(char p)
{
    children[number_of_children++]=new GameTree(p);
}

void GameTree::set_heuristic_value(int value)
{
    heuristic_value = value;
}

void GameTree::add_all_children()
{
    char p = (player == 'A') ? 'B' : 'A';
    for(int i=0;i<6;i++)
    {
        number_of_children++;
        children[i]=new GameTree(p);
        if(this->board_status.A[i]!=0 && player == 'A')
            children[i]->board_status = this->board_status;
        else if(this->board_status.B[i]!=0 && player == 'B')
            children[i]->board_status = this->board_status;
        else
            children[i] = NULL;
        if(children[i]!=NULL)
        {
            nodes_generated++;
            children[i]->board_status.move(i,children[i]->player);
        }
        
    }
}

bool GameTree::deepenough(int depth)
{
    if(heuristic_value != -1000)
        return heuristic_value;
    if(depth >= 3 || board_status.checkWin() != 'N' )//if the depth is greater than 3 or a player has won the game then it is deep enough.
    {
        return true;
    }
    else
    {
        nodes_expanded++;
        add_all_children();
        return false;
    }
}

void GameTree::print(GameTree *node,int nestLevel)
{
    cout<<node->player<<":"<<node->heuristic_value<<endl;
    int i, j;
    for (i = 0; node->children[i] != NULL && i < 6; i++)
    {
        for (j = 0; j < nestLevel; j++)
            cout<<"\t";
        print(node->children[i], nestLevel + 1);
    }
}

int GameTree::get_hole_number()
{
    for(int i=0;i<6;i++)
    {
        if(children[i] == NULL)
            continue;
        if(children[i]->heuristic_value == heuristic_value)
        {
            cout<<"hole #"<<i;
            return i;
        }
    }
    return -1;
}

int GameTree::evaluation()
{
    int value;
    if(player == 'A')
    {
        int a_stones = 0;
        for(int i = 0 ; i < 6 ; i++)
        {
            if(board_status.A[i] == 0)
                a_stones++;
        }
        if(a_stones == 6)
            value = 1000;
    }
    else if(player == 'B')
    {
        int b_stones = 0;
        for(int i = 0 ; i < 6 ; i++)
        {
            if(board_status.B[i] == 0)
                b_stones++;
        }
        if(b_stones == 6)
            value = -1000;
    }
    set_heuristic_value(value);
    return value;
}

void GameTree::copyBoardStatus(KalahBoard kb)
{
    for(int i=0;i<6;i++)
    {
        this->board_status.A[i]=kb.A[i];
        this->board_status.B[i]=kb.B[i];
    }
    this->board_status.kalah_A=kb.kalah_A;
    this->board_status.kalah_B=kb.kalah_B;
}

