#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

int main(){
srand(time(NULL));
string input;
cout << "$ ";

getline(cin,input);

while(input != "q"){

	string times;
	unsigned i;
	for(i = 0; input.at(i) != 'd'; i++){
		times.push_back(input.at(i));
	}

	i++;

	double t;

	if(times.size() != 0){
	 t = stod(times, nullptr);
	}else{
		 t = 1.0;
	}


	times = "";

	for(unsigned k = i; k < input.size(); k++){
		times.push_back(input.at(k));
	}

	int x = stoi(times, nullptr);

	int output = 0;

	for(double ti = 0.0; ti < t; ti++){
		output += ((rand() % x) + 1.0);
	}

	cout << output << endl;

	cout << "$ ";

	getline(cin, input);

}





	return 0;
}