#ifndef CREATURE_H
#define CREATURE_H

#include <cstdlib>
#include <time.h>
#include <cctype>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdio>
#include <chrono>
#include "General.h"
#include <iostream>

using namespace std;


void build_c(vector<Creat*>& v){
	v.resize(500);
	for(unsigned i = 0; i < 500; i++){
		v.at(i) = nullptr;
	}
	
	string temp;
	string adder;
	string hash;

	int loc = 0;
	int tot = 0;

	ifstream in;

	in.open("Creature.txt");

	while(tot != 316){

		Creat* out = new Creat;

		getline(in, temp);
		out -> name = temp;
		hash = temp;

		temp = "";

		getline(in, temp);
		while(temp != "SEPERATOR--"){
			adder += temp;
			adder += "\n";
			getline(in, temp);
		}

		out -> description = adder; 
		adder = "";
		temp = "";

		loc = Hash(hash);

		if(v.at(loc) != nullptr){
			while(v.at(loc) != nullptr){
				if(loc == 499){
					loc = 0;
				}else{
					loc++;
				}
			}
		}

		v.at(loc) = out;
		tot++;

	}

	in.close();

}

void searchC(const vector<Creat*> & v, string input){
	int loc = Hash(input);
	int start = loc;
	if(v.at(loc) == nullptr){
		cout << "CREATURE DOES NOT EXSIST. IF THIS IS AN ERROR PLEASE SEND IT TO THE DEVELOPER\n\n\n";
		return;
	}
	string tem = v.at(loc) -> name;
	string temp;
	string in;

	for(unsigned i = 0; i < tem.size(); i++){
		temp += toupper(tem.at(i));
	}
	for(unsigned i = 0; i < input.size(); i++){
		in += toupper(input.at(i));
	}


	while(temp != in){
		loc++; 
		if(loc >= v.size()){
			loc = 0;
		}
		if(loc == start){
			cout << "CREATURE DOES NOT EXIST. IF THIS IS AN ERROR PLEASE SEND IT TO THE DEVELOPER\n\n\n";
			return;
		}
		if(v.at(loc) == nullptr){
			cout << "CREATURE DOES NOT EXIST. IF THIS IS AN ERROR PLEASE SEND IT TO THE DEVELOP\n\n\n";
			return;
		}

		temp = v.at(loc) -> name;
		string jump;
		for(unsigned i = 0; i < (v.at(loc) -> name).size(); i++){
			jump += toupper((v.at(loc) -> name).at(i));
		}
		temp = jump;
		//cout << temp << endl << in << endl;
	

	}


	cout << v.at(loc) -> name << endl;
	cout << v.at(loc) -> description << endl << endl << endl;

}


#endif