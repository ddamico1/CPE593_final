#include "move_to_front.h"


int symbol_table[256];

static void symbol_table_init();
static void move_to_front(int position);

void mtf_encode(std::ifstream& file, std::ofstream& out) {
    int i;

    // Initialize the symbol table
    symbol_table_init();

    while(file.good()) {
        int c = file.get();

        // Look for the current symbol in the symbol table
        for(i = 0; i < sizeof(symbol_table); i++) {
            if(symbol_table[i] == c) {
                // Output the symbol's position in the symbol table and move it to the front
                out << i;
                move_to_front(i);

                break;  // Stop looking when the current symbol is found
            }
        }
    }
}

void mtf_decode(std::ifstream& encoded_file, std::ofstream& out) {
    int i;

    symbol_table_init();

    while(encoded_file.good()) {
        int position = encoded_file.get();

        // Output the symbol at this position
        out << symbol_table[position];

        // Move this symbol to the front
        move_to_front(position);
    }
}

static void symbol_table_init() {
    for(int i = 0; i < sizeof(symbol_table); i++)
        symbol_table[i] = i;
}

static void move_to_front(int position) {
    // Keep track of the symbol at the current position
    int new_front = symbol_table[position];

    // Shift the symbols to the right (only up to the current position)
    memcpy(&symbol_table[1], symbol_table, position);

    // Place the current symbol at the front
    symbol_table[0] = new_front;
}
