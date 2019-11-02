//Christopher Fong
//p1.cpp
//Purpose: Takes user input and runs the methods of the Hangman class
#include <iostream>
#include <string>
#include "hangman.h"
using namespace std;

int main() 
{
	//Intro to the game
	cout << "Welcome to Hangman!" << endl;
	cout << "Hangman is a game where you guess letters until you win by completing the unknown word, or until you lose by guessing incorectly too many times." << endl;

	//Ask to play
	string cont;
	cout << "\nDo you want to play Hangman (y/n)? ";
	cin >> cont;

	if(cont != "yes" && cont != "y" && cont != "YES" && cont != "Y")
		return 0;

	cout << endl;

	Hangman game;
	bool redo;

	do
	{
		string wordFile;
		cout << "\nEnter a file name that contains a max of 100 words: ";
		cin >> wordFile;

		if (game.initializeFile(wordFile))			//Inputs user's file name into game to be read for words
		{
			cout << "file loaded OK";
			redo = false;
		}
		else
		{
			cout << "file not loaded";
			redo = true;
		}
		cout << endl;
	}while(redo);

	while(game.newWord())						//Grabs a word from inputed file randomly if able
	{
		bool done = false;
		bool won = false;
		char letter;

		while(!done) 						//Letters are guessed until win or lose
		{
			game.displayGame();
			cout << "What letter? ";
			cin >> letter;
			if(!game.guess(letter, done, won))
			{
				cout << "Guess is wrong or already used.\n" << endl;
			}
			if(done && !won)
				game.displayGame();
		}

		game.revealWord();					//Reveals the word at the end of the game

		if(won)
			cout << "\nYou won!";

		cout << endl;
		
		game.displayStatistics();
	}
	return 0;
} 
