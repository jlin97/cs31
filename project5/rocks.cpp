#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include "utilities.h"
#include <cstring>

using namespace std;

int manageOneRound(const char words[][7], int nWords, int wordnum);
bool isValidAttempt(char attempt[]);
bool isValidWord(const char wordList[][7], int nWords, char probe[]); // function prototypes

int main() {

	const int MAXWORDS = 9000;
	char wordList[MAXWORDS][MAXWORDLEN + 1];
	int noRounds, score, minTries = 0, maxTries = 0;   // declaration of variables
	double total = 0;

	int ACTUALNOOFWORDS = loadWords(wordList, MAXWORDS);  // filling up the entries of the array
	
	if (ACTUALNOOFWORDS < 1) {
		cout << "No words were loaded, so I can't play this game" << endl;
		return -1;
	}

	cout << "How many rounds do you want to play? ";
	cin >> noRounds;

	if (noRounds < 1) {
		cout << "The number of rounds must be positive." << endl;
		return -1;
	}

	cin.ignore(10000, '\n');    // getline problem

	for (int i = 0; i < noRounds; i++) {         // loops for a noRounds number of times
		cout << "\nRound " << i + 1 << endl;

		int nLetters = randInt(0, ACTUALNOOFWORDS - 1);

		cout << "The secret word is " << strlen(wordList[nLetters]) << " letters long." << endl;
		//outputting the length of the secret word

		score = manageOneRound(wordList, ACTUALNOOFWORDS, nLetters);       // goes through a round
		
		if (score == 1) {
			cout << "You got it in " << score << " try." << endl;
		}
		else {
			cout << "You got it in " << score << " tries." << endl;     // outputs the score
		}
		if (i == 0) {
			minTries = score;         // initializing score as min AND max scores for the first round
			maxTries = score;
		}
		total += score;

		if (score < minTries) {   // min score is initialized
			minTries = score;
		}
		if (score > maxTries) {		 // max score is initialized
			maxTries = score;
		}

		cout.setf(ios::fixed);
		cout.precision(2);
		cout << "Average: " << total / (i + 1) << ", minimum: " << minTries << ", maximum: " << maxTries << endl;
		// outputs
	}
	return 0;
}

int manageOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum) {

	if (nWords < 1 || wordnum < 0 || wordnum >= nWords) {
		return -1;      // checking for invalidities
	}
	char probe[100];        // the array for attempt
	char secretWord[100];
	strcpy(secretWord, words[wordnum]);      // copies the entry in the words array into the secretWord c-string

	int noRocks;      // number of rocks
	int noPebbles;    // number of pebbles
	int counter;   // counter for the rock array repeats
	int counter2;      // counter for the pebble array repeats
	int score = 0;     // number of tries

	while (strcmp(probe, secretWord) != 0)       // repeat until attempt matches the actual word
	{
		int rockArray[7] = { -1,-1,-1,-1,-1,-1,-1 };     // initalization of empty c-strings into -1
		int pebbleArray[7] = { -1,-1,-1,-1,-1,-1,-1 };
		noRocks = 0;          // resets the number of rocks and pebbles to 0
		noPebbles = 0;
		counter = 0;
		counter2 = 0;

		cout << "Probe word: ";    // asks for an attempt
		cin.getline(probe, 99);

		if (!(isValidAttempt(probe))) {          // if input is invalid, output error message
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			continue;   // reprompt for a new probe
		}

		bool validWord = isValidWord(words, nWords, probe);     // checks if a word if a word within the wordlist
		if (!(validWord)) {                // if it's not
			cout << "I don't know that word." << endl;        // display output message
			continue;     // reprompt for a new probe
		}

		if (strcmp(probe, secretWord) == 0) {
			score++;                           // if the probe and the secretWord match then increment score and return it
			return score;
		}
		else {
			score++;   // increment number of tries
			// finding the max length between the attempt and the actual secret word
			int maxLength = 0;
			if (strlen(probe) > strlen(secretWord)) {
				maxLength = strlen(secretWord);           // if the length of the attempt is longer than the secret word
			}											  // change the maxLength to the length of the secret wrod
			else {                                      // otherwise change the maxLength to the length of the attempt
				maxLength = strlen(probe);
			}

			// checking for number of rocks
			for (int i = 0; i < maxLength; i++) {
				if (probe[i] == secretWord[i]) {
					rockArray[counter] = i;       // stores the position of the rock found in the repeats int array
					counter++;
					noRocks++;
				}
			}
			for (int j = 0; j < counter; j++) {
				pebbleArray[j] = rockArray[j];    // separate array for pebbles where positions stored will skip a pos of secret word but not the probe word
				counter2++;
			}

			// checking for number of pebbles
			int probePos = 0;
			int secretPos = 0;     // the positions of every new attempt start from 0

			while (probe[probePos] != '\0' && (probePos < MAXWORDLEN)) {			// outer loop for the probe word
				secretPos = 0;
				for (int pos = 0; pos < counter; pos++) {         // checks for the position of the probe
					if (probePos == rockArray[pos]) {			  // if the position is found within the rock array
						probePos++;                               // skip an entry of the probe entirely, skipping every check of the secretword letter
						continue;								  // reprompt for a new probe
					}
				}
				while (secretWord[secretPos] != '\0' && (secretPos < MAXWORDLEN)) {       // inner loop of the secret word
					bool breakOut = false;
					// if at pos there is a rock, the search for a rock will stop
					for (int pos = 0; pos < counter2; pos++) {                  // checks for the position of secretWord
						if (counter2 < 6 && secretPos == pebbleArray[pos]) {    // if it is the same position is found within the pebbleArray
							secretPos++;										// the position of the secretWord will be incremented but 
							breakOut = true;									// only the inner loop will repeat, not the outer
						}
					}

					if (breakOut) {
						continue;			// so that the continue affects the secretWord while loop and not the for loop
					}

					if (counter2 < 6 && probe[probePos] == secretWord[secretPos]) {
						noPebbles++;                   // otherwise, compare the letter of attempt at probePos
						pebbleArray[counter2] = secretPos;      // to letter of the actual word at the secretPos
						counter2++;  // stores the pos of the letter in the counter to skip for future iterations
						break;
					}
					secretPos++;				// increments the position of the secret word
				}
				probePos++;				// increments the position of the probe word		
			}
			cout << "Rocks: " << noRocks << ", Pebbles: " << noPebbles << endl;		// outputs the number of rocks and pebbles
		}
	}
	return -1;		// default return statement should never be reached
}

// checks if a probe word is a valid lower-case word between 4 and 6 letters
bool isValidAttempt(char attempt[]) {
	int count = 0;
	if (strlen(attempt) < MINWORDLEN || strlen(attempt) > MAXWORDLEN) {
		return false;   // returns false if the length is less than 4 or greater than 6
	}
	for (int i = 0; attempt[i] != '\0'; i++) {
		if (isalpha(attempt[i]) && islower(attempt[i])) {   // checks if all letters are lower-case letters
			count++;
		}
	}
	if (count == strlen(attempt)) {   // if all characters are lower-case letters, return true;
		return true;
	}
	return false;
}

// checks if a probe word is a letter within the wordList
bool isValidWord(const char wordList[][7], int noWords, char probe[]) {
	for (int i = 0; i != noWords; i++) {
		if (strcmp(wordList[i], probe) == 0) {  // loops through all entries of the wordList and returns true if any match is found
			return true;
		}
	}
	return false;
}