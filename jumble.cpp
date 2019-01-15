/*
 * juimble.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Richard
 */
#include "jumble.h"
typedef char* charArrayPtr;

BadJumbleException::BadJumbleException(const string& m): //exception constructor
				message(m) {
		}

string BadJumbleException::what(){//exception message
	return message;
}


JumblePuzzle::~JumblePuzzle(){
	for (int i=0; i<this->size; i++){ //frees heap memory
	    delete [] crossword[i]; //delete current index
		crossword[i] = nullptr;}
	delete [] crossword; //delete array
	crossword = nullptr;
}

JumblePuzzle::JumblePuzzle(const string& word, const string& difficulty){

	if(word.size() < 3 || word.size() > 10 ){ //checks if word is valid length
		throw BadJumbleException("Invalid input");
		return;
	}


	keyword = word; //assigns variables
	row =0;
	col =0;

	if(difficulty=="easy"){ //checks difficulty to find size
		size = (int)word.size()*2;
	}
	else if( difficulty == "medium"){
		size = (int)word.size()*3;
	}
	else if( difficulty == "hard"){
		size = (int)word.size()*4;
	}
	else{
		throw BadJumbleException("Invalid difficulty"); //checks for valid difficulty
	}
	crossword = new charArrayPtr[size]; //create 2d array

	create(word); //sets up puzzle

}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& Progenitor){
	keyword = Progenitor.keyword;//assigns variables
	size = Progenitor.size;
	col = Progenitor.col;
	row = Progenitor.row;
	direction = Progenitor.direction;
	crossword =  new charArrayPtr; //creates 2d array

	if (Progenitor.getJumble()) { //loops through parent array and copies index
			crossword = new char*[size];
			for (int i=0; i<size; i++)
				crossword[i] = new char[size];
			for (int i=0; i<size; i++) {
				for (int j=0; j<size; j++) {
					crossword[i][j] = Progenitor.getJumble()[i][j];
				}
			}
		}

}

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& right){
	if (this != &right){
		for (int i=0; i<this->size; i++){ //deletes current array
		    delete [] this->crossword[i];
			this->crossword[i] = nullptr;}
		delete [] this->crossword;
		this->crossword = nullptr;

		keyword = right.keyword; //assigns variables
		size = right.size;
		col = right.col;
		row = right.row;
		crossword =  new charArrayPtr; //creates new array

		for (int i = 0; i < this->size; i++){ //copies assigner array
			this->crossword[i][0] = right.crossword[i][0];
			for (int j = 0; j < this->size; j++){
				this->crossword[i][j] = right.crossword[i][j];
			}
		}
	}
	return *this;
}


int JumblePuzzle::getSize(){ //size accessor
	return this->size;
}

charArrayPtr* JumblePuzzle::getJumble() const{ //accessor for array
		charArrayPtr* clone = new char*[size];
		for (int i=0; i<size; i++) //creates clone of parent array
			clone[i] = new char[size];
		for (int i=0; i<size; i++) {
			for (int j=0; j<size; j++) {
				clone[i][j] = crossword[i][j];
			}
		}
		return clone;
}

void JumblePuzzle::create(string word){ //sets up puzzle

	int dir = rand() % 4;
	bool foo= true;
	string directions = "nesw"; //chooses direction

	direction = directions[dir];

	for ( int i=0; i<size; i++) //fills array with random letters
			crossword[i] = new char[size];
		for (int i=0; i<size; i++) {
			for (int j=0; j<size; j++) {
				crossword[i][j] = rand() % 26 + 'a';
			}
		}

	while (foo){ //infinite loop
		row = rand()%size; //choose starting point
		col = rand()%size;
		int temp = row;
		int temp2 = col;

		if(direction == 's'){
		for (int count = 0; count < word.length(); count++) {
			if(temp+1 > size-1){ foo = !foo; break;} //if current index is out of bound break for loop and changes bool condition
				crossword[temp][col] = word[count]; //sets index to input word character
				temp += 1;
			}
		}

		else if(direction == 'n'){
			for (int count = 0; count < word.length(); count++) { //if current index is out of bound break for loop and changes bool condition
				if(temp-1 <0){ foo = !foo; break;}
							crossword[temp][col] = word[count];//sets index to input word character
							temp += -1;
						}
		}

		else if(direction == 'e'){
			for (int count = 0; count < word.length(); count++) {//if current index is out of bound break for loop and changes bool condition
				if(temp2+1 > size-1){ foo = !foo; break;}
							crossword[row][temp2] = word[count];//sets index to input word character
								temp2 += 1;}
			}

		else {
			for (int count = 0; count < word.length(); count++) {//if current index is out of bound break for loop and changes bool condition
				if(temp2-1 < 0){ foo = !foo; break;}
					crossword[row][temp2] = word[count];//sets index to input word character
							temp2 += -1;}
			}
		foo = !foo; //changes bool character to true if false to iterate again, if true ends loop this ensures entire word is printed
	}

}

char JumblePuzzle::getDirection(){ //accessor
	return this->direction;
}

int JumblePuzzle::getRowPos(){//accessor
	return this->row;
}

int JumblePuzzle::getColPos(){
	return this->col;//accessor
}



