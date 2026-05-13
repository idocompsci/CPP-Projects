
/******************************************                                                  
 ** File: TicTacToe.cpp                                                                           
                                                                                             
 ** Assignment: CMSC 202 Project 1, Spring 2025                                                    
                                                                                             
 ** Author: EJ Nyameh                                                                        
                                                                                                                                      
                                                                                             
 **                                                                                          
                                                                                             
 ** This file contains the main driver program for project 1.                                    
                                                                                             
 ** This program uses statements, loops, and functions to                                 
                                                                                             
 ** properly run this tictactoe game.                                                                             
 *****************************************/
#include <iostream>
#include <ctime>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;
//declaration and initialization of constants representing the 2 players
const char symbol1='X';
const char symbol2='O';
//Function delcarations
void displayBoard(char ticTacBoard[3][3]);
void clearBoard(char ticTacBoard[3][3]);
void playGame(char ticTacBoard[3][3]);
void mainMenu(char ticTacBoard[3][3]);
void saveGame(char ticTacBoard[3][3]);
bool checkWinner(char ticTacBoard[3][3]);


/*main declares and initializes the board that will be used through out the entire program and calls
mainMenu() to start the game*/
int main()
{
  char ticTacBoard[3][3]={{'-','-','-'},{'-','-','-'},{'-','-','-'}};
   mainMenu(ticTacBoard);

  return 0;
}



/*mainMenu is responsible for prompting the user with the necessary options regarding the gameplay.
They can either play the game which calls playGame() or they can quit which would end the program.*/
void mainMenu(char ticTacBoard[3][3])
{
  //local variable declarations
  int choice;

   cout<<"Welcome to Tic-Tac-Toe\n";
  
  do{
     cout <<"What would you like to do?\n"
      <<"1. Play New Game\n"
      <<"2. Quit\n";
      cin>>choice;
    

  

    switch(choice)
    {
    case 1: 
      clearBoard(ticTacBoard);
      playGame(ticTacBoard);
  break;
    case 2: cout<<"Thank you for playing Tic-Tac-Toe\n";
    saveGame(ticTacBoard);

    }
  }while(choice!=2);
  
  
}

/*playGame is responsible for allowing the user to choose what symbol they want to be, and makes sure
that they symbol is a valid choice before continuing with the game. Once the input is validated, both
players will take turns putting their symbol on a 3 by 3 tic-tac-toe board. board entries will also
be validated to make sure that the entry isn't out of bounds or that entry isn't already occupied.*/
void playGame(char ticTacBoard[3][3])
{
  //make a variable for taking turns
  int turn=0;
  char mark;
  int row, column;

  cout<<"What symbol would you like to be? (X or O)\n";
  /*make code to check to make sure the user puts in a X or O, if not, prompt the 
  user the question, and keep asking till valid input is entered*/
  cin>>mark;
  while(mark!=symbol2 and mark!=symbol1)
  {
      cout<<"What symbol would you like to be? (X or O)\n";
      cin>>mark;
  }
  displayBoard(ticTacBoard);

  //make code to keep alternating turns for each player until the entire board is filled up
  while(checkWinner(ticTacBoard)==false)
  {
    if(turn%2==0)
    {
      cout<<"Player X, enter row and column (0-2): ";
      cin>>row>>column;
     //while loop checking for validity of row and column entries
      while((ticTacBoard[row][column]!='-') or ((row<0 or row>2) and (column<0 or column>2)))
      {

          cout<<"Invalid move. Try again.\n";
            displayBoard(ticTacBoard);
            cout<<"Player X, enter row and column (0-2): ";
            cin>>row>>column;
          displayBoard(ticTacBoard);
          

        
        }
        ticTacBoard[row][column]='X';
      displayBoard(ticTacBoard);

      
      saveGame(ticTacBoard);
    //inrcrement turn to change player
    turn++;
    }
    else if(turn%2==1)
    {
      cout<<"Player O, enter row and column (0-2): ";
        cin>>row>>column;
        //while loop checking for validity of row and column entries
      while((ticTacBoard[row][column]!='-') or ((row<0 or row>2) and (column<0 or column>2)))
      {   
            cout<<"Invalid move. Try again.\n";
            displayBoard(ticTacBoard);
            cout<<"Player O, enter row and column (0-2): ";
            cin>>row>>column;
          displayBoard(ticTacBoard);
          
      }

    
      
    ticTacBoard[row][column]='O';
    displayBoard(ticTacBoard);

    
    saveGame(ticTacBoard);
    //increment turn to change player
    turn++;
    
    

    }
  }
  
}

/*displayBoard is responsible for showing the board after each move, so players know what entries are
and aren't free to choose*/
void displayBoard(char ticTacBoard[3][3])
{
  cout<<"Current Board: \n";
  for(int i=0; i<3;i++)
  {
    for(int j=0; j<3;j++)
    {

      cout<<ticTacBoard[i][j]<<" ";
    }
  cout<<endl; //for line break  
  }


}


/*clearBoard is responsible for clearing the board if the user decides not to use the saved game
that was found on file after an unexpected quit while the game was still running*/
void clearBoard(char ticTacBoard[3][3])
{
 
  // delete current values and refill array with initial values
  for(int i=0; i<3;i++)
  {
    for(int j=0; j<3;j++)
    {
       ticTacBoard[i][j]='-';
      
    }
  }

}

/*checkWinner basically checks to see if there's a winner on all rows, columns and diags. This
function is called after every move*/
bool checkWinner(char ticTacBoard[3][3])
{
  //check for winner on all columns
  for(int i=0; i<3; i++)
  {
    if(ticTacBoard[0][i]!='-' and ticTacBoard[0][i]==ticTacBoard[1][i]
     and ticTacBoard[1][i]==ticTacBoard[2][i])
     {
      cout<<"Player "<<ticTacBoard[1][i]<<" wins!\n";
      cout<<"Thank you for playing Tic-Tac-Toe\n";
      return true;
     }
  }

  //check for winner on all rows
  for(int i=0; i<3; i++)
  {
    if(ticTacBoard[i][0]!='-' and ticTacBoard[i][0]==ticTacBoard[i][1]
     and ticTacBoard[i][1]==ticTacBoard[i][2])
     {
      cout<<"Player "<<ticTacBoard[i][1]<<" wins!\n";
      cout<<"Thank you for playing Tic-Tac-Toe\n";
      return true;
     }
  }

  //check for winner on diags
  for(int i=0; i<3; i++)
  {
    if(ticTacBoard[0][0]!='-' and ticTacBoard[0][0]==ticTacBoard[1][1]
     and ticTacBoard[1][1]==ticTacBoard[2][2])
     {
      cout<<"Player "<<ticTacBoard[1][1]<<" wins!\n";
      cout<<"Thank you for playing Tic-Tac-Toe\n";
      return true;
     }
  }
  //second diag
  for(int i=0; i<3; i++)
  {
    if(ticTacBoard[0][2]!='-' and ticTacBoard[0][2]==ticTacBoard[1][1]
     and ticTacBoard[1][1]==ticTacBoard[2][0])
     {
      cout<<"Player "<<ticTacBoard[1][1]<<" wins!\n";
      cout<<"Thank you for playing Tic-Tac-Toe\n";
      return true;
     }
  }
  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
      if(ticTacBoard[i][j]=='-')
      {
        return false;
      }
    }
  }
   cout<<"This game is a draw!\n";
   cout<<"Thank you for playing Tic-Tac-Toe\n";

  return true;

}


/*saveGame is the function that saves every move so if the user unexpectedly quits, they can see
the status of how the board was before the quit*/
void saveGame(char ticTacBoard[3][3])
{
  //declare and open a text file
  ofstream myfile("proj1_data.txt");

  if(myfile.is_open())
  {
  
    for(int i=0; i<3;i++)
      {
        for(int j=0; j<3;j++)
        {

          myfile<<ticTacBoard[i][j]<<" ";
        }
      myfile<<" \n";
      }
     myfile.close();
  }
 

}


