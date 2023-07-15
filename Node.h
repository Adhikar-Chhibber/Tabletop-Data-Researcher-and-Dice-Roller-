#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "Roller.h"
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

virtual int execute(){

	if(IsRoll(data)){
		return Roll(data);
	}else{
		return stoi(data);
	}
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

class Div : public Node{

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
	in.push_back(s);


	if(out.size() == 0){
		Node* yet = new Node;
		yet -> data = in.at(0);
		parent.push_back(yet);
		return;
	}


	type = out.at(0);

	switch (type){

		case 42:{
		mult* temp = new mult;
		Node* l= new Node;
		Node* r = new Node;
		r -> data = in.at(0);
		l -> data = in.at(1);
		temp -> left = l;
		temp -> right = r;
		parent.push_back(temp);
		break;
	}
		case 43:{
		add* Temp = new add;
		Node* L= new Node;
		Node* R = new Node;
		R -> data = in.at(0);
		L -> data = in.at(1);
		Temp -> left = L;
		Temp -> right = R;
		parent.push_back(Temp);
		break;
	}
		case 45:{
		sub* tEmp = new sub;
		Node* W = new Node;
		Node* E = new Node;
		E -> data = in.at(0);
		W -> data = in.at(1);
		tEmp -> left = W;
		tEmp -> right = E;
		parent.push_back(tEmp);
		break;
	}
		case 47:{
		Div* teMp = new Div;
		Node* q = new Node;
		Node* v = new Node;
		v -> data = in.at(0);
		q -> data = in.at(1);
		teMp -> left = q;
		teMp -> right = v;
		parent.push_back(teMp);
		break;
	}
	}

	for(unsigned i = 2; i < in.size(); i++){
		type = out.at(i-1);

		switch (type){

		case 42:{
		mult* pmet = new mult;
		Node* b = new Node;
		b -> data = in.at(i);
		pmet -> left = b;
		pmet -> right = parent.at(0);
		parent.pop_back();
		parent.push_back(pmet);
		break;
	}
		case 43:{
		add* pmeT = new add;
		Node* k = new Node;
		k -> data = in.at(i);
		pmeT -> left = k;
		pmeT -> right = parent.at(0);
		parent.pop_back();
		parent.push_back(pmeT);		
		break;
	}
		case 45:{
		sub* pmEt = new sub;
		Node* g = new Node;
		g -> data = in.at(i);
		pmEt -> left = g;
		pmEt -> right = parent.at(0);
		parent.pop_back();
		parent.push_back(pmEt);
		break;
	}
		case 47:{
		Div* Pmet = new Div;
		Node* p = new Node;
		p -> data = in.at(i);
		Pmet -> left = p;
		Pmet -> right = parent.at(0);
		parent.pop_back();
		parent.push_back(Pmet);
		break;
	}
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


#endif