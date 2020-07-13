#include <iostream>
#include "hello.h"


int main(){
  using namespace std;

  int length;
  cin >> length;

  int *array = new int[length];

  int count =0;
  for (int i=0; i< length; i++){
    array[i]=count ;
    count++;
  }
  
  int num;
  cin >> num;

  cout << array[num] << endl;

  return 0;
}