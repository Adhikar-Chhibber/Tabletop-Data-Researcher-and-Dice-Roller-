#ifndef GENERAL_H
#define GENERAL_H

#include <cstdlib>
#include <time.h>
#include <cctype>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdio>
#include <chrono>
#include <iostream>

using namespace std;

struct spell{
	string name;
	string description;
};

struct Creat{
	string name;
	string description;
};

bool hasNum(string input){
	for(unsigned i = 0; i < input.size(); i++){
		if(isdigit(input.at(i))){
			return true;
		}
	}
	return false;
}


string parse(string input){
	string output;

	for(unsigned i = 0; i < input.size(); i++){
		if(input.at(i) != ' '){
			output.push_back(input.at(i));
		}
	}

	return output;
}


string up(string input){
	string temp;

	for(unsigned i = 0; i < input.size(); i++){
		temp += toupper(input.at(i));
	}

	return temp;
}





int Hash(string input){

	int x = 0;

	for(unsigned i = 0; i < input.size(); i++){
		x += toupper(input.at(i));
	}

	x = x % 500;

	return x;


}


#endif