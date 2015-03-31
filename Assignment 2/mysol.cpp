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
// using std::to_string;

int max_keys;
int count_total;
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
	count_total=1;
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
	cout<<"Split : filename: "<<filename<<endl;
	string temp;
	char Result[50];
	sprintf ( Result, "%d", count_total );
	temp_child_1= filename;
	temp_child_2= Result+format;
	count_total++;
	ofstream myfile1 (temp_child_1.c_str());
	ofstream myfile2 (temp_child_2.c_str());
	int element_count= (max_keys+1)/2;
	if(isleaf)
	{
		myfile1 << element_count<<" 1\n";
		myfile2 << max_keys + 1 - element_count<<" 1\n";
		for (int i = 0; i < element_count; ++i)
		{
			myfile1 << allkeys[i] << " " << allkeys_value[i]<<endl;
		}
		for (int i = element_count; i < max_keys; ++i)
		{
			myfile2 << allkeys[i] << " " << allkeys_value[i]<<endl;
		}
	}
	else
	{
		element_count= max_keys/2;
		myfile1 << element_count << " 0\n";
		myfile2 << max_keys + 1 - element_count << " 0\n";
		for (int i = 0; i < element_count; ++i)
		{
			myfile1 << allkeys_value[i]<< " "<< allkeys[i]<<" ";
		}
		myfile1 << allkeys_value[element_count]<<" ";

		for (int i = element_count+1; i < max_keys+1; ++i)
		{
			myfile2 << allkeys_value[i]<< " "<< allkeys[i]<<" ";
		}
		myfile2 << allkeys_value[max_keys+1]<<" ";
	}
	return allkeys[element_count];
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
    			string file_array[number_of_elements+1];
    			int i,j=0;
        		for (i = 0,j=0; i < number_of_elements; ++i,++j)
        		{
        			myfile >> file_array[i] >> allkeys[i];
        			if(key < allkeys[j])
        			{
        				break;
        			}
        		}
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
				}
				else
				{
					return -1;
				}
				if(number_of_elements == max_keys)
				{
					return split(filename,allkeys,file_array,isleaf);
				}
				else
				{
					ofstream file (filename.c_str());
					cout<<"check";
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
				    // return -1;
				}
				// else
				// {
				// 	return -1;
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
			float return_value=insert_key(key,key_value,root); 
			if(return_value != -1)
			{
				string temp_child_3;
				char Result[50];
				sprintf ( Result, "%d", count_total );
				temp_child_3=Result+format;
				count_total++;
				ofstream myfile3 (temp_child_3.c_str());
				myfile3 << "1 0\n";
				myfile3 << temp_child_1 << " "<< return_value << " "<< temp_child_2;
			}
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
	string sample_input="sample_input_32.txt";
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