#ifndef MOVE_TO_FRONT_H
#define MOVE_TO_FRONT_H

#include <stack>
#include <sstream>
#include <fstream>
#include <iostream>
#include <memory.h>

void mtf_encode(std::ifstream& file, std::ofstream& out);
void mtf_decode(std::ifstream& encoded_file, std::ofstream& out);

#endif
