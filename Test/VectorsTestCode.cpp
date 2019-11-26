
#include <iostream>
#include "Vectors.h"
using namespace std;

int main()
{
    Vectors test;
    Vectors test_2;
    Vectors test_3;

    test.SetVector(2, 3, 4);
    test_2.SetVector(5, 6, 7);

    cout<<"This is Vector 1"<<endl;
    cout<<test<<endl;

    cout<<"This is Vector 1.5 Copied"<<endl;
    Vectors test_1_5 = test;
    cout<<test_1_5<<endl;

    cout<<"This is Vector 2"<<endl;
    cout<<test_2<<endl;

    cout<<"This is Vector 3"<<" Vector 1 + Vector 2"<<endl;
    test_3 = test + test_2;
    cout<<test_3<<endl;

    cout<<"This is Vector 4"<<" Vector 2 - Vector 1"<<endl;
    Vectors test_4 = test_2 - test;
    cout<<test_4<<endl;

    cout<<"This is Vector 5 Vector Product"<<endl;
    Vectors test_5 = test.Vector_Product(test_2);
    cout<<test_5<<endl;

    float test_6 = test.Scalar_Product(test_2);
    cout<<"This is Scalar Product of Vector 2"<<endl;
    cout<<test_6<<endl;

    cout<<"This is Vector 1"<<endl;
    cout<<test<<endl;

    float X = test.GetXVector();
    float Y = test.GetYVector();
    float Z = test.GetZVector();

    cout<<"Verifying Get function works"<<endl;
    cout<<"X = "<<X<<" Y = "<<Y<<" Z = "<<Z<<endl;

    cout<<"Vector 1 divided by 2"<<endl;
    Vectors test_7 = test.Vector_Divide_By_Number(2);
    cout<<test_7<<endl;

    cout<<"Verifying that Vector 1 is unchanged"<<endl;
    cout<<test<<endl;

    Vectors test_8;
    test_8.SetX_Vector(8.8);
    test_8.SetY_Vector(9.8);
    test_8.SetZ_Vector(10.8);
    cout<<"This is Vector 8"<<endl;
    cout<<"Verifying Set functions work"<<endl;
    cout<<test_8<<endl;

}
