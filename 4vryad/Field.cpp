#include"Field.h"
#include <iostream>
using namespace std;
const int Field::di[] = { 1, 0, 1, 1 };
const int Field::dj[] = { 0, 1, -1, 1 };
Field::Field(bool isRedFirst)
{
	clear(isRedFirst);
}
void Field::clear(bool isRedFirst)
{
	isRedTurn = isRedFirst;
	winner = EMPTY;
	gameOver = false;
	for (int i = 0; i < FIELD_HEIGHT; i++)
		for (int j = 0; j < FIELD_WIDTH; j++)
			cells[i][j] = EMPTY;
}
bool Field::makeTurn(int column){
	if (gameOver || column < 1 || column > FIELD_WIDTH)
		return false;
	int j = column - 1; 
	for (int i = FIELD_HEIGHT - 1; i >= 0; i--)
	{
		if (cells[i][j] == EMPTY)
		{
			cells[i][j] = isRedTurn ? RED : YELLOW;
			checkWinner();
			if (!gameOver)
				isRedTurn = !isRedTurn;
			return true;
		}
	}
	return false; 
}
void Field::checkWinner()
{
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			Cell start = cells[i][j];
			if (start == EMPTY) continue;
			for (int k = 0; k < DIR_NUMBER; k++) {
				int length = 0;
				for (int step = 0; step < WIN_LENGTH; step++) {
					int iline = i + step * di[k];
					int jline = j + step * dj[k];
					if (iline < 0 || iline >= FIELD_HEIGHT ||
						jline < 0 || jline >= FIELD_WIDTH)
						break;

					if (cells[iline][jline] != start) break;

					length++;
				}
				if (length == WIN_LENGTH) {
					gameOver = true;
					winner = start;
					return;
				}
			}
		}
	}
}
bool Field::isWon(bool red) const {
	Cell target = red ? RED : YELLOW;
	return gameOver;
}

void Field::print() const {
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {
			if (cells[i][j] == RED)
				cout << "R ";
			else if (cells[i][j] == YELLOW)
				cout << "Y ";
			else 
				cout << ". ";
		}
		cout << "\n";
	}
}

void Field::printResult() const {
	if (gameOver) {
		if (winner == RED) {
			cout << "Победил КРАСНЫЙ игрок!" << endl;
		}
		else if (winner == YELLOW) {
			cout << "Победил ЖЕЛТЫЙ игрок!" << endl;
		}
		else {
			cout << "Ничья!" << endl;
		}
	}
}
bool Field::isRedTurnNow() const {
	return isRedTurn;
}

bool Field::isOver() const {
	return gameOver;
}

Cell Field::getCell(int i, int j) const {
	if (i >= 0 && i < 6 && j >= 0 && j < 7) {
		return cells[i][j];
	}
	return EMPTY;
}

