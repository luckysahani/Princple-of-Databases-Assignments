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

using namespace std;
int max_keys;

void set_maxkey_value(string filename)
{
	string line;
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


void queries_init(string filename)
{
	// cout<<"The filename is "<<filename<<endl;

	cout<<"All the queries have been processed\n";
}

void input_init(string filename)
{
	// cout<<"The filename is "<<filename<<endl;


	cout<<"Points from the file "<<filename<< " has been inserted \n";
}

int main()
{
	string input="assgn2_bplus_data.txt",queries="querysample.txt";
	string file_maxkeys="bplustree.config";
	cout<<"Processing.........\n";
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