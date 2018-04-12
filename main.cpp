#include "huffman.h"

int main(int argc, char** argv) {
    std::string str;
    std::cout << "input text..." << std::endl;
    std::cin >> str;

    HuffmanCode obj;

    std::string encoded_str = obj.encode(str);
    std::cout << "[Huffman Code]" << std::endl << "  " << encoded_str << std::endl;

    std::string decoded_str = obj.decode(encoded_str);
    std::cout << "[Restored Text]" << std::endl << "  " << decoded_str << std::endl;

    obj.dbg_dumpCode();
    obj.dbg_dumpTree();

    return 0;
}
