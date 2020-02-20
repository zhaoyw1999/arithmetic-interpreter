#include "../src/Parser.h"
#include "../src/Parser.cc"
#include "../src/Exception.h"
#include "../src/Exception.cc"
#include "../src/Tokenizer.h"
#include "../src/Tokenizer.cc"

#include <algorithm>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::reverse;

int main() {
    string s;

    while (true) {
        cout << ">>> ";
        getline(cin, s);
        if (s == "$") {
            break;
        }

        cout << "Tokenize..." << endl;
        TokenStream ts = TokenStream(s);
        ts.tokenize();
        auto v = ts.get_tokenized_vector();
        reverse(v.begin(), v.end());
        cout << "total token = " << v.size() << endl;
        for (Token e: v) {
            cout << e.to_string() << endl;
        }
        cout << endl;

        cout << "Parse..." << endl;
        Parser psr;
        VectorStream res;
        try {
            psr.parse(v);
        } catch (Exception &e) {
            ExceptionHandler::log(e);
        } catch (...) {
            // to do
        }
        cout << endl;

        cout << "Syntax Tree (Preorder)..." << endl;
        psr.get_preorder_traversal(res);
        for (Token e: res) {
            cout << e.to_string() << endl;
        }

        res.clear();
        cout << "Syntax Tree (Inorder)..." << endl;
        psr.get_inorder_traversal(res);
        for (Token e: res) {
            cout << e.to_string() << endl;
        }

        cout << endl << "DONE..." << endl << endl;
    }

    return 0;
}