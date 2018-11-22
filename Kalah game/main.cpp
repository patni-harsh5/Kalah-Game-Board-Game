//
//  main.cpp
//  Kalah game
//
//  Created by HARSH H PATNI on 11/22/18.
//  Copyright © 2018 HARSH H PATNI. All rights reserved.
//

#include<iostream>
#include<ctime>
#include "GameTree.hpp"
#include "KalahBoard.hpp"
#include "AlphaBetaSearch.hpp"
#include "MinMaxAB.hpp"

using namespace std;


void print(char,int);

int nodes_generated,nodes_expanded,steps;

void MinMax()
{
    KalahBoard *kb = new KalahBoard();
    cout << "Initial board " << endl;
    kb->displayBoard();
    char win = kb->checkWin();
    char player ='A';
    int start_s = clock();
    while(win == 'N')
    {
        steps++;
        GameTree *head = new GameTree(player);
        head->copyBoardStatus( kb);
        cout << "*****Turn*****" << player << endl;
        MinMaxAB(head,0,player,10000,-10000);
        int hole = head->heuristic_value;
        cout<< "hole # "<<hole<<endl;
        player = kb->move(hole,player);
        kb->displayBoard();
        win = kb->checkWin();
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    kb->displayBoard();
    print(win,execution_time);
    
}

void AlphaBeta()
{
    KalahBoard *kb = new KalahBoard();
    cout << "Initial board " << endl;
    kb->displayBoard();
    char win = kb->checkWin();
    char player = 'A';
    int start_s = clock();
    while(win == 'N')
    {
        steps++;
        GameTree *head = new GameTree(player);
        head->copyBoardStatus(kb);
        cout << "*****Turn*****" << player << endl;
        alphabeta(head,0,player,1000,-1000);
        int hole = head->get_hole_number();
        player = kb->move(hole,player);
        //cout << "The index of the board " << obj.value << endl;
        //cout << "The board with the new position " << endl;
        kb->displayBoard();
        win = kb->checkWin();
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    kb->displayBoard();
    print(win,execution_time);
}

void UserVsSystem()
{
    int choice;
    KalahBoard *kb = new KalahBoard();
    cout << "Initial board " << endl;
    kb->displayBoard();
    char win = kb->checkWin();
    char player = 'A';
    cout << "Enter 1 for MinMaxAB " << endl;
    cout << "Enter 2 for AlphaBeta " << endl;
    cin >> choice;
    int start_s = clock();
    while(win == 'N')
    {
        steps++;
        GameTree *head = new GameTree(player);
        head->copyBoardStatus(kb);
        cout << "*****Turn*****" << player << endl;
        if(player == 'A')
        {
            int hole;
            cout << "Enter the A hole number " << endl;
            cin >> hole;
            while(!kb->checkLegealMove(player,hole))
            {
                cout<<"Illegal move, choose another hole"<<endl;
                cout << "Enter the A hole number :" << endl;
                cin >> hole;
            }
            player = kb->move(hole,player);
        }
        else if(player == 'B' && choice == 1)
        {
            MinMaxAB(head,0,player,1000,-1000);
            int hole = head->heuristic_value;
            cout<< "hole # "<<hole<<endl;
            player = kb->move(hole,player);
        }
        else if(player == 'B' && choice == 2)
        {
            alphabeta(head,0,player,1000,-1000);
            int hole = head->get_hole_number();
            player = kb->move(hole,player);
        }
        kb->displayBoard();
        win = kb->checkWin();
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    kb->displayBoard();
    print(win,execution_time);
}

void UserVsUser()
{
    KalahBoard *kb = new KalahBoard();
    cout << "Initial board " << endl;
    kb->displayBoard();
    char win = kb->checkWin();
    char player = 'A';
    int start_s = clock();
    while(win == 'N')
    {
        steps++;
        cout << "*****Turn*****" << player << endl;
        if(player == 'A')
        {
            int hole;
            cout << "Enter the A hole number :" << endl;
            cin >> hole;
            while(!kb->checkLegealMove(player, hole))
            {
                cout<<"Illegal move, choose another hole"<<endl;
                cout << "Enter the A hole number :" << endl;
                cin >> hole;
            }
            player = kb->move(hole,player);
        }
        else if(player == 'B')
        {
            int hole;
            cout << "Enter the B hole number :" << endl;
            cin >> hole;
            while(!kb->checkLegealMove(player, hole))
            {
                cout<<"Illegal move, choose another hole"<<endl;
                cout << "Enter the B hole number :" << endl;
                cin >> hole;
            }
            player = kb->move(hole,player);
        }
        kb->displayBoard();
        win = kb->checkWin();
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    kb->displayBoard();
    print(win,execution_time);
}

void MinMaxVsAlphaBeta()
{
    KalahBoard *kb = new KalahBoard();
    cout << "Initial board " << endl;
    kb->displayBoard();
    char win = kb->checkWin();
    char player = 'A';
    int start_s = clock();
    while(win == 'N')
    {
        steps++;
        GameTree *head = new GameTree(player);
        head->copyBoardStatus(kb);
        cout << "*****Turn*****" << player << endl;
        if(player == 'A')
        {
            MinMaxAB(head,0,player,1000,-1000);
            int hole = head->heuristic_value;
            cout<< "hole # "<<hole<<endl;
            player = kb->move(hole,player);
        }
        else if(player == 'B')
        {
            alphabeta(head,0,player,1000,-1000);
            int hole = head->get_hole_number();
            player = kb->move(hole,player);
        }
        kb->displayBoard();
        win = kb->checkWin();
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    kb->displayBoard();
    print(win,execution_time);
}

void print(char win,int execution_time)
{
    cout << "The result of the game is : " <<win<< endl;
    cout << endl;
    
    if(win == 'A')
        cout << "Player A won! Congrats " << endl;
    else if(win == 'B')
        cout << "Player B won! Congrats " << endl;
    else if(win == 'T')
        cout << "Game tied!! " << endl;
    
    cout <<"\n\t\t\tGame Ends-*\n" << endl;
    
    cout << "Execution time taken is : " << (execution_time)/double(CLOCKS_PER_SEC)*1000 << " seconds" << endl;
}

void Statistics_print()
{
    cout << "Number of nodes generated : " << nodes_generated << endl;
    cout << "Number of nodes expanded : " << nodes_expanded << endl;
    cout << "Number of steps : " << steps << endl;
    cout<<"Memory need for 1 node is: 81 bytes."<<endl;
    int x=81*nodes_generated;
    cout<<"Total memory needed for the algorithm is : "<< x << "bytes = " << x/(1024)<<"kb"<<endl;
    //cin>>x;
}

int main()
{
    int choice_game;
    cout <<"\t\t\tKALAH - Board Game\n\t\t      *-*-*-*-*-*-*-*-*-*-*-*\n\t\t\t*-Game Begins" << endl;
    cout << "Enter 1 for MinMaxAB " << endl;
    cout << "Enter 2 for AlphaBetaSearch " << endl;
    cout << "Enter 3 for MinMaxAB vs AlphaBetaSearch" << endl;
    cout << "Enter 4 for user vs system " << endl;
    cout << "Enter 5 for user vs user " << endl;
    cin >> choice_game;
    
    switch(choice_game)
    {
        case 1:
            MinMax();
            break;
        case 2:
            AlphaBeta();
            break;
        case 3:
            MinMaxVsAlphaBeta();
            break;
        case 4:
            UserVsSystem();
            break;
        case 5:
            UserVsUser();
            break;
    }
    Statistics_print();
    
    return 0;
}

