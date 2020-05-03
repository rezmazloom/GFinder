#pragma once
#include <string>
#include <istream>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

class ParsePredicateMatrix
{

#define BUFF_SIZE 10240

public:
	static float** predicate_similarity_matrix;
	static int predicateLength;


	static inline unsigned long long pureSplit(const string& txt, vector<string>& strs, char ch) {
		//this is the general case
		size_t pos = txt.find(ch);
		size_t initialPos = 0;
		strs.clear();
		// Decompose statement
		while (pos != string::npos) {
			strs.push_back(txt.substr(initialPos, pos - initialPos));
			initialPos = pos + 1;
			pos = txt.find(ch, initialPos);
		}
		// Add the last one
		strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));
		//return the size of the vector
		return strs.size();
	}

	static inline void initPredicateSimilarityMatrix(int length) {
		predicate_similarity_matrix = new float* [length];
		for (int i = 0; i < length; ++i)
			predicate_similarity_matrix[i] = new float[length];
	}

	static inline void parsePredicateFile(string predicate_file) {
		char str[BUFF_SIZE];
		string line;
		vector<string> v;
		FILE* fp;
		fp = fopen(predicate_file.c_str(), "r");

		// a new line character makes fgets top reading, so it reads file line by line
		fgets(str, BUFF_SIZE, fp);
		line = string(str);
		pureSplit(line, v, ' ');
		predicateLength = atoi(v[0].c_str());
		//cout << predicateLength;

		initPredicateSimilarityMatrix(predicateLength);
		int row = 0;

		while (fgets(str, BUFF_SIZE, fp) != NULL) {
			line = string(str);
			pureSplit(line, v, ',');
			int col = 0;
			for (std::vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
				predicate_similarity_matrix[row][col] = atof((*it).c_str());
				col++;
			}
			row++;
		}
		fclose(fp);

#ifdef TEST
		for (int __test_i = 0; __test_i < predicateLength; __test_i++) {
			for (int __test_j = 0; __test_j < predicateLength; __test_j++) {
				cout << predicate_similarity_matrix[__test_i][__test_j];
			}
		}
#endif
	}
};

