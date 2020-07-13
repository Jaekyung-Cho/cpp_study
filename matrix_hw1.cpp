#include "include/matrix.h"


using namespace std;

int main(){
  cout << "start" <<endl;
  double array1[6]={1,0,2,1,0,2};
  double array2[6]={1,2,3,4,5,6};
  double array3[9] = {1,2,3,4,1,2,3,4,5};
  
  Matrix::matrix b = Matrix::matrix(2,3,array1);
  Matrix::matrix c = Matrix::matrix(3,3,array3);
  b+c;
  cout << b.det() << endl;

  

  return 0;
}