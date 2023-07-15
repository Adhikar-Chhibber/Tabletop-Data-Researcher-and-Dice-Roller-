#ifndef Expression_h
#define Expression_h

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <cctype>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdio>

using namespace std;


class Node{

public:
	Node* left;
	Node* right;
	string data;

Node(){
	left = nullptr;
	right = nullptr;
	data = "";
}

virtual int execute(){}

	if(IsRoll(data)){
		return Roll(data);
	}else{
		return stoi(data);
	}


};

class add : public Node{

virtual int execute(){

	int x,y = 0;

	if(right != nullptr){
		x = right -> execute();
	}

	if(left != nullptr){
		y = left -> execute();
	}

	return (x + y);

	
}


};

class sub : public Node{

virtual int execute(){

	int x,y = 0;

	if(right != nullptr){
		x = right -> execute();
	}

	if(left != nullptr){
		y = left -> execute();
	}

	return (x - y);

	
}


};

class mult : public Node{

virtual int execute(){

	int x,y = 0;

	if(right != nullptr){
		x = right -> execute();
	}

	if(left != nullptr){
		y = left -> execute();
	}

	return (x * y);

	
}


};

class div : public Node{

virtual int execute(){

	int x,y = 0;

	if(right != nullptr){
		x = right -> execute();
	}

	if(left != nullptr){
		y = left -> execute();
	}
	return (x/y);

	
}


};




string parse(string input){
	string output;

	for(unsigned i = 0; i < input.size(); i++){
		if(input.at(i) != ' '){
			output.push_back(input.at(i));
		}
	}

	return output;
}

void breaker(string input, vector<Node*> & parent){
		
	int size = parent.size();
	int type;

	vector<string> in;
	vector<char> out;

	string s,t;

	for(unsigned i = 0; i < input.size(); i++){
		if(input.at(i) == '+' || input.at(i) == '-' || input.at(i) == '*' || input.at(i) == '/' ){
			in.push_back(s);
			out.push_back(input.at(i));
			s = "";
		}else{
			s.push_back(input.at(i));
		}
	}

	type = out.at(0);

	switch (type){

		case 42:
		mult* temp = new mult;
		Node* l,r = new Node;
		r -> data = in.at(0);
		l -> data = in.at(1);
		temp -> left = l;
		temp -> right = r;
		parent.push_back(temp);
		break;

		case 43:
		add* temp = new add;
		Node* l,r = new Node;
		r -> data = in.at(0);
		l -> data = in.at(1);
		temp -> left = l;
		temp -> right = r;
		parent.push_back(temp);
		break;

		case 45:
		sub* temp = new sub;
		Node* l,r = new Node;
		r -> data = in.at(0);
		l -> data = in.at(1);
		temp -> left = l;
		temp -> right = r;
		parent.push_back(temp);
		break;

		case 47:
		div* temp = new div;
		Node* l,r = new Node;
		r -> data = in.at(0);
		l -> data = in.at(1);
		temp -> left = l;
		temp -> right = r;
		parent.push_back(temp);
		break;
	}

	for(unsigned i = 2; i < in.size(); i++){
		type = out.at(i-1);

		switch (type){

		case 42:
		mult* temp = new mult;
		Node* l = new Node;
		l -> data = in.at(i);
		temp -> left = l;
		temp -> right = parent.at(0);
		parent.pop_back();
		parent.push_back(temp);
		break;

		case 43:
		add* temp = new add;
		Node* l = new Node;
		l -> data = in.at(i);
		temp -> left = l;
		temp -> right = parent.at(0);
		parent.pop_back();
		parent.push_back(temp);		
		break;

		case 45:
		sub* temp = new sub;
		Node* l = new Node;
		l -> data = in.at(i);
		temp -> left = l;
		temp -> right = parent.at(0);
		parent.pop_back();
		parent.push_back(temp);
		break;

		case 47:
		div* temp = new div;
		Node* l = new Node;
		l -> data = in.at(i);
		temp -> left = l;
		temp -> right = parent.at(0);
		parent.pop_back();
		parent.push_back(temp);
		break;
	}

	}





}

void Roller(string input){

	int total = 0;

	vector<Node*> parent;

	breaker(input, parent);

	total = parent.at(0) -> execute();

	cout << "TOTAL: " << total << endl << endl;

	parent.pop_back();

}







}

#endif

