#include "Model.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;


Model::Model()
{
	cout<<"Model has been created"<<endl;

}

Model::~Model()
{
	cout << "Model has been realeased" << endl;
}


int Model::readfile(string path) //read the model file
{
	//string *filepath = path;
	ifstream file;
	file.open(path, ios::in);

	if (!file.is_open()) {
		return 0;
	}
	string strLine;
	int i_c=0,i_v=0,i_m;
	while (getline(file, strLine))
	{
		if (strLine.empty()) {
			continue;
		}
		if (strLine[0] == 'm') {
            i_m++;
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
        //cout<<strLine<<endl;
		Content_file.push_back(strLine);
	}
    file.close();
	this->totalvalue_c = i_c;
	this->totalvalue_v = i_v;
	this->totalvalue_m =i_m;

}

int Model::readfile_binary(string binary_path) //check the binary file
{
    vector<string> check_content;
    //int i=Content_file.size();

	ifstream file(binary_path, ios::in | ios::binary);
	if(!file.is_open())
	{
		return 0;
	}
    string test;
    while(getline(file,test))
	{
        cout<<test<<endl;
	}
    file.close();

}

int Model::savefile_binary(string save_path) //save the loaded model as binary file
{
    ofstream file;
    file.open(save_path, ios::out | ios::binary);

    if (!file.is_open()) {
		return 0;
	}

    int i=Content_file.size();

    for(int n=0;n<i;n++){

        Content_file[n]=Content_file[n]+"\n";
        file.write(Content_file[n].c_str(),Content_file[n].size());

    }
    file.close();
}


double** Model::getvector()
{
    int i=Vectore.size();
    int n=0;
    int space[3];
    //double vector_pass[i][3];
    vector_pass= new double*[i];
    for(size_t j=0;j<i;j++)
    {
        vector_pass[j]=new double[3];
    }
    while(n<i){
        int position=2;
        int num=0;
        while((position=Vectore[n].find_first_of(" ",position))!=string::npos){      //push all the space in an array

        space[num]=position;
        position++;
        num++;

        }
        int number=0;
        int number_doublecheck=0;
        string x="";
        string y="";
        string z="";
        for(int value_positionx=space[0];value_positionx<space[1];value_positionx++){      //get the value for the x
                number=value_positionx+1;
                number_doublecheck=value_positionx;
                if(Vectore[n][number]==' '&& Vectore[n][number_doublecheck]=='.')
                {
                    Vectore[n][number]='0';
                    x=x+Vectore[n][number];
                }
                else if(Vectore[n][number]==' ')
                {
                    continue;
                }
                else if(Vectore[n][number]!=' ')
                {
                    x=x+Vectore[n][number];
                }
        }

        for(int value_positiony=space[1];value_positiony<space[2];value_positiony++){      //get the value for the y
                number=value_positiony+1;
                number_doublecheck=value_positiony;

                if(Vectore[n][number]==' '&& Vectore[n][number_doublecheck]=='.')
                {
                    Vectore[n][number]='0';
                    y=y+Vectore[n][number];
                }
                else if(Vectore[n][number]==' ')
                {
                    continue;
                }
                else if(Vectore[n][number]!=' ')
                {
                    y=y+Vectore[n][number];
                }
        }

        for(int value_positionz=space[2];value_positionz<Vectore[n].size()-1;value_positionz++){      //get the value for the z
                number=value_positionz+1;
                //number_doublecheck=value_positionz;

                if(Vectore[n][number]=='.'&& number==Vectore[n].size()-1)
                {
                    z=z+Vectore[n][number]+'0';
                }
                else
                {
                    z=z+Vectore[n][number];
                }
        }
        //cout<<x<<":"+y<<":"+z<<endl;
        double X=0;
        double Y=0;
        double Z=0;
        X=atof(x.c_str()),Y=atof(y.c_str()),Z=atof(z.c_str());
        vector_pass[n][0]=X;
        vector_pass[n][1]=Y;
        vector_pass[n][2]=Z;
        n++;
    }

        return vector_pass;

}

string** Model::getmaterial()
{
    int i=Material.size();
    int n=0;
    int space[4];
    //double vector_pass[i][3];
    material_pass= new string*[i];
    for(size_t j=0;j<i;j++)
    {
        material_pass[j]=new string[4];
    }
    while(n<i){

        int position=0;
        int num=0;
        while((position=Material[n].find_first_of(" ",position))!=string::npos){      //push all the space in an array

        space[num]=position;
        position++;
        num++;
        //cout<<position<<endl;
        }
        int number=0;

        for(int material_positionID=space[0];material_positionID<space[1];material_positionID++){      //get the value for the ID
                number=material_positionID+1;

                if(Material[n][number]==' ')
                {
                        continue;
                }
                else if(Material[n][number]!=' ')
                {
                    material_pass[n][0]+=Material[n][number];
                }
        }

        for(int material_positionname=space[3];material_positionname<Material[n].size()-1;material_positionname++){      //get the value for the name
                number=material_positionname+1;

                if(Material[n][number]==' ')
                {
                        continue;
                }
                else if(Material[n][number]!=' ')
                {
                    material_pass[n][1]=material_pass[n][1]+Material[n][number];
                }
        }

        for(int material_positioncolor=space[2];material_positioncolor<space[3];material_positioncolor++){      //get the value for the color
                number=material_positioncolor+1;

                if(Material[n][number]==' ')
                {
                        continue;
                }
                else if(Material[n][number]!=' ')
                {
                    material_pass[n][2]+=Material[n][number];
                }
        }

        for(int material_positiondensity=space[1];material_positiondensity<space[2];material_positiondensity++){      //get the value for the density
                number=material_positiondensity+1;

                if(Material[n][number]==' ')
                {
                        continue;
                }
                else if(Material[n][number]!=' ')
                {
                    material_pass[n][3]+=Material[n][number];
                }
        }
                n++;
    }
                return material_pass;

}


void Model::display_Vec()
{
	cout << "The total number of Vector in this Model is:" << this->totalvalue_v << endl;
	//return totalvalue_c;
}

void Model::display_Cell()  //show the type of each cell and total number
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

	cout << "The total value for the cell is:" << totalvalue_c<< endl;
}

string** Model::getcell_t()
{
    //char material;
    int i=totalvalue_c;
    int number=0;
    int space[6];
    string** cell_t=new string*[i];
    for(int m=0;m<i;m++)
    {
        cell_t[m]=new string[5];
    }
    for(int n=0;n<i;n++)
    {
        //material=Cell[n][4];
       // cout<<Cell[1][4]<<endl;
       // cout<<n<<endl;
        if(Cell[n][4]=='t'|Cell[n][5]=='t'|Cell[n][6]=='t')
        {
            int position=2;
            int num=0;
            while((position=Cell[n].find_first_of(" ",position))!=string::npos){      //push all the space in an array

            space[num]=position;
            position++;
            num++;
            //cout<<position<<endl;
            }
            int read_p=0;

            for(int m_1=space[1];m_1<space[2];m_1++)
            {
                read_p=m_1+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_t[number][0]+=Cell[n][read_p];
                }
            }

            for(int v_1=space[2];v_1<space[3];v_1++)
            {
                read_p=v_1+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_t[number][1]+=Cell[n][read_p];
                }
            }

            for(int v_2=space[3];v_2<space[4];v_2++)
            {
                read_p=v_2+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_t[number][2]+=Cell[n][read_p];
                }
            }

            for(int v_3=space[4];v_3<space[5];v_3++)
            {
                read_p=v_3+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_t[number][3]+=Cell[n][read_p];
                }
            }

            for(int v_4=space[5];v_4<Cell[n].size()-1;v_4++)
            {
                read_p=v_4+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_t[number][4]+=Cell[n][read_p];
                }
            }
            number++;
        }
    }
    return cell_t;
}

string** Model::getcell_p()
{
    //char material;
    int i=totalvalue_c;
    int number=0;
    int space[7];
    string** cell_p=new string*[i];
    for(int m=0;m<i;m++)
    {
        cell_p[m]=new string[6];
    }
    for(int n=0;n<i;n++)
    {
        //material=Cell[n][4];
       // cout<<Cell[1][4]<<endl;
       // cout<<n<<endl;
        if(Cell[n][4]=='p'|Cell[n][5]=='p'|Cell[n][6]=='p')
        {
            int position=2;
            int num=0;
            while((position=Cell[n].find_first_of(" ",position))!=string::npos){      //push all the space in an array

            space[num]=position;
            position++;
            num++;
            //cout<<position<<endl;
            }
            int read_p=0;

            for(int m_1=space[1];m_1<space[2];m_1++)
            {
                read_p=m_1+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_p[number][0]+=Cell[n][read_p];
                }
            }

            for(int v_1=space[2];v_1<space[3];v_1++)
            {
                read_p=v_1+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_p[number][1]+=Cell[n][read_p];
                }
            }
            for(int v_2=space[3];v_2<space[4];v_2++)
            {
                read_p=v_2+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_p[number][2]+=Cell[n][read_p];
                }
            }

            for(int v_3=space[4];v_3<space[5];v_3++)
            {
                read_p=v_3+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_p[number][3]+=Cell[n][read_p];
                }
            }

            for(int v_4=space[5];v_4<space[6];v_4++)
            {
                read_p=v_4+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_p[number][4]+=Cell[n][read_p];
                }
            }

            for(int v_5=space[6];v_5<Cell[n].size()-1;v_5++)
            {
                read_p=v_5+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_p[number][5]+=Cell[n][read_p];
                }
            }
            number++;
        }
    }
    return cell_p;
}

string** Model::getcell_h()
{
    //char material;
    int i=totalvalue_c;
    int number=0;
    int space[10];
    string** cell_h=new string*[i];
    for(int m=0;m<i;m++)
    {
        cell_h[m]=new string[9];
    }
    for(int n=0;n<i;n++)
    {
        //material=Cell[n][4];
       // cout<<Cell[1][4]<<endl;
       // cout<<n<<endl;
        if(Cell[n][4]=='h'|Cell[n][5]=='h'|Cell[n][6]=='h')
        {
            int position=2;
            int num=0;
            while((position=Cell[n].find_first_of(" ",position))!=string::npos){      //push all the space in an array

            space[num]=position;
            position++;
            num++;
            //cout<<position<<endl;
            }
            int read_p=0;

            for(int m_1=space[1];m_1<space[2];m_1++)
            {
                read_p=m_1+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_h[number][0]+=Cell[n][read_p];
                }
            }

            for(int v_1=space[2];v_1<space[3];v_1++)
            {
                read_p=v_1+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_h[number][1]+=Cell[n][read_p];
                }
            }
            for(int v_2=space[3];v_2<space[4];v_2++)
            {
                read_p=v_2+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_h[number][2]+=Cell[n][read_p];
                }
            }

            for(int v_3=space[4];v_3<space[5];v_3++)
            {
                read_p=v_3+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_h[number][3]+=Cell[n][read_p];
                }
            }

            for(int v_4=space[5];v_4<space[6];v_4++)
            {
                read_p=v_4+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_h[number][4]+=Cell[n][read_p];
                }
            }

            for(int v_5=space[6];v_5<space[7];v_5++)
            {
                read_p=v_5+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_h[number][5]+=Cell[n][read_p];
                }
            }

            for(int v_6=space[7];v_6<space[8];v_6++)
            {
                read_p=v_6+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_h[number][6]+=Cell[n][read_p];
                }
            }

            for(int v_7=space[8];v_7<space[9];v_7++)
            {
                read_p=v_7+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_h[number][7]+=Cell[n][read_p];
                }
            }

            for(int v_8=space[9];v_8<Cell[n].size()-1;v_8++)
            {
                read_p=v_8+1;
                if(Cell[n][read_p]==' ')
                {
                    continue;
                }
                else
                {
                    cell_h[number][8]+=Cell[n][read_p];
                }
            }
            number++;
        }
    }
    return cell_h;
}
