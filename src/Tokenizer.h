#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <queue>

using std::deque;
using std::vector;
using std::string;

enum TokenType {
    IDENTIFIER,
    NUMBER,
    L_BRACKET,
    R_BRACKET,
    ASSIGNMENT,
    ADD,
    SUB,
    MUL,
    DIV,
    END_FLAG
};

using TokenValue = std::string;

struct Token {
    TokenType token_type;
    TokenValue token_value;

    Token();
    Token(TokenType token_type_, TokenValue token_value_);
    ~Token();

    string to_string();
};

using VectorStream = vector <Token>;
using DequeStream = deque <Token>;

class TokenStream {
private:
    string origin_stream;
    VectorStream stream_vector;
    DequeStream stream_deque;

    void append_token(Token to_add);
    bool is_alpha_underline(char c);
    bool is_alpha(char c);
    bool is_digit(char c);
    bool is_alpha_underline_digit(char c);

public:
    TokenStream();
    TokenStream(string origin_stream_);
    ~TokenStream();

    void set_origin_stream(string origin_stream_);
    void tokenize();
    VectorStream get_tokenized_vector();
    DequeStream get_tokenized_deque();
};

#endif