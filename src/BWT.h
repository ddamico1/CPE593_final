#ifndef BWT_H
#define BWT_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void BWT_encode(ifstream& file, ofstream& out);
void BWT_decode(ifstream &encoded_file,ofstream &out);


#endif
