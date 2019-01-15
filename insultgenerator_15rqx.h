/*
 * insultgenerator_netid.h
 *
 *  Created on: Oct 4, 2018
 *      Author: Richard
 */
#pragma once
#include <string>
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <vector>
#ifndef INSULTGENERATOR_15RQX_H_
#define INSULTGENERATOR_15RQX_H_

class FileException { //exception class for File
public:
	FileException(const string&); //constructor
	string what() const;

private:
	string message; //
};

class NumInsultsOutOfBounds {
public:
	NumInsultsOutOfBounds(const string&);
	string what() const;
private:
	string message;
};

class InsultGenerator {
public:
	InsultGenerator(); //function declaration
	void initialize();
	string talkToMe();
	vector<string> generate(const int n);
	vector<string> generateAndSave(const string s, const int n);

private:
	int generateRandNum();
	vector<string> col1, col2, col3, foo,insultList;

};



#endif /* INSULTGENERATOR_15RQX_H_ */
