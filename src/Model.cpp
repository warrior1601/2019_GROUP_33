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

    convert_vector();
    convert_cell_h();
    convert_cell_p();
    convert_cell_t();
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


void Model::convert_vector()
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
}

double** Model::getvector()
{
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
	for (int n = 0; n < totalvalue_c; ++n)
	{
		if (Cell[n][4]=='t'|Cell[n][5]=='t'|Cell[n][6]=='t')
		{
			cout << "c" << n << ":Tetrahedron" << endl;
		}
		if (Cell[n][4]=='p'|Cell[n][5]=='p'|Cell[n][6]=='p')
		{
			cout << "c" << n << ":Hexahedron" << endl;
		}
		if (Cell[n][4]=='h'|Cell[n][5]=='h'|Cell[n][6]=='h')
		{
			cout << "c" << n << ":Pyramid" << endl;
		}
	}

	cout << "The total value for the cell is:" << totalvalue_c<< endl;
}

void Model::convert_cell_t()
{
    int i=totalvalue_c;
    number_t=0;
    int space[6];
    cell_t=new string*[i];
    cell_ot=new double*[i];
    for(int m=0;m<i;m++)
    {
        cell_t[m]=new string[5];
        cell_ot[m]=new double[4];
    }
    for(int n=0;n<i;n++)
    {
        //material=Cell[n][4];
       // cout<<Cell[1][4]<<endl;
       // cout<<n<<endl;
        string x_1,x_2,x_3,x_4="";
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
                    cell_t[number_t][0]+=Cell[n][read_p];
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
                    cell_t[number_t][1]+=Cell[n][read_p];
                    x_1+=Cell[n][read_p];
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
                    cell_t[number_t][2]+=Cell[n][read_p];
                    x_2+=Cell[n][read_p];
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
                    cell_t[number_t][3]+=Cell[n][read_p];
                    x_3+=Cell[n][read_p];
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
                    cell_t[number_t][4]+=Cell[n][read_p];
                    x_4+=Cell[n][read_p];
                }
            }
            cell_ot[number_t][0]=atof(x_1.c_str());
            cell_ot[number_t][1]=atof(x_2.c_str());
            cell_ot[number_t][2]=atof(x_3.c_str());
            cell_ot[number_t][3]=atof(x_4.c_str());
            number_t++;
        }
    }
}

void Model::convert_cell_p()
{
    int i=totalvalue_c;
    number_p=0;
    int space[7];
    cell_p=new string*[i];
    cell_op=new double*[i];
    for(int m=0;m<i;m++)
    {
        cell_p[m]=new string[6];
        cell_op[m]=new double[5];
    }
    for(int n=0;n<i;n++)
    {
        //material=Cell[n][4];
       // cout<<Cell[1][4]<<endl;
       // cout<<n<<endl;
        string x_1,x_2,x_3,x_4,x_5="";
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
                    cell_p[number_p][0]+=Cell[n][read_p];
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
                    cell_p[number_p][1]+=Cell[n][read_p];
                    x_1+=Cell[n][read_p];
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
                    cell_p[number_p][2]+=Cell[n][read_p];
                    x_2+=Cell[n][read_p];
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
                    cell_p[number_p][3]+=Cell[n][read_p];
                    x_3+=Cell[n][read_p];
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
                    cell_p[number_p][4]+=Cell[n][read_p];
                    x_4+=Cell[n][read_p];
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
                    cell_p[number_p][5]+=Cell[n][read_p];
                    x_5+=Cell[n][read_p];
                }
            }
            cell_op[number_p][0]=atof(x_1.c_str());
            cell_op[number_p][1]=atof(x_2.c_str());
            cell_op[number_p][2]=atof(x_3.c_str());
            cell_op[number_p][3]=atof(x_4.c_str());
            cell_op[number_p][4]=atof(x_5.c_str());
            number_p++;
        }
    }
}

void Model::convert_cell_h()
{
    int i=totalvalue_c;
    number_h=0;
    int space[10];
    cell_h=new string*[i];
    cell_oh=new double*[i];
    for(int m=0;m<i;m++)
    {
        cell_h[m]=new string[9];
        cell_oh[m]=new double[8];
    }
    for(int n=0;n<i;n++)
    {
        //material=Cell[n][4];
       // cout<<Cell[1][4]<<endl;
       // cout<<n<<endl;
       string x_1,x_2,x_3,x_4,x_5,x_6,x_7,x_8="";
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
                    cell_h[number_h][0]+=Cell[n][read_p];
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
                    cell_h[number_h][1]+=Cell[n][read_p];
                    x_1+=Cell[n][read_p];
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
                    cell_h[number_h][2]+=Cell[n][read_p];
                    x_2+=Cell[n][read_p];
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
                    cell_h[number_h][3]+=Cell[n][read_p];
                    x_3+=Cell[n][read_p];
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
                    cell_h[number_h][4]+=Cell[n][read_p];
                    x_4+=Cell[n][read_p];
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
                    cell_h[number_h][5]+=Cell[n][read_p];
                    x_5+=Cell[n][read_p];
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
                    cell_h[number_h][6]+=Cell[n][read_p];
                    x_6+=Cell[n][read_p];
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
                    cell_h[number_h][7]+=Cell[n][read_p];
                    x_7+=Cell[n][read_p];
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
                    cell_h[number_h][8]+=Cell[n][read_p];
                    x_8+=Cell[n][read_p];
                }
            }
            cell_oh[number_h][0]=atof(x_1.c_str());
            cell_oh[number_h][1]=atof(x_2.c_str());
            cell_oh[number_h][2]=atof(x_3.c_str());
            cell_oh[number_h][3]=atof(x_4.c_str());
            cell_oh[number_h][4]=atof(x_5.c_str());
            cell_oh[number_h][5]=atof(x_6.c_str());
            cell_oh[number_h][6]=atof(x_7.c_str());
            cell_oh[number_h][7]=atof(x_8.c_str());
            number_h++;
            //cout<<cell_oh[number_h][0]<<endl;
        }
    }
}

string** Model::getcell_t()
{
    return cell_t;
}

string** Model::getcell_p()
{
    return cell_p;
}

string** Model::getcell_h()
{
    return cell_h;
}

double* Model::getcenter()
{
    center=new double[3];
    int i=totalvalue_c;
    double x=0;
    double y=0;
    double z=0;
    int a=0;
    int number=0;
    if(cell_t[0][0]!="")
    {
        for(int n=0;n<number_t;n++)
        {
            for(int m=0;m<4;m++)
            {
                a=0;
                a=cell_ot[n][m];
                x+=vector_pass[a][0];
                y+=vector_pass[a][1];
                z+=vector_pass[a][2];
                number++;
            }
        }
    }
    if(cell_p[0][0]!="")
    {
        for(int n=0;n<number_p;n++)
        {
            for(int m=0;m<5;m++)
            {
                a=0;
                a=cell_op[n][m];
                x+=vector_pass[a][0];
                y+=vector_pass[a][1];
                z+=vector_pass[a][2];
                number++;
            }
        }
    }
    if(cell_h[0][0]!="")
    {
        for(int n=0;n<number_h;n++)
        {
            for(int m=0;m<8;m++)
            {
                a=0;
                a=cell_oh[n][m];
                x+=vector_pass[a][0];
                y+=vector_pass[a][1];
                z+=vector_pass[a][2];
                number++;
                cout<<number<<":"<<x<<endl;
            }
        }
    }
    center[0]=x/number;
    center[1]=y/number;
    center[2]=z/number;

    return center;
}
