/*

Implementing a B+ Tree in C++

*/

#include <fstream>
// #include<conio>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;
int max_keys;
int count=0;
string root="0.txt";
string format=".txt";

void set_maxkey_value(string filename)
{
	// string line;
    ifstream myfile (filename.c_str());
    if (myfile.is_open())
    {
        while (myfile.good())
        {
        	myfile >> max_keys;
        }
        myfile.close();
    }
    else 
    {  
        cout << "Unable to open file "<<filename<<endl; 
    }
    cout<<"Setting the maxkeys to "<<max_keys<<endl;
}	

void intialize_root()
{
	string filename=root;
	ofstream myfile (filename.c_str());
	int number_of_elements=0;
	bool isleaf = true;
    if (myfile.is_open())
    {
        myfile << number_of_elements;
        myfile << isleaf;
        myfile.close();
    }
    else 
    {  
        cout << "Unable to open file "<<filename<<endl; 
    }
}

void insert_key(float key, string key_value, string filename)
{
	cout<<"Insertion : Key: "<<key<<"\tValue: "<<key_value<<"\tFilename: "<<filename<<endl;
	int number_of_elements;
	bool isleaf;
	float t_key;
	string file; 
	ifstream myfile (filename.c_str());
    if (myfile.is_open())
    {
        while (myfile.good())
        {
        	myfile >> number_of_elements >> isleaf;
        	if(isleaf)
        	{





        	}
        	else
        	{







        	}
        }
        myfile.close();
    }
    else 
    {  
        cout << "Unable to open file "<<filename<<endl; 
    }



}

void range_query(float start, float end, string filename)
{
	cout<<"Range Query : Start ->"<<start << "\t End: "<<end<<endl;


}

void queries_init(string filename)
{
	int type_of_query;
	float start, end, key;
	string key_value;
	ifstream myfile (filename.c_str());
    if (myfile.is_open())
    {
        while (myfile.good())
        {
			myfile >> type_of_query;
			if(type_of_query == 0)
			{
				myfile >> key;
				myfile >> key_value;
				insert_key(key,key_value,root); 
			}
			else if(type_of_query == 2)
			{
				myfile >> start;
				myfile >> end;
				range_query(start,end,root);
			}
			else
			{
				//IGNORE ANY QUERY OTHER THAN ABOVE 2
			}
			     	
        }
        myfile.close();
    }
    else 
    {  
        cout << "Unable to open file "<<filename<<endl; 
    }
	cout<<"All the queries have been processed\n";
}

void input_init(string filename)
{
	float key;
	string key_value;
	ifstream myfile (filename.c_str());
    if (myfile.is_open())
    {
        while (myfile.good())
        {
			myfile >> key;
			myfile >> key_value;
			insert_key(key,key_value,root); 
        }
        myfile.close();
    }
    else 
    {  
        cout << "Unable to open file "<<filename<<endl; 
    }
	cout<<"Points from the file "<<filename<< " has been inserted \n";
}

int main()
{
	string input="assgn2_bplus_data.txt",queries="querysample.txt";
	string file_maxkeys="bplustree.config";
	cout<<"Processing.........\n";
	intialize_root();
	set_maxkey_value(file_maxkeys);
	cout<<"Inserting the points from assgn2_bplus_data.txt\n";
	input_init(input);
	cout<<"Processing the queries\n";
	queries_init(queries);
	return 0;
}




// void file_reader()
// { 
//     string line;
//     ifstream myfile ("example.txt");
//     if (myfile.is_open())
//     {
//         while (myfile.good())
//         {
//           stream_reader(myfile);
//         }
//         myfile.close();
//     }
//     else 
//     {  
//         cout << "Unable to open file"; 
//     }
// }

// void stream_reader(istream& stream)
// {
//     getline (stream,line);
//     cout << line << endl;
// }