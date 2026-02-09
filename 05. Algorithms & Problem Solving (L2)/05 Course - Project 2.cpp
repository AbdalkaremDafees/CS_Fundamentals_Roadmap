/* Test Your Math Skill Program */
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Define difficulty levels as an enumeration
enum enQuestionLevel { easy = 1, midium = 2, hard = 3, mixLevel = 4 };
// Define mathematical operations as an enumeration
enum enOperation { add = 1, sub = 2, mul = 3, divi = 4, mixOp = 5 };

// Structure to store program configuration from user
struct stProgramInfo {
    short QuestionsNumber;          // Number of questions user wants
    short QuestionsLevelInput;      // Difficulty level choice
    short QusetionOperationInput;   // Operation type choice
};

// Collect user preferences for the quiz
stProgramInfo getInfo() {
    stProgramInfo userInput;
    cout << " How many question do you want? ";
    cin >> userInput.QuestionsNumber;
    cout << " Enter question level [easy = 1, midium = 2, hard = 3, mixLevel = 4]: ";
    cin >> userInput.QuestionsLevelInput;
    cout << " Enter question operation [add = 1, sub = 2, mul = 3, div = 4, mixOp = 5]: ";
    cin >> userInput.QusetionOperationInput;
    cout << endl;

    return userInput;
}

// Generate random number within specified range
int randomNum(short from, short to) {
    return rand() % (to - from + 1) + from;
}

// Generate random number based on selected difficulty level
short getRandomNum(stProgramInfo ProgramInfo) {
    switch (ProgramInfo.QuestionsLevelInput) {
    case enQuestionLevel::easy:
        return randomNum(0, 9);      // Easy: numbers 0-9
    case enQuestionLevel::midium:
        return randomNum(10, 99);    // Medium: numbers 10-99
    case enQuestionLevel::hard:
        return randomNum(100, 999);  // Hard: numbers 100-999
    default:
        return randomNum(0, 150);    // Mix: numbers 0-150
    }
}

// Get operation symbol based on user choice
char getOperation(stProgramInfo ProgramInfo) {
    switch (ProgramInfo.QusetionOperationInput) {
    case enOperation::add:
        return '+';   // Addition
    case enOperation::sub:
        return '-';   // Subtraction
    case enOperation::mul:
        return '*';   // Multiplication
    case enOperation::divi:
        return '/';   // Division
    default:
        // For mixOp, generate random operation symbol from ASCII 42-47
        // (excluding comma and period which are ASCII 44 and 46)
        int RightOp = randomNum(42, 47);
        while (RightOp == 44 || RightOp == 46)
            RightOp = randomNum(42, 47);
        return (char)RightOp;
    }
}

// Calculate result for mixed operation using ASCII value
int mixOperationResult(int n1, int n2, char charOperation) {
    int AsciiOperation = (int)charOperation; // Convert char to ASCII code
    switch (AsciiOperation) {
    case 42:  // ASCII 42 = '*'
        return n1 * n2;
    case 43:  // ASCII 43 = '+'
        return n1 + n2;
    case 45:  // ASCII 45 = '-'
        return n1 - n2;
    default:  // ASCII 47 = '/'
        return n1 / n2;
    }
}

// Calculate correct answer for given operation
short getResult_N1_Op_N2(stProgramInfo Opertaion, int n1, int n2, char charOperation) {
    switch (Opertaion.QusetionOperationInput) {
    case enOperation::add:
        return n1 + n2;
    case enOperation::sub:
        return n1 - n2;
    case enOperation::mul:
        return n1 * n2;
    case enOperation::divi:
        if (n2 == 0) return n1 / 1;  // Avoid division by zero
        return n1 / n2;
    default:
        return mixOperationResult(n1, n2, charOperation);
    }
}

// Check if user's answer is correct and update score
void checkAnswer(int answer, int number1, int number2, int& RightAnswerCtr, int& WrongAnswerCtr, stProgramInfo ProgramInfo, char charOperation) {
    int result = getResult_N1_Op_N2(ProgramInfo, number1, number2, charOperation);

    if (answer == result) {
        cout << "\nRight answer.";
        system("color 2F");  // Green background for correct answer
        RightAnswerCtr++;
    }
    else {
        cout << "\nWrong answer.";
        system("color 4F");  // Red background for wrong answer
        WrongAnswerCtr++;
    }
}

// Convert level choice number to descriptive string
string QuestionsLevel(short choice) {
    string arrQuestionsLevel[4] = { "easy", "midium", "hard", "mix level" };
    return arrQuestionsLevel[choice - 1];
}

// Convert operation choice number to descriptive string
string QuestionsOperation(short choice) {
    string arrQuestionsOperation[5] = { "addition", "substract", "multiplication", "division", "mix operation" };
    return arrQuestionsOperation[choice - 1];
}

// Display final results summary
void printOverScreen(stProgramInfo ProgramInfo, int Rctr, int Wctr) {
    cout << "\n\n_______________________\n";
    cout << "\n Final Result Pass :-) ";
    cout << "\n______________________\n";
    cout << "\nNumber of question: " << ProgramInfo.QuestionsNumber;
    cout << "\nLeve of question: " << QuestionsLevel(ProgramInfo.QuestionsLevelInput);
    cout << "\nOpertation of question: " << QuestionsOperation(ProgramInfo.QusetionOperationInput);
    cout << "\nRight answer: " << Rctr;
    cout << "\nWrong ansewr: " << Wctr;
    cout << "\n_______________________";
}

// Main quiz execution - generates questions and collects answers
void showProgramScreen(stProgramInfo ProgramInfo) {
    int N1 = 0, N2 = 0, Answer = 0, Rctr = 0, Wctr = 0;
    char Operation;

    for (int i = 1; i <= ProgramInfo.QuestionsNumber; i++) {
        N1 = getRandomNum(ProgramInfo), N2 = getRandomNum(ProgramInfo);
        Operation = getOperation(ProgramInfo);
        if (N2 > N1) swap(N1, N2);  // Ensure larger number first for subtraction/division
        cout << "\n\n Question [" << i << "/" << ProgramInfo.QuestionsNumber << "]\n";
        cout << N1 << '\n' << N2 << '\t' << Operation << '\n' << "__________\n";
        cin >> Answer;
        checkAnswer(Answer, N1, N2, Rctr, Wctr, ProgramInfo, Operation);
    }

    printOverScreen(ProgramInfo, Rctr, Wctr);
}

// Clear screen and reset colors for new game
void resetScreen() {
    system("cls");
    system("color 0F");
}

// Main program loop with replay option
void startProgram() {
    char repeat = 'Y';
    do {
        resetScreen();
        showProgramScreen(getInfo());

        cout << "\n\nDo you want to play again? ";
        cin >> repeat;

    } while (repeat == 'y' || repeat == 'Y');
}

// Entry point - seed random generator and start program
int main()
{
    srand(unsigned(time(NULL)));  // Initialize random seed

    startProgram();

    return 0;
}