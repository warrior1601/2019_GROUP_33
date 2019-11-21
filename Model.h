#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Model
{
private:

		vector<string> Material;
		vector<string> Vectore;
		vector<string> Cell;
		vector<string> Content_file;
		double** vector_pass;
		string** material_pass;


    public:
        //double(*take)[3];
		Model();//constructor
		~Model();//destructor
		int totalvalue_m;
        int totalvalue_c;
		int totalvalue_v;
		int readfile(string path);
		int savefile_binary(string save_path);
		int readfile_binary(string binary_path);
		double** getvector();
		string** getmaterial();
		string** getcell_t();
		string** getcell_p();
		string** getcell_h();
		void display_Vec();
		void display_Cell();
		//float* getcenter();

};

#endif // MODEL_H
