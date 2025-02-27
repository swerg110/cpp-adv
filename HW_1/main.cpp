#include "string"
#include "iostream"
bool is_the_word(const std::string& str) {
    return std::all_of(std::begin(str), std::end(str),
                       [](unsigned char c){ return std::isalpha(c);}
    );
}

int main() {
    std::string str{"bamboleio, bamboleia!"};
    std::remove(str.begin(), str.end(), 'b');
    std::cout << str << std::endl;
}