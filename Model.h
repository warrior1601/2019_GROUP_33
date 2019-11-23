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
		string** cell_t;
		string** cell_p;
		string** cell_h;
		string** material_pass;
		int number_t,number_p,number_h;
		double** cell_ot;
		double** cell_op;
		double** cell_oh;
		double* center;


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
		void convert_vector();
		void convert_cell_t();
		void convert_cell_p();
		void convert_cell_h();
		string** getmaterial();
		string** getcell_t();
		string** getcell_p();
		string** getcell_h();
		double** getvector();
		void display_Vec();
		void display_Cell();
		double* getcenter();

};

#endif // MODEL_H
