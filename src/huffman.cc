#include "huffman.h"

/*
 * References:
 *  https://en.wikipedia.org/wiki/Huffman_coding#Basic_technique for the general algorithm
 *  https://www.techiedelight.com/huffman-coding/ for the priority queue idea/implementation
 */


// Goal - encode the output file such that the most frequent symbols have the least bits
void HuffmanTree::encode(std::ofstream& out) {
    // Construct the Huffman Tree
    build_tree();

    // Map the symbols in the file to Huffman coded values
    huffman_encode(root, "", huffman_code);  // Set initial code to empty

#if 0
    // Display the symbol-codeword pairs
    for(std::unordered_map<char,std::string>::const_iterator i = huffman_code.begin(); i != huffman_code.end(); ++i)
        std::cout << i->first << ": " << i->second << "\n";
#endif

    // Go to the beginning of the file (building the tree moves the pointer to EOF)
    file.clear();
    file.seekg(0, std::ios::beg);

    // Write the encoded symbols to the output file
    // Since each symbol now has different bit lengths, we will buffer each bit and write bytes when ready
    uint8_t next_byte = 0;
    uint8_t bit_count = 0;
    int prev_size = 0;
    int symbol;
    while((symbol=file.get()) != -1) {
        const std::string* code = &huffman_code[symbol];

        for(uint8_t i = 0; i < code->size(); i++) {
            uint8_t next_bit = code->at(i) == '1';  // 0 or 1

            // Buffer the current bit and increment the bit count
            next_byte |= next_bit << (7 - bit_count);
            bit_count++;

            // When 8 bits are buffered, write the byte to the file and reset the count
            if(bit_count == 8) {
                out.put(next_byte);
                bit_count = 0;
            }
            
        }

        delta.push_back((int)code->size() - prev_size);
        prev_size = (int)code->size();

        encoded.push_back(*code);  // debugging
    }

    // Write whatever is left in the buffer
    if(bit_count > 0)
        out.put(next_byte);
    
    // TODO: save the mapping so that decoding is possible
}

void HuffmanTree::decode(std::ifstream& encoded_file, std::ofstream& out) {
    uint8_t num_bits = 0;
    uint8_t current_byte, bit_index = 0;

    for(std::vector<std::string>::const_iterator i = encoded.begin(); i != encoded.end(); ++i) {
        for(std::unordered_map<char,std::string>::const_iterator j = huffman_code.begin(); j != huffman_code.end(); ++j) {
            if(j->second == *i)
                out.put(j->first);
        }
    }
}


void HuffmanTree::build_tree() {
    // Keep a histogtram of characters and their frequencies
    std::unordered_map<char, uint32_t> hist;

    // First step: record the frequency of each character in the file
    int symbol;
    while((symbol=file.get()) != -1)
        hist[symbol]++;

    // Second step: create a priority queue that contains the nodes
    // Lambda function is used to determine priorities when inserting nodes
    auto cmp = [](Node* left, Node* right) -> bool { return left->freq > right->freq;};
    static std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> nodes(cmp);

    // Populate the queue with every node set as a (disconnected) leaf node
    for(std::unordered_map<char, uint32_t>::const_iterator i = hist.begin(); i != hist.end(); ++i)
        nodes.push(new Node(i->first, i->second, nullptr, nullptr));

    // Form the tree structure by placing the two lowest-priority nodes as children to an internal node
    // Do this until only the root remains in the queue
    while(nodes.size() > 1) {
        // Remove the two lowest-priority nodes
        Node* left = nodes.top();
        nodes.pop();
        Node* right = nodes.top();
        nodes.pop();

        // Create an internal node with the recently-removed nodes as children
        // and the sum of their frequencies as the frequency
        nodes.push(new Node(0, left->freq + right->freq, left, right));  // O(logn) to insert
    }

    // The remaining node is the root node - the tree has been generated
    root = nodes.top();
}

// Determine each node's coded symbol and add it to the map
void HuffmanTree::huffman_encode(Node* root, std::string code, std::unordered_map<char, std::string>& huffman_code) {
    if(root == nullptr)
        return;  // Nothing to do
    
    // When we reach a leaf node, record its mapping
    // Non-leaf nodes are internal-only and hold no meaning
    if(root->left == nullptr && root->right == nullptr) {
        huffman_code[root->c] = code;
    }

    // Label the left edge "0" and the right edge "1" and repeat for the child nodes
    huffman_encode(root->left, code + "0", huffman_code);
    huffman_encode(root->right, code + "1", huffman_code);
}

int HuffmanTree::huffman_decode(const std::string& code) {
#if 0
    if(root == nullptr)
        return;

    if(root->left == nullptr && root->right == nullptr)
        symbol = root->c;
    else {
        index++;
        huffman_decode(code.at(index) == '1' ? root->right : root->left, index, code, symbol);
    }
#endif
    for(std::unordered_map<char,std::string>::const_iterator i = huffman_code.begin(); i != huffman_code.end(); ++i) {
        if(code == i->second)
            return i->first;
    }
    return -1;
}

