/*
Regan Hanson -- Section 1 -- reganhanson1994@gmail.com
Description: This program simulates the playing of a plinko game, as done on game shows. The
user chooses which slots and how many chips to use. 
Late days: Please use 2 of my late days. 

Test 1:
Input: (1, string, 5, 5)
Expected output:
Welcome to the Plinko simulator!  Enter 4 to see options.

Enter your selection now:1


*** Drop a single chip ***

Which slot do you want to drop the chip in (0-8)? string

Invalid slot.
Which slot do you want to drop the chip in (0-8)?5


*** Dropping chip into slot 5 ***
Path: [5.0, 5.5, 5.0, 5.5, 5.0, 5.5, 6.0, 5.5, 5.0, 5.5, 6.0, 6.5, 6.0]
Winnings: $1000.00

Enter your selection now:5
Results: Infinite loop after the string. Solved.


Test 2:
Input:(2, -2, 5, 5)
Expected output:
Welcome to the Plinko simulator!  Enter 4 to see options.

Enter your selection now:2


***  Drop multiple chips ***
How many chips do you want to drop (>0)?-2

Invalid number of chips.

How many chips do you want to drop (>0)?5

Which slot do you want to drop the chip in (0-8)? 5
Results: SUCCESS

Test 3:
Input: (3, 1, 5)
Expected output: 
Welcome to the Plinko simulator!  Enter 4 to see options.

Enter your selection now:3


*** Sequentially Drop Multiple Chips ***
How many chips do you want to drop (>0)?1

Total winnings on slot 0 chips: 1000.00
Average winnings per chip: 1000.00
Total winnings on slot 1 chips: 100.00
Average winnings per chip: 100.00
Total winnings on slot 2 chips: 1000.00
Average winnings per chip: 1000.00
Total winnings on slot 3 chips: 1000.00
Average winnings per chip: 1000.00
Total winnings on slot 4 chips: 0.00
Average winnings per chip: 0.00
Total winnings on slot 5 chips: 1000.00
Average winnings per chip: 1000.00
Total winnings on slot 6 chips: 500.00
Average winnings per chip: 500.00
Total winnings on slot 7 chips: 1000.00
Average winnings per chip: 1000.00
Total winnings on slot 8 chips: 0.00
Average winnings per chip: 0.00

Enter your selection now:5
Results: SUCCESS
*/

#include <iostream>
#include <iomanip>
using namespace std;
int const IGNORE = 10000;
int const LEFT_LIMIT = 0;
int const RIGHT_LIMIT = 6;
int const FIRST_PRECISION = 1;
int const SECOND_PRECISION = 2;


int GetMenuOption() {
	int menuInput = 0;
	int const SINGLE = 1;
	int const QUIT = 5;
	cout << "Enter your selection now:";
	cin >> menuInput;
	cout << endl;

	while (cin.fail() || menuInput < SINGLE || menuInput > QUIT) {
		cout << "Invalid selection.  Enter 4 to see options." << endl;
		cin.clear();
		cin.ignore(IGNORE,'\n');
		cout << endl;
		cout << "Enter your selection now:";
		cin >> menuInput;
		cout << endl;
	}

	return menuInput;
}

int GetSlotNum() {
	int slotNumber = 0;	

	cout << "Which slot do you want to drop the chip in (0-" << RIGHT_LIMIT << ")? ";
	cin >> slotNumber;
	while (slotNumber < LEFT_LIMIT || slotNumber > RIGHT_LIMIT || cin.fail()) {
		cout << endl;
		cout << "Invalid slot." << endl;
		cin.clear();
		cin.ignore(IGNORE, '\n');
		cout << "Which slot do you want to drop the chip in (0-" << RIGHT_LIMIT << ")?";
		cin >> slotNumber;
		cout << endl;
	}
	
	return slotNumber;
}

int GetChipNum() {
	int ChipNum = 0;
	
	cout << "How many chips do you want to drop (>0)?";
	cin >> ChipNum;
	cout << endl;
	while (ChipNum <= LEFT_LIMIT || cin.fail()) {
		cout << "Invalid number of chips." << endl;
		cout << endl;
		cin.clear();
		cin.ignore(IGNORE, '\n');
		cout << "How many chips do you want to drop (>0)?";
		cin >> ChipNum;
		cout << endl;
	}
	
		return ChipNum;
}

double ComputeWinnings(int slotNum) {
	double winnings = 0.00;
	const double WINNINGS[] = { 300.00, 200.00, -600.42, 20000.00, 0.01, 800.00, -1400.00 };

	winnings = WINNINGS[slotNum];

	return winnings;
}

double OneChipFalling(double slotNum, bool doPrint) {
	int const NUM_OPTIONS = 2;
	int const PATH_LENGTH = 19;
	double const LEFT_SLIDE = -.5;
	double const RIGHT_SLIDE = .5;
	double const CREATE_SLIDE = .5;
	double leftORRight = 0;
	double slotNumber = 0;
	double winnings = 0;

	for (int i = 1; i < PATH_LENGTH; i++) {
		if (slotNum == LEFT_LIMIT) {
			slotNum += RIGHT_SLIDE;
		}
		else if (slotNum == RIGHT_LIMIT) {
			slotNum += LEFT_SLIDE;
		}
		else {
			leftORRight = (rand() % NUM_OPTIONS) - CREATE_SLIDE;
			slotNum += leftORRight;
		}
		if (doPrint == true) {
			cout << slotNum;
			if (i < PATH_LENGTH - 1) {
				cout << ", ";
			}
		}
	}
	cout << fixed << setprecision(SECOND_PRECISION);
	winnings = ComputeWinnings(slotNum);
	
	return winnings;
}

double MultiChipFalling(int initSlotNum, int numberChips) {
	double slotNumber = 0;
	double winnings = 0;
	double totalWinnings = 0;
	double avgWinnings = 0;
	bool doPrint = false;
	
	for (int i = 0; i < numberChips; i++) {
		if (initSlotNum >= LEFT_LIMIT || initSlotNum <= RIGHT_LIMIT) {
			slotNumber = initSlotNum;
			winnings = OneChipFalling(slotNumber, false);
		}
		cout << fixed << setprecision(SECOND_PRECISION);
		totalWinnings = totalWinnings + winnings;
	}

	return totalWinnings;
}

int main() {
	int const SINGLE = 1;
	int const MULTIPLE = 2;
	int const SHOW_OPTIONS = 4;
	int const MULTIPLE_CHIPS_SLOTS = 3;
	int const QUIT = 5;
	int const RANDOM_SEED = 42;
	int numChips = 0;
	int initialSlotNumber = 0;
	int menuInput = 0;
	double winnings = 0.00;
	double totalWinnings = 0;
	double avgWinnings = 0;
	double slotNumber = 0;
	bool Test = true;


	srand(RANDOM_SEED);
	cout << "Welcome to the Plinko simulator!  Enter 4 to see options." << endl;
	while (menuInput != QUIT) {
		Test = true;
		cout << fixed << setprecision(0);
		cout << endl;
		menuInput = GetMenuOption();
		cout << endl;

		if (menuInput == SINGLE) {
			cout << "*** Drop a single chip ***" << endl;
			cout << endl;
			slotNumber = GetSlotNum();
			cout << endl;
			cout << "*** Dropping chip into slot " << slotNumber << " ***" << endl;
			cout << setprecision(FIRST_PRECISION);
			cout << "Path: [";
			cout << slotNumber << ", ";
			winnings = OneChipFalling(slotNumber, true);
			cout << "]" << endl;
			cout << fixed << setprecision(SECOND_PRECISION);
			cout << "Winnings: $" << winnings << endl;
	
		}
		else if (menuInput == MULTIPLE) {
			totalWinnings = 0;
			cout << "***  Drop multiple chips ***" << endl;
			numChips = GetChipNum();
			slotNumber = GetSlotNum();
			totalWinnings = MultiChipFalling(slotNumber, numChips);
			cout << "Total winnings on " << numChips << " chips: $" << totalWinnings << endl;
			avgWinnings = totalWinnings / (static_cast<double>(numChips));
			cout << "Average winnings per chip: $" << avgWinnings << endl;
		}
		else if (menuInput == SHOW_OPTIONS) {
			cout << "Menu: Please select one of the following options:" << endl;
			cout << endl;
			cout << "1 - Drop a single chip into one slot" << endl;
			cout << "2 - Drop multiple chips into one slot" << endl;
			cout << "3 - Show the options menu" << endl;
			cout << "4 - Quit the program" << endl;
			cout << endl;
		}
		else if (menuInput == MULTIPLE_CHIPS_SLOTS) {
			cout << "*** Sequentially Drop Multiple Chips ***" << endl;
			numChips = GetChipNum();
			for (int i = 0; i <= RIGHT_LIMIT; ++i) {
				totalWinnings = MultiChipFalling(i, numChips);
				cout << "Total winnings on slot " << i << " chips: " << totalWinnings << endl;
				cout << fixed << setprecision(SECOND_PRECISION);
				avgWinnings = totalWinnings / (static_cast<double>(numChips));
				cout << "Average winnings per chip: " << avgWinnings << endl;
			}
			
		}
		
	}
	cout << "Goodbye!";
	
	return 0;
}
