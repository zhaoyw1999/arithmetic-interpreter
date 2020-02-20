#include "../src/Tokenizer.h"
#include "../src/Tokenizer.cc"

#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main() {
    string s;

    while (true) {
        cout << ">>> ";
        getline(cin, s);
        if (s == "$") {
            break;
        }
        TokenStream ts = TokenStream(s);
        ts.tokenize();
        auto v = ts.get_tokenized_vector();
        cout << "TokenList.size = " << v.size() << endl;
        for (Token e: v) {
            cout << e.to_string() << endl;
        }
        cout << endl;
    }

    return 0;
}