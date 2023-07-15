#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <cctype>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdio>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct spell{
	string name;
	string description;
};

struct Creat{
	string name;
	string description;
};










////////BASIC FUNCTIONS

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




/////TYPES


int Roll(string input){

	string times;
	unsigned i;
	for(i = 0; input.at(i) != 'd' && input.at(i) != 'D'; i++){
		times.push_back(input.at(i));
	}

	i++;

	double t;

	if(times.size() != 0){
	 t = stod(times, nullptr);
	}else{
		 t = 1.0;
	}

	if(t == 0){
		cout << "NO DICE ROLLED\n\n";
		return -1;
	}


	times = "";

	for(unsigned k = i; k < input.size(); k++){
		times.push_back(input.at(k));
	}
	if(times == "0"){
		cout << "INVALID INPUT, CANNOT ROLL DICE VALUE 0\n\n";
		return -1;
	}

	int x = stoi(times, nullptr);

	int output = 0;

	for(double ti = 0.0; ti < t; ti++){
		int temp = ((rand() % x) + 1.0);
		if(t != 1 && ti + 1 < t){
			cout << temp << ", ";
		}else{
			cout << temp;
		}
		output += temp;
	}
	cout << endl;
	/*cout << endl << "TOTAL: ";

	cout << output << endl << endl;
	*/

	return output;

}

bool IsRoll(string input){

	bool x,y = false;

	for(unsigned i = 0; i < input.size(); i++){
		if(isdigit(input.at(i))){
			x = true;
		}else if(input.at(i) == 'd' || input.at(i) == 'D'){
			y = true;
		}
	}

	if(x && y){
		return true;
	}else{
		return false;
	}
}

bool hasNum(string input){
	for(unsigned i = 0; i < input.size(); i++){
		if(isdigit(input.at(i))){
			return true;
		}
	}
	return false;
}


///////////////ROLLS

int Hash(string input){

	int x = 0;

	for(unsigned i = 0; i < input.size(); i++){
		x += toupper(input.at(i));
	}

	x = x % 500;

	return x;


}

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

////BUILD AND SEARCH FOR CREATURE

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

////////Build and Search for Spells


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








////////////FOR ROLLERS



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








/////EXTRA


int main(){
vector<spell*> lib;
vector<Creat*> creature;
build_c(creature);
build(lib);
srand(time(NULL));
string input;
cout << "Enter dice roll or spell name. \n To search a Creature, add a ! to the beginning of the name. \n To roll a d20, just hit enter. Enter \"exit\" to exit the program\n\n";

getline(cin,input);

cout << endl << endl;



while(input != "exit" && input != "EXIT"){
	
	auto start = high_resolution_clock::now(); 

	if(IsRoll(input) || hasNum(input)){
		//Roll(input);
		input = parse(input);
		Roller(input);
	}else if(input == ""){
		Roller("d20");
	}else if(input.at(0) == '!'){
		input.erase(0,1);
		searchC(creature, input);
	}else{
		search(lib, input);
	}

	 auto stop = high_resolution_clock::now();

	  auto duration = duration_cast<microseconds>(stop - start); 
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 

	
	cout << "Enter dice roll or spell name. \n To search a Creature, add a ! to the beginning of the name. \n To roll a d20, just hit enter. Enter \"exit\" to exit the program\n\n";

	getline(cin, input);

	cout << endl << endl;

}

for(unsigned i = 0; i < lib.size(); i++){
	if(lib.at(i) != nullptr){
	delete lib.at(i);
	}
}



return 0;

}