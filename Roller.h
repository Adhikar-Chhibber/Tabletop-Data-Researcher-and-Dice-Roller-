#ifndef ROLLER_H
#define ROLLER_H

#include <iostream>
#include <string>
#include <cstdlib>

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



#endif