/*
 * insultgenerator_netid.cpp
 *
 *  Created on: Oct 4, 2018
 *      Author: Richard
 */

#include "insultgenerator_15rqx.h"
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


InsultGenerator::InsultGenerator() {
} //default constructor

void InsultGenerator::initialize() { //method for reading text file
	string line;
	ifstream fileIn; //declares input filestream variable
	//fileIn.open("C:\\Users\\Richard\\eclipse-workspace\\CMPE320 As1\\src\\InsultsSource.txt"); //opens insult file
	string name = "InsultsSource.txt";
	fileIn.open(name.c_str());
	if (fileIn.fail()) { //checks if file failed
		throw FileException("File failed"); //creates exception
		return;
	}
	stringstream foo3;
	while (!fileIn.eof()) { //while not end of file
		getline(fileIn, line); // read string
		foo3.clear(); //clears error state of input sting stream foo3
		foo3.str(" "); //clears contents of foo3
		foo3 << line; //writes to foo3
		while (foo3 >> line) { //while ss is inserting into line
			foo.push_back(line); //push into vector string foo
		}
	}

	for (int i = 0; i < foo.size(); i += 3) { //push foo into col1,col2,col3
		col1.push_back(foo[i]);
		col2.push_back(foo[i + 1]);
		col3.push_back(foo[i + 2]);
	}
	fileIn.close();
}

int InsultGenerator::generateRandNum() { //generates random number
	int num;
	num = rand() % 49;
	return num;
}

string InsultGenerator::talkToMe() { //creates insult
	int n1, n2, n3;
	n1 = generateRandNum();
	n2 = generateRandNum();
	n3 = generateRandNum();
	string insult;
	insult = "Thou " + col1[n1] + " " + col2[n2] + " " + col3[n3] + "!";
	return insult;
}

vector<string> InsultGenerator::generate(int n) { //generates insults
	if (n > 10000 || n < 1) { //checks if # of insults is within bounds
		throw NumInsultsOutOfBounds("Number of insults out of bounds"); //throws exception
		return vector<string>(); //returns empty string vector
	}
	vector<string> insultList; //declares insult string vector
	while (n > insultList.size()) { //while vector has less than n insults
		string temp(talkToMe()); //generate insult
		insultList.push_back(temp); //inserts insult to vector
	}
		sort(insultList.begin(),insultList.end());//sorts list alphabetically
		insultList.erase(unique(insultList.begin(),insultList.end()),insultList.end()); //erases repeated
	return insultList; //returns list
}

vector<string> InsultGenerator::generateAndSave(string filename, int n) {
	ofstream output(filename);//initialize output file
	vector<string> insultList;
	if(output.fail()){ //checks if file output failed
		throw NumInsultsOutOfBounds("Failed to create output");
				return vector<string>();
	}
	if (n < 1) { //checks if n is within bounds
		throw NumInsultsOutOfBounds("Number of insults is less than 1");
		return vector<string>();
	} else if (n > 10000) {
		throw NumInsultsOutOfBounds("Number of insults is greater than 10000");
		return vector<string>();
	}

	else {
		while (n > insultList.size()) {//generates insuls and isnerts into vector string
			string insult = talkToMe();
			insultList.push_back(insult);
				}
	}

	sort(insultList.begin(),insultList.end()); //sorts list alphabetically
	insultList.erase(unique(insultList.begin(),insultList.end()),insultList.end()); //erases repeated insults

	for(int i=0; i<n; i++){ //for loop to iterate through list
		string foo= insultList[i]; //sets current entry to foo
		output << foo; //writes foo to output file
		output << "\n"; //skips line
	}

	return insultList; //returns insults
}


NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& m) :
		message(m) {
}

string NumInsultsOutOfBounds::what() const {
	return message;
}

FileException::FileException(const string& m) :
		message(m) {
}

string FileException::what() const {
	return message;
}
