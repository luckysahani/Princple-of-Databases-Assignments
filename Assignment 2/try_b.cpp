#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

int file_cnt = 1;
int max_elem  = 1;
char root[20] = "node_0.txt";
char fileinit[20] = "node_";
char fileformat[20] = ".txt";

int split(float key, float val, char filename[], float* keyarr, char valarr[][20] ){
	char tempfile1[40]= "", temp[10] = "", temp1[10] = "", tempfile2[40]= "";
	strcpy(temp,to_string(file_cnt).c_str());
	strcat(tempfile1, fileinit), strcat(tempfile1 , temp),	strcat(tempfile1,fileformat);
	file_cnt++;
	strcpy(temp1,to_string(file_cnt).c_str());
	strcat(tempfile2, fileinit), strcat(tempfile2 , temp1),	strcat(tempfile2,fileformat);
	file_cnt++;
	
	ofstream f1,f2;
	f1.open(tempfile1,ofstream::out);
	f2.open(tempfile2,ofstream::out);
	f3.open(filename,ofstream::out);

	int temp = (max_elem+1)/2;

	f1 << temp << " 1\n"; 
	for(int i=0;i<(max_elem+1)/2;i++){

	}

// 	file_cnt++;
// 	cout << tempfile1 << tempfile2;
}

float insert(float key, float val, char filename[]){
	int num_elem;
	bool isleaf;
	ifstream fin (filename, ifstream::in);
	fin >> num_elem >> isleaf;
	float temp_key;
	char file[40];
	if(isleaf){
		string temp_val;
		if(num_elem == max_elem){
			float valarr[max_elem];
			char keyarr[max_elem][20];
			for(int i = 0;i< num_elem ;i++){
				fin >> keyarr[i] >> valarr[i];
			}
			fin.close();
			split(key,val,filename,valarr,keyarr);
		}
	}
	else {
		for(int i=0;i<num_elem;i++){
			fin >> file;
			fin >> temp_key;
			if(key < temp_key){
				int ret = insert(key, val, file);
				if(ret != -1){

				}
			}
		}
	}

}


bool input(char filename[]){
	int type;
	float key;
	ifstream fin ;
	fin.open(filename, ifstream::in);
	string val;
	fin >> type;
	fin >> key;
	fin >> val;
	// if(type == 0)
	// 	insert(key, val, root);
}


int main(){
	float a[10];
	char b[20][20];
	split(0.5,0.5,root,a,b);
	return 0;
}