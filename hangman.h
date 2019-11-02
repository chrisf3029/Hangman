//Christopher Fong
//hangman.h
//Purpose: Header file containing constant variables, initalizers, and public and private methods and variables
#include <string>

const int MAX_SIZE = 100;						//Maximum amount of words that can be used for an answer.

const int MAX_WRONG = 7;

const int LINES = 16;							//Amount of lines printed out for the hangman image.

const int ALPHABET_SIZE = 26;

const char  ALPHABET[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
									//The alphabet which is used to check if the input was a valid letter.

class Hangman
{
	public:
		bool initializeFile(std::string filename);		//Opens a document and reads up to line MAX_SIZE and uses those words for play.

		void displayStatistics();				//Displays wins, loses, amount of words played, and amount of words left to be played.

		bool newWord();						//Grabs a new word to be played that has not been played before.

		void displayGame();					//Displays the used letters, the progress of completing the word, and the picture of the hangman.

		bool guess(char ltr, bool& done, bool& won);		//Checks the guessed letter and returns if the word has been guessed and if the game was won.

		void revealWord();					//Reveals the correct word to the user.

		int wordsLeft;						//The amount of words left to be played.

	private:
		std::string word;					//Holds the current word that is being played

		std::string wordList[MAX_SIZE];				//Holds all the words that can be played.

		std::string body[LINES];				//Holds all the drawn parts of hangman (the body parts, the hanging device).

		char used[ALPHABET_SIZE];				//Holds the characters that have already been played.

		char currentWord;

		bool excludeIndex[MAX_SIZE];				//Holds all the indexes of words that have been played.

		bool letterFound[MAX_SIZE];				//Holds wether a letter at a given position was guessed.

		int size;						//The size or amount of words that can be played.

		int gameNum;						//The the number of games that have been played so far.

		int numUsed;						//The amount of letters that have been already played.

		int lettersLeft;					//The amount of letters left to be guessed.

		int wins;

		int loses;

		int wrong;	
};
