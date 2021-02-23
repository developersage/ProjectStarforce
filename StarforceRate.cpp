// StarforceRate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <random>
using namespace std;

void display(int, int);
static int get_input();
void starforce(int,int,bool,bool);

enum type { boom, fail, success };
type run(int,bool,bool);

default_random_engine gen;
uniform_int_distribution<int> range(1, 10000); //int random_num = range(gen);

int main()
{
	string continu;
	do {
		system("cls");
		cout << "    Starforce  SafeGuard  StarCatch" << endl;
		cout << "1.  15 -> 20       X          X    " << endl;
		cout << "2.  15 -> 20       X          O    " << endl;
		cout << "3.  15 -> 20       O          X    " << endl;
		cout << "4.  15 -> 20       O          O    " << endl;
		cout << "5.  20 -> 22       X          X    " << endl;
		cout << "6.  20 -> 22       X          O    " << endl;
		cout << "7.  15 -> 22       X          X    " << endl;
		cout << "8.  15 -> 22       X          O    " << endl;
		cout << "9.  15 -> 22       O          X    " << endl;
		cout << "10. 15 -> 22       O          O    " << endl;
	
		switch (get_input()) { //
		case 1:
			starforce(15, 20, false, false); break;
		case 2:
			starforce(15, 20, false, true); break;
		case 3:
			starforce(15, 20, true, false); break;
		case 4:
			starforce(15, 20, true, true); break;
		case 5:
			starforce(20, 22, false, false); break;
		case 6:
			starforce(20, 22, false, true); break;
		case 7:
			starforce(15, 22, false, false); break;
		case 8:
			starforce(15, 22, false, true); break;
		case 9:
			starforce(15, 22, true, false); break;
		case 10:
			starforce(15, 22, true, true); break;
		}

		cout << "Try again? (Y/N)" << endl;
		getline(cin, continu);
	} while (continu == "y" || continu == "Y");
	return 0;
}

void display(int reached, int boomed){
	double rate = static_cast<double>(boomed) / (boomed + reached) * 100;
	cout << "The booming rate is " << rate << "." << endl;
}

static int get_input() {
	string input;
	bool fail;
	do {
		fail = false;
		getline(cin, input);
		if (input.length() == 0) {
			fail = true;
		}
		else {
			for (unsigned i = 0; i < input.length(); i++) {
				if (!isdigit(input[i])) {
					fail = true;
				}
			}
		}
		if (fail) {
			cout << "Type numbers only." << endl;
		}
	} while (fail);	
	return stoi(input);
}

void starforce(int start, int end, bool safe_guard, bool star_catch) {

	cout << "Type how many attempt." << endl;
	int input = get_input();
	

	int current_star, chance_time, attempt = 0, reached = 0, boomed = 0;
	bool fin;

	type state;
	while (attempt != input) {
		attempt++;
		current_star = start;
		fin = false;
		chance_time = 0;
		do {
			if (chance_time == 2) {
				state = success;
				chance_time = 0;
			}
			else {
				state = run(current_star, safe_guard, star_catch);
			}
			if (state == boom) {
				fin = true;
				boomed++;
			}
			else if (state == fail) {
				if (!(current_star == 15 || current_star == 20)) {
					current_star--;
					chance_time++;
				}
			}
			else { //success
				if (current_star != end) {
					current_star++;
				}
				else {
					reached++;
					fin = true;
				}
			}
		} while (!fin);
		system("cls");
		cout << "Success: " << reached << endl;
		cout << "Boomed:  " << boomed << endl;
	}

	display(reached, boomed);
}

type run(int stars, bool safe_guard, bool star_catch) {

	type gamble[10000];

	switch (stars) {
	case 15:
	case 16:
	case 17:
		//success = 3000; fail = 6790; boom = 210; 1.35 - 1.29 = 0.06 
		//success = 3135; fail = 6661 boom = 204
		for (unsigned i = 0; i < 10000; i++) {
			if (i < 204) {
				if (safe_guard && stars != 17) {
					gamble[i] = fail;
				}
				else {
					gamble[i] = boom;
				}
			}
			else if (i < 6865) {
				if (!star_catch && i < 210) {
					gamble[i] = boom;
				}
				else {
					gamble[i] = fail;
				}
			}
			else {
				if (!star_catch && i < 7000) {
					gamble[i] = fail;
				}
				else {
					gamble[i] = success;
				}
			}
		}
		break;
	case 18:
	case 19:
		//success = 3000; fail = 6720; boom = 280;
		//success = 3135; fail = 6591 boom = 274
		for (unsigned i = 0; i < 10000; i++) {
			if (i < 274) {
				gamble[i] = boom;
			}
			else if (i < 6865) {
				if (!star_catch && i < 280) {
					gamble[i] = boom;
				}
				else {
					gamble[i] = fail;
				}
			}
			else {
				if (!star_catch && i < 7000) {
					gamble[i] = fail;
				}
				else {
					gamble[i] = success;
				}
			}
		}
		break;
	case 20:
	case 21:
		//success = 3000; fail = 6300; boom = 700;
		//success = 3135; fail = 6171 boom = 694
		for (unsigned i = 0; i < 10000; i++) {
			if (i < 694) {
				gamble[i] = boom;
			}
			else if (i < 6865) {
				if (!star_catch && i < 700) {
					gamble[i] = boom;
				}
				else {
					gamble[i] = fail;
				}
			}
			else {
				if (!star_catch && i < 7000) {
					gamble[i] = fail;
				}
				else {
					gamble[i] = success;
				}
			}
		}
	}
	return gamble[range(gen) - 1];
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
