// tic tac toe.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const char X = 'X'; //сокращенная запись первого участника игры
const char O = 'O'; //сокращенная запись второго участника игры
const char EMPTY = ' '; //пустая клетка на игровом поле
const char TIE = 'T'; //ничейный исход игры
const char NO_ONE = 'N'; //в игре пока никто не победил

void instructions();
char askYesNo(string question);//просто вопрос с ответом да/нет
int askNumber(string question, int high, int low = 0); //запрос числа из диапозона для хода
char humanPiece(); //спрашивает у пользователя будет ли он ходить первым, и если да, то пользователь ходит крестиками первым
char opponent(char piece); //делает вывод о том какой фигурой будет ходить компьютер
void displayBoard(const vector <char>& board); //отображение игрового поля
char winner(const vector <char>& board); //определение победителя игры
bool isLegal(const vector <char>& board, int move);//определение хода - по правилам ли был сделан ход
int humanMove(const vector <char>& board, char human); //узнать ход пользователя
int computerMove(vector <char> board, char computer);//узнать ход компьютера
void announceWinner(char winner, char computer, char human);//поздравление победителя, или объявление ничьей

int main()
{   
	char answer;
	do {
		int move;
		const int NUM_SQUARES = 9;
		vector <char> board(NUM_SQUARES, EMPTY);
		instructions();
		char human = humanPiece();
		char computer = opponent(human);
		char turn = X;
		displayBoard(board);
		while (winner(board) == NO_ONE) {
			if (turn == human) {
				move = humanMove(board, human);
				board[move] = human;
			}
			else {
				move = computerMove(board, computer);
				board[move] = computer;
			}
			displayBoard(board);
			turn = opponent(turn);
		}
		announceWinner(winner(board), computer, human);
		cout << "Do u want to repeat the game?)" << " (y/n)";
		cin >> answer;
	} while (answer == 'y');
	return 0;
} 

void instructions() {
	cout << "Welcome to the Tic-tac_toe" << endl;
	cout << "Make your move known by entering a number, 0-8. ";
	cout << "The number corresponds to the desired board position, as illustrated:" << endl;
	cout << "0 | 1 | 2 " << endl;
	cout << "----------" << endl;
	cout << "3 | 4 | 5 " << endl;
	cout << "----------" << endl;
	cout << "6 | 7 | 8 " << endl;
	cout << "Okay, dude, let's start our battle!" << endl;
}

char askYesNo(string question){
	char responce;
	do {
		cout << question << " (y/n): ";
		cin >> responce;
	} while (responce != 'y' && responce != 'n');
	return responce;
}

int askNumber(string question, int high, int low) {
	int number;
	do {
		cout << question << " (" << low << " - " << high << "); " << endl;
		cin >> number;
	} while (number > high || number < low);
	return number;
}

char humanPiece() {
	char go_first = askYesNo("Do u requuire the firt move?");
	if (go_first == 'y') {
		cout << "Okay, take the first move. U will need this" << endl;
		return X;
	}
	else {
		cout << "Okay, I will start first!" << endl;
		return O;
	}
}

char opponent(char piece) {
	if (piece == X) {
		return O;
	}
	else {
		return X;
	}
}

void displayBoard(const vector <char>& board) {
	cout << endl;
	cout << board[0] << " | " << board[1] << " | " << board[2] << endl;
	cout << "----------" << endl;
	cout << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "----------" << endl;
	cout << board[6] << " | " << board[7] << " | " << board[8] << endl;
	cout << endl;
}

char winner(const vector <char>& board) {
	const int WINNING_ROWS[8][3] = { {0, 1, 2},
	{3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6} };

	const int TOTAL_ROWS = 8;

	for(int row = 0; row < TOTAL_ROWS; ++row){
		if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) && 
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])) {
			return board[WINNING_ROWS[row][0]];
		}
	}

	if (count(board.begin(), board.end(), EMPTY) == 0) {
		return TIE;
	}

	return NO_ONE;
}

inline bool isLegal(int move, const vector<char>& board) {
	return (board[move] == EMPTY);
}

int humanMove(const vector <char>& board, char human) {
	int move = askNumber("Where will u move?", (board.size() - 1));
	while (!isLegal(move, board)) {
		cout << "that square is already occupied" << endl;
		move = askNumber("Where will u move?", (board.size() - 1));
	}
	cout << "Fine..." << endl;
	return move;
}

int computerMove(vector <char> board, char computer) {
	unsigned int move = 0;
	bool found = false;
	while (!found && move < board.size()) {
		if (isLegal(move, board)) {
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}
		if (!found) {
			++move;
		}
	}

	if (!found) {
		move = 0;
		char human = opponent(computer);
		while (!found && move < board.size()) {
			if (isLegal(move, board)) {
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}
			if (!found) {
				++move;
			}
		}
	}

	if (!found) {
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
			while (!found && i < board.size())
			{
				move = BEST_MOVES[i];
				if (isLegal(move, board))
				{
					found = true;
				}
				++i;
			}
	}

	cout << "I shall take square number " << move << endl;
	return move;
}

void announceWinner(char winner, char computer, char human)
{
	if (winner == computer) {
		cout << winner << "'s won!" << endl;
		cout << "As I predicted, human, I am triumphant once more -- proof" << endl;
		cout << "that computers are superior to humans in all regards." << endl;
	}
	else if (winner == human) {
		cout << winner << "'s won!" << endl;
		cout << "No, way! It cannot Ье! Somehow you tricked me, human." << endl;
		cout << "But never again! I - the computer -  so swear it!" << endl;
	}
	else {
		cout << "It's а tie." << endl;
		cout << "You were most lucky, human, and somehow managed to tie me." << endl;
		cout << "Celebrate... for this is the best you will ever achieve." << endl;
	}
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
