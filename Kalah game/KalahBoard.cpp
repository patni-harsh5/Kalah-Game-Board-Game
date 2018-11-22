//
//  KalahBoard.cpp
//  Kalah game
//
//  Created by HARSH H PATNI on 11/22/18.
//  Copyright © 2018 HARSH H PATNI. All rights reserved.
//

#include "KalahBoard.hpp"
#include <iostream>
#include <iomanip>
#include<ctime>
#include<cstdlib>


using namespace std;

//initializing the board
KalahBoard::KalahBoard()
{
    for(int i = 0 ; i < 6; i++)
    {
        A[i] = 6;
        B[i] = 6;
    }
    numberOfSlots = 5;
    kalah_A = 0,kalah_B = 0;
    ptr = NULL;
    winDecider = 36;
}

//constructor to set the board values, mainly used for testing
KalahBoard::KalahBoard(int arr1[],int arr2[],int a, int b)
{
    for(int i=0;i<6;i++)
    {
        A[i]=arr1[i];
        B[i]=arr2[i];
    }
    kalah_A = a;
    kalah_B = b;
}

//copy constructor to copy the value of the board from one var to another
KalahBoard::KalahBoard(KalahBoard *b)
{
    for(int i=0;i<6;i++)
    {
        this->A[i]=b->A[i];
        this->B[i]=b->B[i];
    }
    this->kalah_A = b->kalah_A;
    this->kalah_B = b->kalah_B;
}

//Function to move for the A player
char KalahBoard::move_A(int hole_number)
{
    int tempPos = hole_number;
    ptr = A;
    int numberOfStones = ptr[tempPos];
    ptr[tempPos] = 0;
    int opponentPos, opponentStones;
    
    tempPos++;
    while(numberOfStones > 0)
    {
        if(tempPos >= 0 && tempPos <= 5)
        {
            if(numberOfStones == 1)
            {
                numberOfStones--;
                opponentPos = numberOfSlots - tempPos;
                if(ptr[tempPos] == 0 && B[opponentPos] > 0)
                {
                    ptr = B;
                    opponentStones = ptr[opponentPos];
                    ptr[opponentPos] = 0;
                    kalah_A += opponentStones + 1;
                    if(numberOfStones == 0)
                        return 'B';
                }
                else
                {
                    ptr[tempPos] += 1;
                    if(numberOfStones == 0)
                        return 'B';
                }
            }
            else if(numberOfStones > 1)
            {
                numberOfStones--;
                ptr[tempPos]+=1;
            }
        }
        else if(tempPos == 6 && numberOfStones >= 1)
        {
            numberOfStones--;
            kalah_A += 1;
            if(numberOfStones == 0)
                return 'A';
        }
        else if(tempPos > 6 && tempPos <= 12)
        {
            ptr = B;
            numberOfStones--;
            ptr[tempPos-7] += 1;
            if(numberOfStones == 0)
                return 'B';
        }
        else if(tempPos >= 12)
        {
            tempPos = -1;
            ptr = A;
        }
        tempPos++;
    }
    return 'B';
}

//Function to move for the B player
char KalahBoard::move_B(int hole_number)
{
    int tempPos = hole_number;
    ptr = B;
    int numberOfStones = ptr[tempPos];
    ptr[hole_number] = 0;
    int opponentPos, opponentStones;
    
    tempPos++;
    while(numberOfStones > 0)
    {
        if(tempPos >= 0 && tempPos <= 5)
        {
            if(numberOfStones == 1)
            {
                numberOfStones--;
                opponentPos = numberOfSlots - tempPos;
                if(ptr[tempPos] == 0)
                {
                    ptr = A;
                    opponentStones = ptr[opponentPos];
                    ptr[opponentPos] = 0;
                    kalah_B += opponentStones + 1;
                    if(numberOfStones == 0)
                        return 'A';
                }
                else
                {
                    ptr[tempPos] += 1;
                    if(numberOfStones == 0)
                        return 'A';
                }
            }
            else if(numberOfStones > 1)
            {
                numberOfStones--;
                ptr[tempPos]+=1;
            }
        }
        else if(tempPos == 6 && numberOfStones >= 1)
        {
            numberOfStones--;
            kalah_B += 1;
            if(numberOfStones == 0)
                return 'B';
        }
        else if(tempPos > 6 && tempPos <= 12)
        {
            ptr = A;
            numberOfStones--;
            ptr[tempPos-7] += 1;
            if(numberOfStones == 0)
                return 'A';
        }
        else if(tempPos >= 12)
        {
            tempPos = -1;
            ptr = B;
        }
        tempPos++;
    }
    return 'A';
}

//Function which decides as to who should move
char KalahBoard::move(int hole_number,char player)
{
    char v;
    if(player == 'A')
        v = move_A(hole_number);
    else
        v = move_B(hole_number);
    return v;
}

//Function to decide as to which player wins
char KalahBoard::checkWin()
{
    int a0=0,b0=0,a_stones=0,b_stones=0;
    for(int i =0 ;i<6 ;i++)
    {
        if(A[i]==0)
        {
            a0++;
        }
        if(B[i]==0)
        {
            b0++;
        }
        a_stones += A[i];
        b_stones += B[i];
        
    }
    if(a0 == 6)
    {
        kalah_B +=b_stones;
        for(int i = 0 ; i < 6; i++)
        {
            B[i] = 0;
        }
        cout<<"A has no stones left to play"<<endl;
    }
    if( b0 == 6)
    {
        kalah_A += a_stones;
        for(int i = 0 ; i < 6 ; i++)
        {
            A[i] = 0;
        }
        cout<<"B has no stones left to play"<<endl;
    }
    if(kalah_A > winDecider)//A wins
    {
        return 'A';   // A wins
    }
    else if(kalah_B > winDecider)//B Wins
    {
        return 'B';  // B wins
    }
    else if(a0 == 6 || b0 == 6)
    {
        return 'T'; // indicates that a tie occurred
    }
    else//No win
    {
        return 'N';
    }
}

//
void KalahBoard::operator=(KalahBoard kb)
{
    for(int i=0;i<6;i++)
    {
        A[i]=kb.A[i];
        B[i]=kb.B[i];
        
    }
    numberOfSlots = 5;
    kalah_A=kb.kalah_A;
    kalah_B=kb.kalah_B;
    ptr = NULL;
    winDecider = 36;
}

//Function to display the board
void KalahBoard::displayBoard()
{
    cout << endl;
    cout << "\t\tA PLAYER";
    cout << endl;
    // First Line
    cout << "\t";
    for(int i = 0 ; i < 25; i++)
    {
        cout << "-";
    }
    //Second Line
    cout << endl;
    cout << "\t" << "|";
    cout << setw(2);
    
    for(int i = 5 ; i >= 0 ; i--)
    {
        cout << A[i] << setw(2) << "|";
        cout << " ";
    }
    cout << endl;
    cout << "------";  //Third Line
    cout << "\t\t\t\t   ------";
    cout << endl;
    cout <<"|" << setw(3) << kalah_A << " |"; // Fourth Line
    cout <<"\t\t\t\t   |" << setw(3) << kalah_B << " |"; // Fourth Line
    cout << endl;
    // Fifth Line
    cout << "\t";
    for(int i = 0 ; i < 25; i++)
    {
        cout << "-";
    }
    cout << endl;
    //Sixth Line
    cout << "\t" << "|";
    cout << setw(2);
    
    for(int i = 0 ; i < 6; i++)
    {
        cout << B[i] << setw(2) << "|";
        cout << " ";
    }
    cout << endl;
    cout << "\t\tB PLAYER";
    cout << endl << endl << endl << endl;
}

bool KalahBoard::checkLegealMove(char player,int hole)
{
    if(hole >5 || hole < 0)
        return false;
    if(player == 'A' && A[hole] == 0)
    {
        return false;
    }
    else  if(player == 'B' && B[hole] == 0)
    {
        return false;
    }
    return true;
}
