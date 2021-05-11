/*
 * CITATIONS
 * Some logic was taken from https://github.com/taochenshh/Burrows-Wheeler-Transform-and-Suffix-Array/blob/master/bwt.cpp
 * for performing the BWT encode on the strings.
 *
 * https://www.geeksforgeeks.org/how-to-find-index-of-a-given-element-in-a-vector-in-cpp/ for implementation of how to find
 * the original string in the vector of rotated and shuffled strings
 *
 */
#include "BWT.h"

int origPtr;

void BWT_encode(ifstream& file, ofstream& out) {

    if(!file.good())
        return;

    string result;
    string text;
    vector<string> cyclicTexts;
    int count = 0;

    while(file.good()) {
        //build string from ifstream and keep track of length
        char currentChar = file.get();

        if((int)currentChar == -1)
            break;

        text += currentChar;
        count++;
    }

    cout << "Text: " << text << '\n';

    //create vector of rotations
    for (int i = 0; i < count; i++) {
        string temp = text.substr(i) + text.substr(0, i);
        cyclicTexts.push_back(temp);
    }

    cout << "Rotations: \n";
    for(auto s: cyclicTexts) {
        cout << s << '\n';
    }
    cout << '\n';

    //sort rotations
    sort(cyclicTexts.begin(), cyclicTexts.end());

    cout << "Sorted rotations: \n";
    for(auto s: cyclicTexts) {
        cout << s << '\n';
    }
    cout << '\n';
    

    //track origin pointer index
    auto it = find(cyclicTexts.begin(), cyclicTexts.end(), text);
    if (it != cyclicTexts.end()) {
        origPtr = it - cyclicTexts.begin();
    }

    //get last letter of each rotation in sorted vector
    for (string &temp : cyclicTexts) {
        result += *(temp.end() - 1);
    }

    for (char x : result) {
        out.put(x);
    }


    cout << "Burrows-Wheeler Transform Complete" << endl;
    cout << "'Origin Pointer' : " << origPtr << endl;
    return;
};


//How to pass the origin pointer to the decoder?
void BWT_decode(ifstream& encoded_file, ofstream& out) {
    cout << "Decoding\n";

    if(!encoded_file.good())
        return;

    string result;
    string text;
    vector<string> cyclicTexts;
    int count = 0;


    while(encoded_file.good()){
        //build string from fstream
        char currentChar = encoded_file.get();

        if((int)currentChar == -1)
            break;

        text += currentChar;
        count++;
    }

    cout << "Text: " << text << '\n';

    //create vector of rotations
    for (int i = 0; i < count; i++) {
        string temp = text.substr(i) + text.substr(0, i);
        cyclicTexts.push_back(temp);
    }

    cout << "rotations: \n";
    for(auto s: cyclicTexts) {
        cout << s << '\n';
    }
    cout << '\n';

    //sort rotations
    sort(cyclicTexts.begin(), cyclicTexts.end());

    cout << "Sorted rotations: \n";
    for(auto s: cyclicTexts) {
        cout << s << '\n';
    }
    cout << '\n';

    //output each character from original string
    for (char x :cyclicTexts[4]) {  // Hardcoded origin pointer 4 for testing
        out.put(x);
    }

    return;
};

/*Not sure if decoding from a Bzip2 encoded file is actually possible.
//As mentioned in the original paper by Burrows and Wheeler, the index at which
//the original string appears in the matrix of rotations is needed to decode.
//My thinking is that we have no way of knowing how/where this index is stored by the actual Bzip2 program
// -Dante
// --- "File Format" section of Bzip2 Wikipedia page may shed light on this --- 
*/
