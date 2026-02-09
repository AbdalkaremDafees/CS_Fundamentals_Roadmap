/* Write a small game program for Store-Paper-Scissor */

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Purpose: Defines the choices available in the game.
enum enGameChoice {stone = 1, paper = 2, scissors = 3};

// Purpose: Defines possible winners for a round or game.
enum enWinner {Player = 1, Computer = 2, Draw = 3};

// get rounds number from user
short roundNumberFunc() {
	short RNumber;
	cout << "How many rounds 1 to 10 ? ";
	do {
		cin >> RNumber;
	} while (RNumber > 10 || RNumber < 1);
	return RNumber;
}

// get player choice (storn - paper - scissors)
short playerChoiceFunc(short ctrRound) {
	cout << "\nRound [" << ctrRound << "] begins: \n";

	short PC;
	cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
	cin >> PC;
	return PC;
}

// get a random number between (from - to) user defined
short computerChoiceFunc(short from, short to) {
	short CC = rand() % (to - from + 1) + from;
	return CC;
}

// return who is the winner (player - computer - draw )
short roundWinnerFunc(short playerChoice, short computerChoice, short &playerWinCtr, short &computerWinCtr, short &drawCtr) {
	if(playerChoice == computerChoice) {
		drawCtr++;
		system("color 6F");
		return enWinner::Draw;
	}
	else if ((playerChoice == 1 && computerChoice == 3) || (playerChoice == 2 && computerChoice == 1) || (playerChoice == 3 && computerChoice == 2)) {
		playerWinCtr++;
		system("color 2F");
		return enWinner::Player;
	}
	else {
		computerWinCtr++;
		cout << '\a';
		system("color 4F");
		return enWinner::Computer;
	}
}

// print what user choice
void printPlayerChoice(short playerChoice) {
	if(playerChoice == enGameChoice::stone)
		cout << "\nPlayer Choice   : " << "Stone";
	else if(playerChoice == enGameChoice::paper)
		cout << "\nPlayer Choice   : " << "Paper";
	else
		cout << "\nPlayer Choice   : " << "scissors";
}

// print what computer choice
void printComputerChoice(short computerChoice) {
	if (computerChoice == enGameChoice::stone)
		cout << "\nComputer Choice : " << "Stone";
	else if (computerChoice == enGameChoice::paper)
		cout << "\nComputer Choice : " << "Paper";
	else
		cout << "\nComputer Choice : " << "scissors";
}

// print who is winner in current round
void printRoundWinner(short roundWinner) {
	if (roundWinner == enWinner::Player)
		cout << "\nRound Winner    : " << "[Player]";
	else if (roundWinner == enWinner::Computer)
		cout << "\nRound Winner    : " << "[Computer]";
	else
		cout << "\nRound Winner    : " << "[Draw]";
}

// print who is winner in all round
void printRoundResult(short roundNumber, short playerChoice, short computerChoice, short roundWinner) {
	cout << "\n_________________Round [" << roundNumber << "]_________________\n";

	printPlayerChoice(playerChoice);
	printComputerChoice(computerChoice);
	printRoundWinner(roundWinner);

	cout << "\n__________________________________________________________\n";
}

// style function
void printHead() {
	cout << "\n\t\t__________________________________________________________________________________________";
	cout << "\n\t\t\t\t\t\t+++ G a m e  O v e r +++";
	cout << "\n\t\t__________________________________________________________________________________________";
	cout << "\n\t\t_____________________________________ [Game Results] _____________________________________";

}

// chek for who is the final winner in the game
void checkFinalWinner(short playerWinCtr, short computerWinCtr, short drawCtr) {
	if (playerWinCtr > computerWinCtr && playerWinCtr >= drawCtr) cout << "Player Win";
	else if (computerWinCtr > playerWinCtr && computerWinCtr >= drawCtr) cout << "Computer Win";
	else cout << "Draw";
}

// print all result
void printFinalResult(short roundNumber, short playerWinCtr, short computerWinCtr, short drawCtr) {

	printHead();
	cout << "\n\t\tGame Rounds          : " << roundNumber;
	cout << "\n\t\tPlayer Won Times     : " << playerWinCtr;
	cout << "\n\t\tComputer Won Times   : " << computerWinCtr;
	cout << "\n\t\tDraw Tiems           : " << drawCtr;
	cout << "\n\t\tFinal Winner         : ";
	checkFinalWinner(playerWinCtr, computerWinCtr, drawCtr);

	cout << "\n\t\t__________________________________________________________________________________________";
}

void repeatGame(char &repeat) {
	cout << "\n\t\tDo you want to play again? Y/N? ";
	cin >> repeat;
	cout << endl;
}

void startGame() {
	char repeat;

	do {
		system("cls");
		system("color 0F");
		short roundNumber = roundNumberFunc();
		short ctrRound = 0, playerWinCtr = 0, computerWinCtr = 0, drawCtr = 0;

		while (roundNumber != ctrRound) {
			++ctrRound;
			short playerChoice = playerChoiceFunc(ctrRound);
			short computerChoice = computerChoiceFunc(1, 3);
			short roundWinner = roundWinnerFunc(playerChoice, computerChoice, playerWinCtr, computerWinCtr, drawCtr);
			printRoundResult(ctrRound, playerChoice, computerChoice, roundWinner);
		}
		printFinalResult(roundNumber, playerWinCtr, computerWinCtr, drawCtr);
		repeatGame(repeat);
	} while (repeat == 'Y' || repeat == 'y');
}

int main()
{
	srand(unsigned(time(NULL)));

	startGame();

	return 0;
}
