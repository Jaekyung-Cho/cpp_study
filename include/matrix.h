#pragma once

#include <iostream>
#include <random>
#include <cstdlib>
#include "randomfloat.h"

using namespace std;

namespace Matrix{
  class matrix
  {
    private:
      int row;
      int column;
      double *data;

    public: 
      //matrix 생성자
      matrix(int row_i, int col_i){
        row = row_i;
        column = col_i;
        data = new double[row_i*col_i];
      }
      //matrix 생성자2
      matrix(int row_i, int col_i, double *data_i){
        row = row_i;
        column = col_i;
        data = new double[row_i*col_i];
        data = data_i;
      }
      //소멸자
      // ~matrix(){

      // }
      //0행렬 생성자
      void zero(){
        for(int i = 0; i< row*column; i++){
          data[i] = 0;
        }
      }
      //unit행렬 생성자
      void unit(){
        if(row!=column){
          cout << "it's not unit matrix" << endl;
        }
        else{
          for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
              if(i==j) data[i*column+j]=1;
              else data[i*column+j]=0;
            }
          }
        }
      }
      //random 행렬 생성자
      void rand(){
        for(int i = 0; i< row*column; i++){
          data[i] = getRandomNumber_normal();
        }
      }
      //print matrix
      void print(){
        for(int i=0; i<row; i++){
          cout<< "| ";
          for (int j=0; j< column; j++){
            cout << data[i*column+j] << "\t";
          }
          cout << "|" << endl;
        }
      }
      //덧셈 연산 
      matrix operator+(matrix m2){
        if(row!= m2.row || column != m2.column){
          throw length_error("[Error reason] Dimension is not correnct!!");
        }
        else{
          double *data_n = new double[row*column];
          for(int i=0;i<row*column;i++){
            data_n[i] = data[i] + m2.data[i];
          }
          return matrix(row,column,data_n);
        }
      }
      //뺄셈 연산
      matrix operator-(matrix m2){
        if(row!= m2.row || column != m2.column){
          throw length_error("[Error reason] Dimension is not correnct!!");
        }
        else{
          double *data_n = new double[row*column];
          for(int i=0;i<row*column;i++){
            data_n[i] = data[i] - m2.data[i];
          }
          return matrix(row,column,data_n);
        }
      }
      //곱셈 연산
      matrix operator*(matrix m2){
        if(column!= m2.row){
          throw length_error("[Error reason] Dimension is not correnct!!");
        }
        else{
          double *data_n = new double[row*m2.column];
          for(int i=0;i<row;i++){
            for(int j=0 ; j< m2.column ; j++){
              double sum = 0;
              for(int k = 0; k< column ; k++){
                sum += data[i*column + k] * m2.data[k* m2.column + j];
              }
              data_n[i*m2.column+j] = sum;
            }
          }
          return matrix(row, m2.column, data_n);
        }
      }
      //Determinent
      double det(){
        if(row != column){
          throw length_error("[Error reason] Not Square Matrix!!");
        }
        else{
          if(row == 1){
            return data[0];
          }
          else if(row == 2){
            return data[0]*data[3]-data[1]*data[2];
          }
          else{
            double add = 0;
            double sub = 0;
            for(int i=0;i < row; i++){   
              double add_mul = 1;
              double sub_mul = 1;      
              for (int j=0;j<column ; j++){
                if(row-j-1 >= i){
                  add_mul *= data[i+(row+1)*j];
                }
                else{
                  add_mul *= data[i+(row+1)*j-row];
                }
                if(j <= i){
                  sub_mul *= data[i+(row-1)*j];
                }
                else{
                  sub_mul *= data[i+(row-1)*j+row];
                }
              }
              add += add_mul;
              sub += sub_mul;
            }
            return add-sub;
          }
        }
      }
      //Transpose
      void transpose(){
        int temp = column;
        column = row;
        row = temp;
        for(int i = 0; i< row; i++){
          for(int j=0; j< column; j++){
            double data_t = data[i*column +j];
            data[i*column+j] = data[j*row+i];
            data[j*row+i] = data_t;
          }
        } 
      }
      //get specific value of matrix
      double getValue(int target_row, int target_col){
        return data[target_row*column + target_col];
      }
      //get specific row of matrix
      matrix getRow(int target_row){
        double *data_t = new double[column];
        for(int i = 0; i< column; i++){
          data_t[i] = data[target_row*column + i];
        }
        return matrix(1,column, data_t);
      }
      //get specific column of matrix
      matrix getColumn(int target_col){
        double *data_t = new double[row];
        for(int i = 0; i< row; i++){
          data_t[i] = data[target_col*row + i];
        }
        return matrix(row,1, data_t);
      }
      //remove specific row of matrix
      matrix removeRow(int target_row){
        double *data_t = new double[(row-1)*column];
        int count = 0;
        for(int i = 0; i< row; i++){
          if(i!=target_row-1)
          {
            for(int j = 0;j< column;j++){
              data_t[count++] = data[i*column+j];
            }
          }
        }
        return matrix(row-1, column, data_t);
      }
      matrix removeColumn(int target_col){
        double *data_t = new double[(row)*(column-1)];
        int count = 0;
        for(int i = 0; i< row; i++){
          for(int j =0; j< column; j++){
            if(j!=target_col-1){
              data_t[count++] = data[i*column+j];
            }
          }
        }
        return matrix(row, column-1, data_t);
      }
      //Inverse matrix
      matrix inverse(){
        if(row != column){
          throw length_error("[Error reason] Not Square Matrix!!");
        }
        
        else if(this -> det()==0){
          throw overflow_error("[Error reason] There is no inverse matrix(devide by zero)");
        }
        else {
          if(row == 1){
            data[0] = 1/data[0];
            return matrix(1,1,data);
          }
          else{
            double det = this -> det();
            double *data_t = new double[row*column];
            for(int i = 0; i< row ;i++){
              for(int j = 0; j< column; j++){
                if((i+j)%2==0){
                  data_t[i*column+j] = (this -> removeRow(j+1)).removeColumn(i+1).det()/det;
                }
                else{
                  data_t[i*column+j] = -(this -> removeRow(j+1)).removeColumn(i+1).det()/det;
                }
              }
            }
            return matrix(row,column, data_t);
          }
        }
      }
  };
}