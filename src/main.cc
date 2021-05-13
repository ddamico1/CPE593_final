#include "run_length_encoding.h"
#include "BWT.h"
#include "move_to_front.h"
#include "huffman.h"

#include <iostream>
#include <fstream>

// Intermediary file names when compressing the file
#define NAME_RLE_BWT(s)         s + ".rle1"
#define NAME_BWT_MTF(s)         s + ".bwt"
#define NAME_MTF_RLE(s)         s + ".mtf"
#define NAME_RLE_HUF(s)         s + ".rle2"
#define NAME_COMPRESSED(s)      s + ".bz2"

// Intermediary file names when decompressing the file
#define NAME_HUF_RLE(s)         s + ".huff"
#define NAME_RLE_MTF(s)         s + ".irle2"
#define NAME_MTF_BWT(s)         s + ".imtf"
#define NAME_BWT_RLE(s)         s + ".ibwt"
#define NAME_DECOMPRESSED(s)    s + "_RECOVERED.txt"


typedef struct {
    std::string in;
    std::string out;
    void(*func)(std::ifstream&,std::ofstream&);
} compression_step;

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cout << "Not enough input arguments (need file to compress)\r\n";
        return -1;
    }

    std::string file(argv[1]);
    std::string filename = file.substr(0, file.find('.'));

    compression_step encode_steps[] = {
        {file, NAME_RLE_BWT(filename), run_length_encode},
        {NAME_RLE_BWT(filename), NAME_BWT_MTF(filename), BWT_encode},
        {NAME_BWT_MTF(filename), NAME_MTF_RLE(filename), mtf_encode},
        {NAME_MTF_RLE(filename), NAME_RLE_HUF(filename), run_length_encode},
    };

    compression_step decode_steps[] = {
        {NAME_HUF_RLE(filename), NAME_RLE_MTF(filename), run_length_decode},
        {NAME_RLE_MTF(filename), NAME_MTF_BWT(filename), mtf_decode},
        {NAME_MTF_BWT(filename), NAME_BWT_RLE(filename), BWT_decode},
        {NAME_BWT_RLE(filename), NAME_DECOMPRESSED(filename), run_length_decode},
    };

    // Perform the encoding transformations
    for(uint8_t i = 0; i < 4; i++) {
        std::ifstream in(encode_steps[i].in);
        std::ofstream out(encode_steps[i].out);

        encode_steps[i].func(in, out);

        in.close();
        out.close();
    }
    
    // Final encoding step - Huffman coding
    std::ifstream final_encode(NAME_RLE_HUF(filename));
    std::ofstream compressed(NAME_COMPRESSED(filename));
    HuffmanTree huffman(final_encode);
    huffman.encode(compressed);
    final_encode.close();
    compressed.close();

    std::cout << "File compressed.\r\n";

    // Start the Huffman decoding
    std::ifstream encoded(NAME_COMPRESSED(filename));
    std::ofstream huffman_decoded(NAME_HUF_RLE(filename));
    huffman.decode(encoded, huffman_decoded);
    encoded.close();
    huffman_decoded.close();

    // Peform the inverse transformations on the Hufffman-decoded data
    for(uint8_t i = 0; i < 4; i++) {
        std::ifstream in(decode_steps[i].in);
        std::ofstream out(decode_steps[i].out);

        decode_steps[i].func(in, out);

        in.close();
        out.close();
    }

    std::cout << "File decompressed.\r\n";


    return 0;
}
