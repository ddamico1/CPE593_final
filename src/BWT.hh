#ifndef BWT_H
#define BWT_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


void BWT_encode(std::ifstream& file, std::ofstream& out);
void BWT_decode(std::ifstream &encoded_file, std::ofstream &out);


#endif
