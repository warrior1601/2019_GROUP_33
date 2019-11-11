
#include <iostream>
#include "Vectors.h"
using namespace std;

int main(){

float Coord[3]   = {2,3,4};
float Coord_2[3] = {5,6,7};
float Coord_3[3] = {0,0,0};
float Coord_4[3] = {0,0,0};
float Coord_5[3] = {0,0,0};
float Coord_6[3] = {0,0,0};
float Coord_7[3] = {0,0,0};

Vectors test;
Vectors test_2;
Vectors test_3;
Vectors test_4;
Vectors test_5;

test.SetVector(Coord);
test_2.SetVector(Coord_2);

cout<<"This is Vector 1"<<endl;
*Coord_3 = test.GetVector(Coord_3);
cout<<Coord_3[0]<<Coord_3[1]<<Coord_3[2]<<endl;

cout<<"This is Vector 2"<<endl;
*Coord_4 = test_2.GetVector(Coord_4);
cout<<Coord_4[0]<<Coord_4[1]<<Coord_4[2]<<endl;

test_3 = test + test_2;
cout<<"This is Vector 3"<<" Vector 1 + Vector 2"<<endl;
*Coord_5 = test_3.GetVector(Coord_5);
cout<<Coord_5[0]<<Coord_5[1]<<Coord_5[2]<<endl;

test_4 = test_2 - test;
cout<<"This is Vector 4"<<"Vector 2 - Vector 1"<<endl;
*Coord_6 = test_4.GetVector(Coord_6);
cout<<Coord_6[0]<<Coord_6[1]<<Coord_6[2]<<endl;

test_5 = test.Vector_Product(test_2);
cout<<"This is Vector 5 Vector Product"<<endl;
*Coord_7 = test_5.GetVector(Coord_7);
cout<<Coord_7[0]<<Coord_7[1]<<Coord_7[2]<<endl;

float test_6 = test.Scalar_Product(test_2);
cout<<"This is Vector 6 Scalar Product"<<endl;
cout<<test_6<<endl;

}
