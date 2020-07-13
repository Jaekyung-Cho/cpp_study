#pragma once
#include<random>
#include<iostream>

using namespace std;

double getRandomNumber_normal(){
  //< 1단계. 시드 설정
  random_device rn;
  mt19937_64 rnd( rn() );
 
    //< 2단계. 분포 설정 ( 정수 )
  normal_distribution<double> dist;

    //< 3단계. 값 추출
  return dist( rnd );
}