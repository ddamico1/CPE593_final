#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>


class HuffmanTree {
private:
    struct Node {
        char c;
        uint32_t freq;
        Node* left;
        Node* right;
        Node(char symbol, uint32_t freq, Node* left, Node* right): c(symbol), freq(freq), left(left), right(right) {}
    };

    Node* root;
    std::ifstream& file;
    std::unordered_map<char, std::string> huffman_code;
    std::vector<uint8_t> delta;
    std::vector<std::string> encoded;

    // Internal function to build the Huffman Tree
    void build_tree();

    // Internal functions to encode/decode the input
    void huffman_encode(Node* root, std::string code, std::unordered_map<char, std::string>& huffman_codes);
    int huffman_decode(const std::string& code);

public:
    HuffmanTree(std::ifstream& file) : file(file) {}
    void encode(std::ofstream& out);
    void decode(std::ifstream& encoded_file, std::ofstream& out);
};


#endif
