/*
 *  Created on: September 24, 2017
 *      Author: Emery Weist
 */

//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "array_functions.h"
#include "constants.h"
#include "utilities.h"
//============================================================================

//============================================================================
struct word {
	std::string word;
	int occurrences;
};

word words[constants::MAX_WORDS];

int next = 0;
//============================================================================

void clearArray() {
	next = 0;
}

int getArraySize() {
	return next;
}

std::string getArrayWordAt(int i) {
	return words[i].word;
}

int getArrayWord_NumbOccur_At(int i) {
	return words[i].occurrences;
}

bool processFile(std::fstream &myfstream) {
	if (myfstream.is_open()) {
		std::string line;

		while (std::getline(myfstream, line)) {
			processLine(line);
		}

		return true;
	}

	return false;
}

void processLine(std::string &myString) {
	std::stringstream ss(myString);
	std::string token;

	while (std::getline(ss, token, ' ')) {
		processToken(token);
	}
}

void processToken(std::string &token) {
	strip_unwanted_chars(token);

	if (token == "")
		return;

	for (int i = 0; i < next; i++) {
		std::string to = token;
		std::string wo = words[i].word;
		toUpper(to);
		toUpper(wo);

		if (wo == to) {
			words[i].occurrences++;
			return;
		}
	}

	word w;
	w.word = token;
	w.occurrences = 1;

	words[next] = w;
	next++;
}

bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode) {
	myfile.open(myFileName, mode);

	if (myfile.is_open()) return true;
	return false;
}

void closeFile(std::fstream& myfile) {
	myfile.close();
}

int writeArraytoFile(const std::string &outputfilename) {
	return 0;
}

void sortArray(constants::sortOrder so) {
	bool sorted = false;
	std::ofstream outfile("../output/testdata_full");

	switch (so) {
	case constants::sortOrder::ASCENDING:
		while (!sorted) {
			sorted = true;

			for (int i = 0; i < next - 1; i++) {
				if (toupper(words[i].word[0]) < toupper(words[i + 1].word[0])) {
					word w = words[i + 1];
					words[i + 1] = words[i];
					words[i] = w;
					sorted = false;
				}
			}
		}

		for (int i = 0; i < next; i++) {
			outfile << words[i].word + "\n" << std::endl;
		}
		break;
	case constants::sortOrder::DESCENDING:
		while (!sorted) {
			sorted = true;

			for (int i = 0; i < next - 1; i++) {
				if (toupper(words[i].word[0]) > toupper(words[i + 1].word[0])) {
					word w = words[i + 1];
					words[i + 1] = words[i];
					words[i] = w;
					sorted = false;
				}
			}
		}

		for (int i = 0; i < next; i++) {
			std::cout << words[i].word + "\n";
		}
		break;
	case constants::sortOrder::NUMBER_OCCURRENCES:
		while (!sorted) {
			sorted = true;

			for (int i = 0; i < next - 1; i++) {
				if (words[i].occurrences < words[i + 1].occurrences) {
					word w = words[i + 1];
					words[i + 1] = words[i];
					words[i] = w;
					sorted = false;
				}
			}
		}

		std::cout << "OCCURRENCES";
		for (int i = 0; i < next; i++) {
			std::cout << words[i].word + "\n";
		}
		break;
	default:
		break;
	}

	outfile.close();
}
