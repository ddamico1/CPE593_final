#ifndef RUN_LENGTH_ENCODING_H
#define RUN_LENGTH_ENCODING_H

#include <fstream>
#include <iostream>


void run_length_encode(std::ifstream& file, std::ofstream& out);
void run_length_decode(std::ifstream &encoded_file, std::ofstream &out);


#endif
