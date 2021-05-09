#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <bitset>


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

    // Internal function to build the Huffman Tree
    void build_tree();

    // Internal functions to encode/decode the input
    void huffman_encode(Node* root, std::string code, std::unordered_map<char, std::string>& huffman_codes);
    void huffman_decode();

public:
    HuffmanTree(std::ifstream& file) : file(file) {}
    void encode(std::ofstream& out);
    void decode(std::ofstream& out);
};


#endif
