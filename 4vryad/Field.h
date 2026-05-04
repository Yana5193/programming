#pragma once

enum Cell {
	EMPTY,
	RED,
	YELLOW
};


class Field {
private:
    static const int FIELD_WIDTH = 7;
    static const int FIELD_HEIGHT = 6;
    static const int DIR_NUMBER = 4;
    static const int WIN_LENGTH = 4;
    static const int di[4];
    static const int dj[4];

    Cell cells[FIELD_HEIGHT][FIELD_WIDTH];
    bool isRedTurn; 
    bool gameOver;
    Cell winner;
    void checkWinner();
public:
	Field(bool isRedFirst);
	void clear(bool isRedFirst);
	bool makeTurn(int column); 
	bool isWon(bool red) const; 
	bool isOver() const;
	Cell getCell(int i, int j) const; 
	bool isRedTurnNow() const; 
	void print() const;
	void printResult() const; 
};