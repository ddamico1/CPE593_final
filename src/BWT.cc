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
    cout << "Burrows-Wheeler Transform Complete" << endl;
    return;
};


/*Not sure if decoding from a Bzip2 encoded file is actually possible.
//As mentioned in the original paper by Burrows and Wheeler, the index at which
//the original string appears in the matrix of rotations is needed to decode.
//My thinking is that we have no way of knowing how/where this index is stored by the actual Bzip2 program
// -Dante
// --- "File Format" section of Bzip2 Wikipedia page may shed light on this --- 
*/
void BWT_decode(std::ifstream& encoded_file, std::ofstream& out) {

    if(!encoded_file.good())
        return;

    while(encoded_file.good()){



    }

    return;
};
