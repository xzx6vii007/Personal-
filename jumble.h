/*
 * jumble.h
 *
 *  Created on: Nov 15, 2018
 *      Author: Richard
 */
#include <iostream>
#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <vector>
using namespace std;
#pragma once
#ifndef JUMBLE_H_
#define JUMBLE_H_

typedef char* charArrayPtr;

class BadJumbleException : public std::exception {  //exception for invalid fraction
public:
	BadJumbleException(const string&); //constructor
	string what();

private:
	string message; //
};

class JumblePuzzle{
public:
	JumblePuzzle(const string&,const string&);
	JumblePuzzle(const JumblePuzzle&);
	~JumblePuzzle();
	int getSize();
	charArrayPtr* getJumble() const;
	int getRowPos();
	int getColPos();
	char getDirection();

	JumblePuzzle& operator=(const JumblePuzzle&);

private:
	int size;
	int row;
	int col;
	string keyword;
	char direction;
	charArrayPtr* crossword;
	void create(string);

};




#endif /* JUMBLE_H_ */
