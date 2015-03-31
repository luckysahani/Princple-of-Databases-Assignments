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
#include <algorithm>

using namespace std;
int max_keys;
int count=0;
string root="0.txt";
string format=".txt";
string temp_child_1,temp_child_2;

void set_maxkey_value(string filename)
{
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
        myfile << "\t";
        myfile << isleaf;
        myfile << "\n";
        myfile.close();
    }
    else 
    {  
        cout << "Unable to open file "<<filename<<endl; 
    }
}


float split(string filename, float* allkeys, string allkeys_value[], bool isleaf)
{
	cout<<"Split : filename: "<<filename;
	return -1;

}

float insert_key(float key, string key_value, string filename)
{
	cout<<"Insertion : Key: "<<key<<"\tValue: "<<key_value<<"\tFilename: "<<filename<<endl;
	int number_of_elements;
	bool isleaf;
	float t_key;
	string t_key_value,t_file; 
	ifstream myfile (filename.c_str());
    if (myfile.is_open())
    {
        while (myfile.good())
        {
        	myfile >> number_of_elements >> isleaf;
    		// float allkeys[number_of_elements+1];
    		// string allkeys_value[number_of_elements+1];
        	if(isleaf)
        	{
        		float allkeys[number_of_elements+1];
    			string allkeys_value[number_of_elements+1];
        		bool check = false;
        		for (int i = 0; i < number_of_elements; ++i)
        		{
        			// myfile >> allkeys[i] >> allkeys_value[i];
        			myfile >> t_key >> t_key_value;
        			if(key < allkeys[i])
        			{
        				allkeys[i+1] = t_key;
        				allkeys_value[i+1] = t_key_value;
        				if(!check)
        				{
        					allkeys[i]=key;
        					allkeys_value[i]=key_value;
        					check = true;
        				}
        			}
        			else
        			{
        				allkeys[i]=t_key;
        				allkeys_value[i]=t_key_value;
        			}
        		}
        		if(!check)
        		{
        			allkeys[number_of_elements]=key;
					allkeys_value[number_of_elements]=key_value;
					check = true;
        		}
        		myfile.close();
        		cout<<"Isleaf function\n";
        		if(number_of_elements == max_keys)
        		{
        			return split(filename, allkeys, allkeys_value, isleaf);
        		}
        		else
        		{
        			ofstream file (filename.c_str());
				    if (file.is_open())
				    {
				    	file << number_of_elements + 1 << " 1\n";
				    	for (int i = 0; i < number_of_elements+1; ++i)
				    	{
				    		file << allkeys[i]<<" "<<allkeys_value[i]<<endl;
				    	}
				    }
				    file.close();
				    return -1;
        		}



        	}
        	else
        	{
        		float allkeys[number_of_elements+1];
    			string file_array[number_of_elements+1],tempfile1,tempfile2;
        		for (int i = 0,j=0; i < number_of_elements; ++i,++j)
        		{
        			myfile >> file_array[i] >> allkeys[i];
        			if(key < allkeys[i])
        			{
        				float return_value= insert_key(key, key_value, file_array[j]);
        				if(return_value != -1)
        				{
        					allkeys[j+1]= allkeys[j];
        					allkeys[j]= return_value;
        					file_array[j+1]=temp_child_2;
        					file_array[j]=temp_child_1;
        					for (j=j+2,i++; i < number_of_elements; ++i,++j)
        					{
        						myfile >> file_array[j] >> allkeys[j];
        					}
        					myfile >> file_array[j];
        					myfile.close();
        					if(number_of_elements == max_keys)
        					{
        						return split(filename,allkeys,file_array,isleaf);
        					}
        					else
        					{
        						ofstream file (filename.c_str());
							    if (file.is_open())
							    {
							    	int i;
							    	file << number_of_elements + 1 << " 0\n";
							    	for (i = 0; i < number_of_elements+1; ++i)
							    	{
							    		file << file_array[i]<<" "<<allkeys[i]<<endl;
							    	}
							    	file<<file_array[i];
							    }
							    file.close();
							    return -1;
        					}
        				}
        				else
        				{
        					return -1;
        				}
        			}
        		}
        		// if(number_of_elements == max_keys)
        		// {
        		// 	for (int i = 0; i < number_of_elements; ++i)
        		// 	{
        		// 		myfile >> allkeys[i];//filename
        		// 		myfile >> allkeys_value[i];//key
        		// 	}
        		// 	split(filename, allkeys, allkeys_value, isleaf);
        		// }
        		// else
        		// {
        		// 	for (int i = 0; i < number_of_elements; ++i)
        		// 	{
        		// 		myfile >> file;
        		// 		myfile >> t_key;
        		// 		if(key < t_key)
        		// 		{
        		// 			insert_key(key, key_value,file);
        		// 		}
        		// 	}
        		// }
        	}
        }
        // myfile.close();
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
				// myfile >> "\n";
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
	string sample_input="sample_input_32.txt"
	cout<<"Processing.........\n";
	intialize_root();
	set_maxkey_value(file_maxkeys);
	cout<<"Inserting the points from assgn2_bplus_data.txt\n";
	// input_init(input);
	input_init(sample_input);
	cout<<"Processing the queries\n";
	// queries_init(queries);
	return 0;
}

// void stream_reader(istream& stream)
// {
//     getline (stream,line);
//     cout << line << endl;
// }