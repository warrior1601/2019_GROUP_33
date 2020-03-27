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

        //This is the constructor function which read the file
        //and call the other function
		Model(string path);

        //destructor is used to free the memory
		~Model();

		//This three value is used to show the total value of material,vector and cell
		int totalvalue_m;
        int totalvalue_c;
		int totalvalue_v;

		//savefile_binary is used to save the information to a binary file
		//user input the save_path
		int savefile_binary(string save_path);

		//readfile_binary is used to check if the information stored in the binary file is correct
		//input the binary path to check
		int readfile_binary(string binary_path);

		//This six function is used to convert the type of cell material and vector
		//cal_center is used to calculate the center of the model
		//it's not necessary to run this six function because it has been deal in the constructor function
		void convert_vector();
		void convert_cell_t();
		void convert_cell_p();
		void convert_cell_h();
		void convert_material();
		void cal_center();

		//use this function to accept the data of material in the model which return string** type pointer
		//it's a two-dimensional array the first dimensional means the id for each data the second dimensional means the data for each material
		string** getmaterial();

		//use this function to accept the data of cell in type t in the model which return string** type pointer
		//it's a two-dimensional array the first dimensional means the id for each data the second dimensional means the data for each cell
		string** getcell_t();

		//use this function to accept the data of cell in type p in the model which return string** type pointer
		//it's a two-dimensional array the first dimensional means the id for each data the second dimensional means the data for each cell
		string** getcell_p();

		//use this function to accept the data of cell in type h in the model which return string** type pointer
		//it's a two-dimensional array the first dimensional means the id for each data the second dimensional means the data for each cell
		string** getcell_h();

		//use this function to accept the data of vector in the model it return double** type pointer
		//it's a two-dimensional array the first dimensional means the id for each data the second dimensional means the data for each vector
		double** getvector();

		//call this function to show the total value of vector
		void display_Vec();

		//call this function to show the total value of cell and the type for each cell
		void display_Cell();

		//call this function to return the value of center which will return a double* type pointer
		//it's a array center[0]means x value, center[1]means y value, center[2]means z value
		//the size is 3 for this array
		double* getcenter();

};

#endif // MODEL_H
