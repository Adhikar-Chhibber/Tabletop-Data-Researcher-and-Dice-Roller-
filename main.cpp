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
	for(i = 0; input.at(i) != 'd' && input.at(i) != 'D' && i != input.size(); i++){
		times.push_back(input.at(i));
		
	}

	if(i == input.size()){
		return stod(times, nullptr);
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



void breaker(string input, vector<string>& type, vector<string>& real){

	string x;

	for(unsigned i = 0; i < input.size(); i++){

		if(input.at(i) == '+'){
			if(real.size() == 0){
				x = "+" + x;
			}
			real.push_back(x);
			x = "+";
		}else if(input.at(i) == '-'){
			if(real.size() == 0){
				x = "+" + x;
			}
			real.push_back(x);
			x = "-";
		}else if(input.at(i) == '*' || input.at(i) == 'x'){
			if(real.size() == 0){
				x = "+" + x;
			}
			real.push_back(x);
			x = "*";
		}else if(input.at(i) == '/'){
			if(real.size() == 0){
				x = "+"  + x;
			}
			real.push_back(x);
			x = "/";
		}else{
			x.push_back(input.at(i));
		}		

	}

	if(real.size() == 0){
		x = "+" + x;
	}

	real.push_back(x);

}

void Roller(string input){

	vector<string> t,r;
	int total = 0;
	string temp;

	breaker(input, t, r);

	for(unsigned i = 0; i < r.size(); i++){
		temp = r.at(i);

		/*if(IsRoll(temp)){
			if(temp.at(0) == '+'){
				temp.erase(0,1);
				total += Roll(temp);
			}else if(temp.at(0) == '-'){
				temp.erase(0,1);
				total -= Roll(temp);
			}else if(temp.at(0) == '*'){
				temp.erase(0,1);
				total *= Roll(temp);
			}else if(temp.at(0) == '/'){
				temp.erase(0,1);
				total /= Roll(temp);
			}
		}else{
			if(temp.at(0) == '+'){
				temp.erase(0,1);
				total += stoi(temp);
			}else if(temp.at(0) == '-'){
				temp.erase(0,1);
				total -= stoi(temp);
			}else if(temp.at(0) == '*'){
				temp.erase(0,1);
				total *= stoi(temp);
			}else if(temp.at(0) == '/'){
				temp.erase(0,1);
				total /= stoi(temp);
			}

		}*/

		int x = (int)temp.at(0);
		temp.erase(0,1);
		int holder = Roll(temp);

		switch (x){

			case 42:
			total *= holder;
			break;

			case 43:
			total += holder;
			break;

			case 45:
			total -= holder;
			break;

			case 47:
			total /= holder;
			break;

		}

	}

	cout << "TOTAL: " << total << endl << endl;

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

	if(IsRoll(input)){
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









