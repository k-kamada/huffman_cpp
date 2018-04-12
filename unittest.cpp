#include "cpptest/cpptest.h"
#include "huffman.h"

class HuffmanCodeTest : public Test::Suite {
public:
    HuffmanCodeTest() {
        TEST_ADD (HuffmanCodeTest::counting_strings_test);
        TEST_ADD (HuffmanCodeTest::encode_test);
        TEST_ADD (HuffmanCodeTest::decode_test);
    }
private:
    // 前処理
    std::string str = "000022233";
    HuffmanCode obj;
    std::string encoded_str = obj.encode(str);
    std::string decoded_str = obj.decode(encoded_str);
    // テスト
    void counting_strings_test() {
        TEST_ASSERT(obj.get_Bfreq(48) == 4);
        TEST_ASSERT(obj.get_Bfreq(50) == 3);
        TEST_ASSERT(obj.get_Bfreq(51) == 2);
    }
    void encode_test() {
        TEST_ASSERT(encoded_str == "00001111111010");
    }
    void decode_test() {
        TEST_ASSERT(decoded_str == str);
    }
};

int main() {
    HuffmanCodeTest tests;
    Test::TextOutput output(Test::TextOutput::Verbose);
    return tests.run(output);
}
