#include "Model.h"¡¢
#include "iostream"
#include "fstream"
#include "string"
#include "vector"

using namespace std;


Model::Model()
{
	cout<<"Model has been created"<<endl

}

Model::~Model()
{
	cout << "Model has been realeased" << endl;
}

void Model::readfile(string path)
{
	char* filepath = path;
	ifstream file;
	file.open(filepath, ios::in);

	if (!file.is_open()) {
		return 0;
	}
	std::string strLine;
	int i_c=0,i_v=0;
	while (getline(file, strLine))
	{
		if (strLine.empty()) {
			continue;
		}
		if (strLine[0] == 'm') {

			Material.push_back(strLine);

		}
		if (strLine[0] == 'v') {
			i_v++;
			Vectore.push_back(strLine);

		}
		if (strLine[0] == 'c') {
			i_c++;
			Cell.push_back(strLine);
		}
	}
	this->totalvalue_c = i_c;
	this->totalvalue_v = i_v;
}

void Model::display_Vec()
{
	cout << "The total number of Vector in this Model is:" << this->totalvalue_v << endl;
}

void Model::display_Cell()
{
	for (int i = 0; i < totalvalue_c; ++i)
	{
		if (Cell[i][4]=='t')
		{
			cout << "c" << i << ":Tetrahedron" << endl;
		}
		if (Cell[i][4] == 'h')
		{
			cout << "c" << i << ":Hexahedron" << endl;
		}
		if (Cell[i][4] == 'p')
		{
			cout << "c" << i << ":Pyramid" << endl;
		}
	}

	cout << "The total value for the cell is:" << totalvalue_c << endl;

}
