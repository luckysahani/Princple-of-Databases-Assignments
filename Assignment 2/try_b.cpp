#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

int file_cnt = 1, max_elem  = 5;
char root[20] = "node_0.txt", fileinit[20] = "node_", fileformat[20] = ".txt", tempfile1[40]= "", tempfile2[40] = "";

float split(char filename[], float* keyarr, char valarr[][20], bool isleaf ){
	char temp[10] = "", temp1[10] = "";
	tempfile2[0]= tempfile1[0] = '\0';
	strcpy(tempfile1, filename);
	strcpy(temp1,to_string(file_cnt).c_str());
	strcat(tempfile2, fileinit), strcat(tempfile2 , temp1),	strcat(tempfile2,fileformat);
	file_cnt++;
	
	ofstream f1,f2,f3;
	f1.open(tempfile1,ofstream::out);
	f2.open(tempfile2,ofstream::out);

	int temp_cnt = (max_elem+1)/2;
	
	if(isleaf){
		f1 << temp_cnt << " 1\n";
		f2 << max_elem + 1 -temp_cnt << " 1\n";
		for(int i=0;i<temp_cnt;i++){
			f1 << keyarr[i] << " " << valarr[i] << endl;
		}
		for(int i=temp_cnt;i <= max_elem;i++){
			f2 << keyarr[i] << " " << valarr[i] << endl;
		}
	}
	else {

		temp_cnt = max_elem/2;
		f1 << temp_cnt << " 0\n";
		f2 << max_elem + 1 - temp_cnt << " 0\n";
		for(int i=0;i<temp_cnt;i++){
			f1 << valarr[i] << " " << keyarr[i] << " ";
		}
		f1 << valarr[temp_cnt] << " ";
		for(int i=temp_cnt + 1;i <= max_elem;i++){
			f2 << valarr[i] << " " << keyarr[i] << " ";
		}
		f2 << valarr[max_elem+1];
	}

	return keyarr[temp_cnt];
}

float insert(float key, char val[], char filename[]){
	int num_elem;
	bool isleaf;
	ifstream fin (filename, ifstream::in);
	fin >> num_elem >> isleaf;
	float temp_key;
	char file[40];
	if(isleaf){
		cout << "I am in leaf insert "<<endl;
		float keyarr[num_elem+1];
		char valarr[num_elem+1][20];
		bool done = false;
		for(int i = 0;i< num_elem ;i++){
			fin >> keyarr[i] >> valarr[i];
			if(keyarr[i] > key){
				keyarr[i+1] = keyarr[i];
				strcpy(valarr[i+1],valarr[i]);
				keyarr[i] = key;
				strcpy(valarr[i],val);
				done=true;
				i++;
			}
		}
		if(done){
			fin >> keyarr[num_elem] >> valarr[num_elem];
		}
		else{
			strcpy(valarr[num_elem],val);
			keyarr[num_elem] = key;
		}
		fin.close();
		printf("Entered at isleaf in insert function\n");
		string temp_val;
		if(num_elem == max_elem){
			return split(filename,keyarr,valarr,isleaf);
		}
		else{
			ofstream f;
			f.open(filename,ofstream::out);
			f << num_elem + 1 << " 1\n";
			for(int i = 0; i < num_elem +1;i++){
				f << keyarr[i] << " " << valarr[i] << endl;
			}
			return -1;
		}
	}
	else {
		float keyarr[num_elem+1];
		char valarr[num_elem+4][20];
		int i,j=0;
		for(i=0;i<num_elem;i++,j++){	
			fin >> valarr[j] >> keyarr[j];
			if(key < keyarr[j]){
				break;
			}
		}
		float ret = insert(key, val, valarr[j]);
		if(ret != -1){
			strcpy(valarr[j+1],tempfile2);
			strcpy(valarr[j],tempfile1);
			keyarr[j+1] = keyarr[j];
			keyarr[j] = ret;
			j++,j++,i++;
			// cout << valarr[2] << " Hello"<< endl;
			for(;i<num_elem;i++,j++){
				fin >> valarr[j] >> keyarr[j];
			}
			fin >> valarr[j];
			fin.close();
		}
		else{
			return -1;
		}
		if(num_elem == max_elem){
			return split(filename,keyarr,valarr,isleaf);
		}
		else{
			ofstream f;
			f.open(filename,ofstream::out);
			f << num_elem+1 << " 0\n";
			for(int i=0;i<=num_elem;i++){
				f << valarr[i] << keyarr[i];
			}
			f<<valarr[num_elem + 1];
		}
	}

}
bool input(char filename[]){
	int type;
	float key;
	ifstream fin ;
	fin.open(filename, ifstream::in);
	char val[40];
	//fin >> type;
	for(int i=0;i<6;i++){
		fin >> key;
		fin >> val;
		cout << key << " " << val << endl;
		float ret = insert(key, val, root);
		if(ret != -1){
			char tempfile3[40] = "",temp1[40] = "";
			strcpy(temp1,to_string(file_cnt).c_str());
			strcat(tempfile3, fileinit), strcat(tempfile3 , temp1),	strcat(tempfile3,fileformat);
			file_cnt++;
			ofstream f;
			f.open(tempfile3, ofstream::out);
			f << "1 0\n";
			f << tempfile1 << " " << ret << " " << tempfile2;
		}

	}
	// if(type == 0)
}
int main(){
	char s[20];
	cin >> s;
	// cout << s;
	input(s);
	return 0;
}