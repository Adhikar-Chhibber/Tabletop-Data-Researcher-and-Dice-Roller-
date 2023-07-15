#ifndef SPELL_H
#define SPELL_H

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

void build(vector<spell*>& library){

	library.resize(500);
	for(unsigned i = 0; i < 500; i++){
		library.at(i) = nullptr;
	}
	//cout << "here2\n";
	int tot = 0;
	int loc = 0;

	ifstream in;

	in.open("Spells.txt");
	string temp;
	string hash;
	string adder;


	while(tot != 385){

		spell* out = new spell;

		getline(in, temp);
		out -> name = temp;
		hash = temp;

		getline(in, temp);


		while(temp != "SEPERATOR--"){
			temp += "\n";
			adder += temp;
			getline(in, temp);
		}

		loc = Hash(hash);
		out -> description = adder;
		adder = "";
		if(library.at(loc) == nullptr){
			library.at(loc) = out;
		}else{
			while(library.at(loc) != nullptr){
				loc++;
				if(loc == 500){
					loc = 0;
				}
			}
			library.at(loc) = out;
		}
		tot++;


	}


}

void search(const vector<spell*> & v, string input){
	int loc = Hash(input);
	int start = loc;

	string temp;

	input = up(input);
	
	if(v.at(loc) != nullptr && input == up(v.at(loc) -> name)){
		cout << up(v.at(loc) -> name) << endl << v.at(loc) -> description << endl << endl;
		return;
	}
	loc++;

	while(loc != start){
		if(v.at(loc) != nullptr && input == up(v.at(loc) -> name)){
			cout << up(v.at(loc) -> name) << endl << v.at(loc) -> description << endl << endl;
			return;
		}
		if(loc +1 != 500){
			loc++;
		}else{
			loc = 0;
		}
	}

	cout << "THIS SPELL DOES NOT EXIST OR IS SPELLED INCORRECTLY. PLEASE CONTACT DEVELOPER IF THIS IS NOT TRUE WITH THE NAME OF THE SPELL\n\n";

}

#endif