#include "Tokenizer.h"
#include "Tokenizer.cc"
#include "Parser.h"
#include "Parser.cc"
#include "Exception.h"
#include "Exception.cc"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    Parser parser;
    string user_input;
    while (true) {
        cout << "\033[34m" ">>>" "\033[0m" " ";
        getline(cin, user_input);

        if (user_input == "$") {
            break;
        }

        TokenStream token_stream = TokenStream(user_input);
        token_stream.tokenize();
        VectorStream v = token_stream.get_tokenized_vector();

        cout << endl;
        cout << "---tokenize---" << endl;
        cout << "size of token list = " << v.size() << endl;
        cout << endl;

        cout << "---parse---" << endl;
        std::pair <bool, Integer> res;
        try {
            res = parser.calculate(v);
            if (res.first == 0) {
                cout << "\033[32m" "The variable has been assigned a value." "\033[0m" << endl;
            } else {
                cout << "\033[32m" "result = " << res.second << "\033[0m" << endl;
            }
            cout << endl;
        } catch (Exception e) {
            ExceptionHandler::log(e);
        } catch (...) {
            cout << "\033[31m" "Syntax error: Unexpected error." "\033[0m" << endl;
        }
        cout << endl;

        
    }
    return 0;
}