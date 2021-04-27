#include "run_length_encoding.h"

/*
 * Any sequence of 4-255 consecutive repeated characters is replaced with
 * the first four symbols followed by the total repeat length - 4
 */
void run_length_encode(std::ifstream& file, std::ofstream& out) {
    uint8_t prev_char, current_char, count, i;

    if(!file.good())
        return;

    prev_char = file.get();
    count = 1;
    while(file.good()) {
        // Keep reading characters until a new (non-repeating) character is found
        while((current_char=file.get()) == prev_char) {
            count++;

            // Avoid overflow
            if(count == 255)
                break;
        }

        // Write the compressed data
        if(count >= 4) {
            // Write the repeated character four times followed by the number of subsequent repeats
            for (i = 0; i < 4; i++)
                out << prev_char;
            out.put(count);
        }
        else {
            // If there were fewer than 4 repeating characters, just write them directly
            if(count != 0) {
                for (i = 0; i < count && count != 0; i++)
                    out << prev_char;
            }
        }

        prev_char = current_char;
        count = (count==255) ? 0 : 1;
    }

    std::cout << "File compressed using run-length encoding\n";
}

void run_length_decode(std::ifstream& encoded_file, std::ofstream& out) {

}



