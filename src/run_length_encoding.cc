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
            out.put(count - 4);
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
    if(!encoded_file.good())
        return;

    int prev_char = encoded_file.get();
    uint8_t run_length = 0;

    while(encoded_file.good()) {
        int current_char = encoded_file.get();

        if(current_char == prev_char)
            run_length++;
        
        if(run_length == 3) {
            run_length = (uint8_t) encoded_file.get();
            
            for(uint8_t i = 0; i < run_length; i++)
                out.put(prev_char);

            run_length = 0;
            
        }

        out.put(prev_char);
        prev_char = current_char;
    }

    std::cout << "File decompressed using run-length decoding\n";
}



