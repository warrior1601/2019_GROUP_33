#include "Model.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;
int main()
{
	Model test;
	test.readfile("E:\\ExampleModel2.mod");

    //test.display_Cell();

    //test.display_Vec();

    //test.savefile_binary("E:\\test.bin");
    //test.readfile_binary("E:\\test.bin");

    //double** p;    //to get the vector
    /*p=test.getvector();
    int m=test.totalvalue_v;
    for(int z=0;z<m;z++)
    {
        cout<<p[z][0]<<":"<<p[z][1]<<":"<<p[z][2]<<endl;
    }*/


    /*string** a=test.getmaterial();       //get the material
    for(int n=0;n<test.totalvalue_m;n++)
    {
        for(int p=0;p<4;p++)
        {
            cout<<a[n][p]<<endl;
        }
    }
    */
   //cout<<sizeof(p)<<endl;

   /*string** c=test.getcell_h();  //get different cell
   if(c[0][0]=="")
   {
       cout<<"None"<<endl;
   }
   else
   {
       cout<<c[100][7]<<endl;
   }
    */
}


