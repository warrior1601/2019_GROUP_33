#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Model
{
	private

		vector<string> Material =vector<string>(5);
		vector<string> Vectore =vector<string>(5);
		vector<string> Cell=vector<string>(5);
		int totalvalue_c;
		int totalvalue_v;


	public:
		
		Model();//constructor
		~Model();//destructor
		void readfile(string path);
		void display_Vec();
		void display_Cell();
};

