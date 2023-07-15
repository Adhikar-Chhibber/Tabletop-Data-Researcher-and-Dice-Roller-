#include "Creature.h"
#include "Spell.h"
#include "General.h"
#include "Node.h"
#include "Roller.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

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