#include "../src/huffman.h"



int main(int argc, char** argv) {
    std::string orig_filename(argv[1]);
    std::string filename = orig_filename.substr(0, orig_filename.find('.'));

    std::ifstream in(orig_filename);
    std::ofstream out(filename + ".bz2", std::ios::binary);
    HuffmanTree h(in);
    h.encode(out);

    out.close();

    std::ifstream in2(filename + ".bz2");
    std::ofstream out2(filename + ".huff", std::ios::binary);
    h.decode(in2, out2);

    return 0;
}
