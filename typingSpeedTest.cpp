/*
Simple Typing Speed Test -- Alan Zhong

This program tests how fast your typing speed is using an average of 5 tests, each of which
generates a random sequence of words and times how long you take to type them. The program then 
outputs several statistics such as accuracy, wpm, and consistency among tests.

*/

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

using namespace std;

#define nl endl
#define pub push_back
#define pob pop_bac

int main() {
	// keeps track of the details of each test, in order to generate results at the end
	vector<vector<double> > testDetails; // wpm, accuracy

	// reads in all of the possible words that can be used in the typing speed test (top 200 most common words)
	ifstream dict ("dict.txt");
	vector<string> allWords;

	for (int i = 0; i < 200; ++i) {
		string word;
		dict >> word;
		allWords.pub(word);
	}
    srand(time(0)); // setting the seed to the current time so that we can generate random words later

    // performs each test and outputs the wpms
	for (int i = 0; i < 5; ++i) {
		int wordCount = rand() % 15 + 25; // random number of words between [25, 50)
		string sentence; // the sentence that we'll print
		vector<string> words; // the words that the user needs to type
		for (int j = 0; j < wordCount; j++) {
            string word = allWords[rand() % 200]; // we retrieve a random word from the vector of words
			words.pub(word);
			sentence += word + " ";
		}
        int totalLetters = sentence.length(); // total number of letters, used to calculate WPM

		// preparing the user
		cout << "Get Ready: " << nl;
		sleep(2);
		cout << "3" << nl;
		sleep(1);
		cout << "2" << nl;
		sleep(1);
		cout << "1" << nl;
		sleep(1);
		// timing how fast it takes the user to type the sentence, and stores the sentence
		time_t start;
		time_t end;
		string input; // the user's input
		cout << sentence << nl; // printing the sentence 
		time(&start);
		getline(cin, input); // reading the user's input
		time(&end);
		double minutesUsed = (double)(end - start)/60; // timing how long it took for the user to type

		// separates input into words
		vector<string> wordsTyped; // vector to store each word
		string currentWord;
		for (int i = 0; i < input.length(); ++i) {
			if (input[i] == ' ') { // separating words by spaces
				wordsTyped.pub(currentWord);
				currentWord = "";
			} else {
				currentWord += string(1, input[i]);
			}
		}

        // determines how many correct words there are
		int correctWords;
		int incorrectWords;
		for (int i = 0; i < words.size(); ++i) {
			if (words[i] == wordsTyped[i]) { // checks each pair of words
				correctWords++;
			} else {
				incorrectWords++;
			}
		}
		incorrectWords--; // new line at the end of input is counted as an error
		
		double wpm = ((totalLetters)/5 - incorrectWords)/minutesUsed; // calculates wpm
        double accuracy = (double)correctWords / (correctWords + incorrectWords);
        cout << "WPM: " << wpm << nl; // prints wpm
        cout << "Accuracy: " << 100*accuracy << "%" << nl;
		vector<double> currentTestDetails = {wpm, accuracy}; // keeps track of this test's wpm and accuracy
		testDetails.pub(currentTestDetails);
		sleep(2);
    }
	// now we output some details about the user's performance
	double averageWPM;
	double averageAccuracy;
	// we find the sums of the wpms and accuracy, then we divide each by 5 to find the average
	for (vector<double> i : testDetails) {
		averageWPM += i[0];
		averageAccuracy += i[1];
	}
	averageWPM /= 5;
	averageAccuracy /= 5;

	// telling the user what their statistics were
	cout << nl << "Your average wpm was " << averageWPM << " and your average accuracy was " << 100*averageAccuracy << "%" << nl << nl;
	// telling the user how consistent their results were
	double wpmRange;
	double accuracyRange;
	double minWPM;
	double maxWPM;
	double minAccuracy;
	double maxAccuracy;
	// finding min and max accuracy and wpm; this is to find how consistent their accuracy and wpm were
	for (vector<double> i : testDetails) {
		minAccuracy = min(minAccuracy, i[1]);
		maxAccuracy = max(maxAccuracy, i[1]);
		minWPM = min(minWPM, i[0]);
		maxWPM = max(maxWPM, i[0]);
	}
	// ranges of wpm and accuracy
	wpmRange = maxWPM - minWPM;
	accuracyRange = maxAccuracy - minAccuracy;	

	// telling the user how consistent they were
	if (wpmRange < 5) {
		cout << "You were extremely consistent in your typing speed and  "; // don't nl so that we can just add on when we print the accuracy consistency
	} else if (wpmRange < 10) {
        cout << "You were consistent in your typing speed and  ";
    } else if (wpmRange < 20) {
        cout << "You weren't very consistent in your typing speed and  ";
    } else {
		cout << "You were not consistent in your typing speed and ";
	}
    if (accuracyRange < 0.05) {
        cout << "you were extremely consistent in your accuracy. " << nl;
    } else if (accuracyRange < 0.1) {
        cout << "you were consistent in your accuracy. " << nl;
    } else if (accuracyRange < 0.2) {
        cout << "you weren't very consistent in your accuracy. " << nl;
    } else {
        cout << "you were not consistent in your accuracy. " << nl;
    }
	sleep(1);
	cout << "Thanks for playing! " << nl;
}
