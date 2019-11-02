//Christopher Fong
//hangman.cpp
//Purpose: Contains the methods of the class Hangman
#include <iostream>
#include <string>
#include <fstream>		//Contains ifstream
#include <cstdlib>		//Contains rand() and srand()
#include <ctime>		//Conatins time()
#include "hangman.h"

using namespace std;

bool Hangman::initializeFile(string filename)
{
	gameNum = 0;	//Game number is reset to 0.
	wins = 0;	//Win total reset to 0.
	loses = 0;	//Loss total reset to 0.
	size = 0;	//File size reset to 0;
	
	for(int i = 0; i < MAX_SIZE; i++)		//Makes all the exculded random indexes set to false.
		excludeIndex[i] = false;

	ifstream inFile;
	inFile.open(filename, ios::in);			//Opens the files to be read.
	inFile.seekg(0, ios::beg);			//Starts from the position 0 and the beginning line of file.
	string inWord;	

	if(!inFile.is_open())				//If program cannot open file it returns false.
		return false;

	while(inFile >> inWord && size < MAX_SIZE)	//Each line of the file is read and inputed temperarily in inWord then is set in the array wordList maximum of MAX_SIZE times.
		wordList[size++] = inWord;

	inFile.close();					//Closes the accessed file.

	return true;
}

void Hangman::displayStatistics()
{
	wordsLeft = size - gameNum;			//Amount of words left is the total amount of available words minus the amount of words already played.
	cout << "\nGame Statistics";
	cout << "\nGames won: " << wins;
	cout << "\nGames lost: " << loses;
	cout << "\nWords read from file: " << gameNum;
	cout << "\nWords available for play: " << wordsLeft << endl;
}

bool Hangman::newWord()
{
	int randNum = 0;			//Random number integer
	wrong = 0;
	numUsed = 0;

	for(int i = 0; i < MAX_SIZE; i++)	//Resets letterFound
		letterFound[i] = false;

	for(int i = 0; i < ALPHABET_SIZE; i++)	//Resets letters used
		used[i] = ' ';

	if(gameNum == size)			//Returns false if there are no more new words to be played
		return false;

	srand((int)time(0));			//Random number generator seed

	randNum = rand() % size;

	while(excludeIndex[randNum])		//Keep generating a new random number until it does not match any of the previously generated numbers
		randNum = (rand() % size);

	excludeIndex[randNum] = true;
	word = wordList[randNum];		
	lettersLeft = word.length();

	return true;
}

void Hangman::displayGame()
{
	//Start of display.
	body[0]  = "    ----   \n";
	body[1]  = "    |  |   \n";
	body[2]  = "       |   \n";
	body[3]  = "       |   \n";
	body[4]  = "       |   \n";
	body[5]  = "       |   \n";
	body[6]  = "       |   \n";
	body[7]  = "       |   \n";
	body[8]  = "_______|___\n";

	//Bad guesses - total 7.
	body[9]  = "    O  |   \n";
	body[10] = "    |  |   \n";
	body[11] = "   -|  |   \n";
	body[12] = "   -|- |   \n";
	body[13] = "    |  |   \n";
	body[14] = "   /   |   \n";
	body[15] = "   / \\ |   \n";
	
	cout << body[0];
	cout << body[1];
	if(wrong == 7)			//7 wrong guesses
	{
		cout << body[9];
		cout << body[10];
		cout << body[12];
		cout << body[13];
		cout << body[15];
		cout << body[7];
		cout << body[8];
	}
	else if(wrong == 6)		//6
	{
		cout << body[9];
		cout << body[10];
		cout << body[12];
		cout << body[13];
		cout << body[14];
		cout << body[7];
		cout << body[8];
	}
	else if(wrong == 5)		//5
	{
		cout << body[9];
		cout << body[10];
		cout << body[12];
		cout << body[13];
		cout << body[6];
		cout << body[7];
		cout << body[8];
	}
	else if(wrong == 4)		//4
	{
		cout << body[9];
		cout << body[10];
		cout << body[12];
		cout << body[5];
		cout << body[6];
		cout << body[7];
		cout << body[8];
	}
	else if(wrong == 3)		//3
	{
		cout << body[9];
		cout << body[10];
		cout << body[11];
		cout << body[5];
		cout << body[6];
		cout << body[7];
		cout << body[8];
	}
	else if(wrong == 2)		//2
	{
		cout << body[9];
		cout << body[10];
		cout << body[4];
		cout << body[5];
		cout << body[6];
		cout << body[7];
		cout << body[8];
	}
	else if(wrong == 1)		//1
	{
		cout << body[9];
		cout << body[3];
		cout << body[4];
		cout << body[5];
		cout << body[6];
		cout << body[7];
		cout << body[8];
	}
	else				//0
	{
		cout << body[2];
		cout << body[3];
		cout << body[4];
		cout << body[5];
		cout << body[6];
		cout << body[7];
		cout << body[8];
	}

	cout << endl;;

	for(int i = 0; i < (int)word.length(); i++)		//Prints out dashed lines with correct letter if they have been guessed
	{
		if(letterFound[i])
			cout << word[i];
		else
			cout << "_";
		cout << " ";
	}
	cout << endl << endl;
	for(int i = 0; i < ALPHABET_SIZE; i++)			//Prints out the available letter choices left to be used
	{
		int p;
		for(p = 0; p < (int)sizeof(used); p++)
		{
			if(ALPHABET[i] == used[p])
			{
				cout << " ";
				break;
			}
		}
		if(ALPHABET[i] != used[p])
			cout << ALPHABET[i];
		cout << " ";
	}
	cout << endl << endl;
		
}

bool Hangman::guess(char letter, bool& done, bool& won)
{
	int count;
	bool valid = false;
	bool correct = false;

	letter = toupper(letter);				//Changes user input to a capital char

	for(int i = 0; i < ALPHABET_SIZE; i++)			//Checks if user input is a valid letter
	{
		if(ALPHABET[i] == letter)
		{
			valid = true;
			break;
		}
	}

	if(valid)
	{
		for(int i = 0; i < numUsed; i++)		//Checks if the letter has already been used
		{
			if(letter == used[i])
				return false;	
		}

		used[numUsed++] = letter;

		for(int i = 0; i < (int)word.length(); i++)			//Checks if the guessed letter is in the answer word
		{
			count = 0;
			if(letter == word[i])
			{
				correct = true;
				for(int p = i; p < (int)word.length(); p++)	//If letter is in the word, checks how many times the letter occurs in the answer word
				{
					if(letter == word[p])
					{
						count++;
						letterFound[p] = true;
					}
				}
				break;
			}
		}
		if(correct)
		{
			cout << "Correct\n\n" << endl;
			lettersLeft -= count;
			if(lettersLeft == 0)					//If no letters remain to be found game is won
			{
				gameNum++;
				done = true;
				won = true;
				wins++;
			}
			return true;
		}

		else
		{
			wrong++;
			if(wrong == MAX_WRONG)					//If max number of wrong guesses is reached game is over
			{
				gameNum++;
				done = true;
				loses++;
			}
			return false;
		}
	}

	return false;
}
void Hangman::revealWord()
{
	cout << "\nThe word is...." << word << endl;
}

