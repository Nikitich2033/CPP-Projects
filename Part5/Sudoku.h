#ifndef SUDOKU_H
#define SUDOKU_H

#include "SudokuSquare.h"
#include "Searchable.h"
#include <set>
#include <math.h>
#include <cmath>
#include <iterator>
#include <map>

#include <iostream>
using namespace std;
// TODO: Your Sudoku class goes here:

class Sudoku : public Searchable{

private:

    std::vector<std::vector<SudokuSquareSet>> board;
    //std::vector<std::vector<set<int>>> board;
    int boardsize;

public:

    Sudoku(int boardsizeIn):boardsize(boardsizeIn){
        //int count = 0;

        set<int> initialSet = {1,2,3,4,5,6,7,8,9};

        for (int i = 0; i < boardsize; i++) {
          vector<SudokuSquareSet> rowVector;
          //vector<set<int>> rowVector;
          for (int j = 0; j < boardsize; j++) {
            //count++;
            //rowVector.push_back(initialSet);
            SudokuSquareSet set;
            for (int k = 1; k < 10; k++) {
              set.insert(k);
            }
            rowVector.push_back(set);
          }
          board.push_back(rowVector);
        }

        //std::cout << "Sets inserted: "<<count << '\n';

      }

    int getSquare(int row, int col){

      if(board[row][col].size() == 1){
        return *board[row][col].begin();
      }
      else{
        return -1;
      }

    }

    bool setSquare(int row, int col, int value){


      board[row][col].clear();
      board[row][col].insert(value);

      //std::cout << "Value inserted: "<< value << '\n';

      bool gotSmaller = true;
      //while the number of choices gets smaller with each iteration
      while(gotSmaller){

        gotSmaller = false;

        //go through the whole board
        //check all size 1 sets
        //delete the value from the sets in the same row and columns
        //delete the value from the box which the square is in


        for (int i = 0; i < boardsize; i++) {
          for (int j = 0; j < boardsize; j++) {



            if (board[i][j].size() == 1) {

              // std::cout << "To remove: "<<getSquare(i,j) << '\n';
              // std::cout << "Board row: "<< i << '\n';
              // std::cout << "Board col: "<< j << '\n';

              //remove value from the sets in the same row and column
              bool removedFromRowAndCol = removeFromRowAndCol(getSquare(i,j),i,j);

              //remove values from the sqrt(boardsize)^2 sized square
              //add math lib for sqrt

              bool removedFromBox = removeFromBox(getSquare(i,j),i,j,i,j);

              //if the functions removed any values set gotSmaller to true
              if(removedFromBox || removedFromRowAndCol){
                gotSmaller = true;
              }

            }
            if(board[i][j].empty()){
              return false;
            }
          }
        }
      }

      return true;
    }


    bool removeFromRowAndCol(int valueInSquare,int row, int col){

      bool gotSmaller = false;

      for (int i = 0; i < boardsize; i++) {
        for (int j = 0; j < boardsize; j++) {

          if(row == i ^ col == j){


            if(board[i][j].find(valueInSquare) != board[i][j].end()){

              board[i][j].erase(valueInSquare);
              gotSmaller = true;

            }
          }
        }
      }

      return gotSmaller;
    }


    bool removeFromBox(int valueInSquare,int currentRow, int currentCol, int exceptRow, int exceptCol){

      bool gotSmaller = false;

      int rowCoord = currentRow - (currentRow%(int)sqrt(boardsize));

      int colCoord = currentCol - (currentCol%(int)sqrt(boardsize));

      for (int row = rowCoord; row < (rowCoord + (int)sqrt(boardsize));row++) {

        for(int col = colCoord; col < (colCoord + (int)sqrt(boardsize)); col++){

          if(board[row][col].find(valueInSquare) != board[row][col].end()){

            if(row != exceptRow|| col != exceptCol){

              board[row][col].erase(valueInSquare);
              gotSmaller = true;

            }
          }
        }
      }

      return gotSmaller;

    }

// error: invalid new-expression of abstract class type ‘Sudoku’
// add const to abstract methods, otherwise countrd as not implemented
    bool isSolution() const{

        bool onlyOneValue = true;

        for (int i = 0; i < boardsize; i++) {
            for (int j = 0; j < boardsize; j++) {

                if (board[i][j].size() != 1){

                    onlyOneValue = false;

                }

            }
        }

        return onlyOneValue;
    }

    vector<unique_ptr<Searchable> > successors() const{

     vector<unique_ptr<Searchable>> successors;

     for (int i = 0; i < boardsize; i++) {
         for (int j = 0; j < boardsize; j++) {

             if (board[i][j].size() != 1){

                 for(int value : board[i][j]){

                    //try with  *
                     Sudoku* copyOfCurrentBoard = new Sudoku(*this);

                     if(copyOfCurrentBoard -> setSquare(i,j,value) == true){

                        successors.push_back(unique_ptr<Searchable>(copyOfCurrentBoard));

                     }
                     else {

                        delete copyOfCurrentBoard;

                     }

                 }

                 return successors;
             }
         }
     }

     return successors;

 }

 void write(ostream & o) const{

     for (int i = 0; i < boardsize; i++) {
         for (int j = 0; j < boardsize; j++) {

             if (board[i][j].size() == 1){
                 o << *board[i][j].begin();
             }
             else {
                 o << " ";
             }
         }
         o << "\n";
     }
 }

};

#endif
