#include "huffman.h"

// std::string型の文字列を渡し、byte_freq配列に出現頻度を記録
void HuffmanCode::counting_strings(std::string str) {
    for (unsigned int i=0; i<str.size(); i++) {
        byte_freq[(unsigned char)str[i]]++;
    }
}

// byte_freq配列を参照し、ハフマン木の葉を作成
void HuffmanCode::make_treeleaf() {
    for (unsigned int i=0; i<256; i++) {
        // 頻度0の葉は作成しない
        if (byte_freq[i] == 0) continue;
        // 葉はleft/right共に256の値をとる(末端の表現)
        HuffmanTree.push_back(HuffmanTreeNode(i, byte_freq[i], 256, 256));
    }
}

// ハフマン木の葉を参照し、節を作成
unsigned int HuffmanCode::make_treenode() {
    std::vector<HuffmanTreeNode>::difference_type root = 0;
    std::vector<HuffmanTreeNode>::size_type size = 0;

    while (size+1 < HuffmanTree.size()) {
        std::vector<HuffmanTreeNode>::iterator s = HuffmanTree.begin() + size;
        HuffmanTreeNode node(256, (s->count + (s+1)->count), size, size+1);
        std::vector<HuffmanTreeNode>::iterator p = std::upper_bound(s+2, HuffmanTree.end(), node);
        root = std::distance(HuffmanTree.begin(), p);
        HuffmanTree.insert(p, node);
        size += 2;
    }

    // 根の位置を返す
    return (unsigned int)root;
}

// ハフマン木を作成
void HuffmanCode::make_huffmantree() {
    make_treeleaf();
    std::sort(HuffmanTree.begin(), HuffmanTree.end());
    root = make_treenode();
}

// ハフマン木からハフマン符号表を作成、連想配列codeに格納
bool HuffmanCode::make_code(unsigned int p, unsigned int c, unsigned int level) {
    if (HuffmanTree[p].right != 256) {
        if (!make_code(HuffmanTree[p].right, (c*2 + 1), level+1)) {
            return false;
        }
    }
    if (HuffmanTree[p].left != 256) {
        if (!make_code(HuffmanTree[p].left, (c*2), level+1)) {
            return false;
        }
    }
    if (HuffmanTree[p].left == 256 && HuffmanTree[p].right == 256) {
        code[HuffmanTree[p].value][1] = c;
        code[HuffmanTree[p].value][0] = level;
    }
    return true;
}

// std::string型の文字列をハフマン符号化
std::string HuffmanCode::encode(std::string str) {
    std::string result;

    counting_strings(str);
    make_huffmantree();

    make_code(root, 0, 0);
    
    for (unsigned int i = 0 ; i < str.size(); i++) {
        result += bin2str(code[(unsigned char)str[i]][1], code[str[i]][0]);
    }

    std::cout << std::endl;

    return result;
}

// ハフマン符号化された文字列を復号
std::string HuffmanCode::decode(std::string str) {
    std::string result;
    unsigned int p = root;

    for (unsigned int i = 0; i < str.size(); i++) {
        if (str[i] == '0') {
            p = HuffmanTree[p].left;
        } else {
            p = HuffmanTree[p].right;
        }
        if (HuffmanTree[p].left == 256 && HuffmanTree[p].right == 256) {
            result += HuffmanTree[p].value;
            p = root;
        }
    }

    return result;
}

// unsigned int型の数値を2進数表記の文字列に変換
std::string HuffmanCode::bin2str(unsigned int num, unsigned int level) {
    std::string result;
    for (unsigned int i = level; i>0; i--) {
        result.push_back('0' + (num & 1));
        num >>= 1;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// 文字列の出現頻度(バイト区切り)を表示
void HuffmanCode::dbg_dumpBfreq() {
    std::cout << "[Input byte frequency]" << std::endl;
    for (unsigned int i=0; i<256; i++) {
        if (byte_freq[i] != 0)
            std::cout << "  " << i << " : " << byte_freq[i] << std::endl;
    }
}

// 作成したハフマン木の情報を表示
void HuffmanCode::dbg_dumpTree() {
    std::cout << "[Huffman Tree nodes]" << std::endl;
    for (unsigned int i = 0; i < HuffmanTree.size(); i++) {
        if (HuffmanTree[i].count == 0) continue;
        std::cout << "  Node[" << i << "] -> " << HuffmanTree[i].value << " : " << HuffmanTree[i].count 
                  << ", left->" << HuffmanTree[i].left << ", right->" << HuffmanTree[i].right
                  << std::endl;
    }
}

// ハフマン符号の対応表を表示
void HuffmanCode::dbg_dumpCode() {
    std::cout << "[Decoded Codes]" << std::endl;
    for (auto i = code.begin(); i != code.end(); ++i) {
        std::cout << "  " << i->first << " : " << bin2str(i->second[1], i->second[0]) << std::endl;
        //std::cout << "  " << i->first << " : " << i->second[1] << std::endl;
    }
}

int HuffmanCode::get_Bfreq(int num) {
    return byte_freq[num];
}
