#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <bitset>

class HuffmanCode {
    private:
        // バイトデータの出現頻度
        unsigned int byte_freq[256] = {0};
        // ハフマン木の節・葉のデータ型
        struct HuffmanTreeNode {
            unsigned int value;
            unsigned int count;
            unsigned int left;
            unsigned int right;

            HuffmanTreeNode(unsigned int v, unsigned int c, unsigned int l, unsigned int r)
                : value(v), count(c), left(l), right(r) {}

            bool operator < (const HuffmanTreeNode& dest) const 
            { return (count < dest.count); }
            
        };
        std::vector<HuffmanTreeNode> HuffmanTree;
        // 元の文字とハフマン符号を収めた連想配列（int[0]:符号、int[1]:符号深さ）
        std::map<unsigned char, unsigned int[2]> code;
        unsigned int root;
        void make_treeleaf();
        unsigned int make_treenode();
        void counting_strings(std::string str);
        void make_huffmantree();
        bool make_code(unsigned int p, unsigned int c, unsigned int level);
        std::string bin2str(unsigned int num, unsigned int level);
    public:
        void dbg_dumpBfreq();
        void dbg_dumpTree();
        void dbg_dumpCode();
        int get_Bfreq(int num);
        std::string encode(std::string str);
        std::string decode(std::string str);
};

