#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/*
 * CITATIONS
 * Some logic was taken from https://github.com/taochenshh/Burrows-Wheeler-Transform-and-Suffix-Array/blob/master/bwt.cpp
 * for performing the BWT encode on the strings.
 *
 *
 *
 */


void BWT_encode(ifstream& file, ofstream& out) {

    if(!file.good())
        return;

    string result;
    string word;
    vector<string> cyclicTexts;
    int count = 0;

    while(file.good()) {

        //build each string from ifstream and keep track of length
        char currentChar = file.get();
        word += currentChar;
        count++;

        if (file.get() == ' ') {

            //create vector of rotations
            for (int i = 0; i < count; i++) {
                string temp = word.substr(i) + word.substr(0, i);
                cyclicTexts.push_back(temp);
            }

            //sort rotations
            sort(cyclicTexts.begin(), cyclicTexts.end());

            //get last letter of each rotation in sorted vector
            for (string &temp : cyclicTexts) {
                result += *(temp.end() - 1);
            }


            for (char x : result) {
                out.put(x);
            }

            count = 0;
            word = "";


        }
    }
    return;
};

void BWT_decode(std::ifstream& encoded_file, std::ofstream& out) {

    if(!encoded_file.good())
        return;

    while(encoded_file.good()){



    }

    return;
};
