#include <string>
#include <iostream>
#include "Tokenizer.h"

using std::string;
using std::clog;
using std::endl;

Token::Token() {}

Token::Token(TokenType token_type_, TokenValue token_value_) {
    this->token_type = token_type_;
    this->token_value = token_value_;
}

Token::~Token() {}

string Token::to_string() {
    return 
        string("Token[")
            .append(std::to_string(this->token_type))
            .append(", ")
            .append(this->token_value)
            .append("]");
}

TokenStream::TokenStream() {}

TokenStream::TokenStream(string origin_stream_) {
    this->origin_stream = origin_stream_;
}

TokenStream::~TokenStream() {}

void TokenStream::set_origin_stream(string origin_stream_) {
    this->origin_stream = origin_stream_;
}

VectorStream TokenStream::get_tokenized_vector() {
    return this->stream_vector;
}

DequeStream TokenStream::get_tokenized_deque() {
    return this->stream_deque;
}

void TokenStream::append_token(Token to_add) {
    this->stream_vector.push_back(to_add);
    this->stream_deque.push_back(to_add);
}

bool TokenStream::is_alpha_underline(char c) {
    return this->is_alpha(c) || c == '_';
}

bool TokenStream::is_alpha(char c) {
    return isalpha(c);
}

bool TokenStream::is_digit(char c) {
    return isdigit(c);
}

bool TokenStream::is_alpha_underline_digit(char c) {
    return is_alpha_underline(c) || is_digit(c);
}

void TokenStream::tokenize() {
    auto &s = this->origin_stream;
    s.push_back('$');

    size_t p = 0;

    while (p < s.size() && s[p] != '$') {
        if (s[p] == '(') {
            this->append_token(
                Token(L_BRACKET, "(")
            );
        } else if (s[p] == ')') {
            this->append_token(
                Token(R_BRACKET, ")")
            );
        } else if (s[p] == '=') {
            this->append_token(
                Token(ASSIGNMENT, "=")
            );
        } else if (s[p] == '+') {
            this->append_token(
                Token(ADD, "+")
            );
        } else if (s[p] == '-') {
            this->append_token(
                Token(SUB, "-")
            );
        } else if (s[p] == '*') {
            this->append_token(
                Token(MUL, "*")
            );
        } else if (s[p] == '/') {
            this->append_token(
                Token(DIV, "/")
            );
        } else if (this->is_alpha_underline(s[p])) {
            string identifier = "";
            while (p < s.size() && s[p] != '$' && is_alpha_underline_digit(s[p])) {
                identifier.push_back(s[p++]);
            }
            --p;
            this->append_token(
                Token(IDENTIFIER, identifier)
            );
        } else if (this->is_digit(s[p])) {
            string number = "";
            while (p < s.size() && s[p] != '$' && is_digit(s[p])) {
                number.push_back(s[p++]);
            }
            --p;
            this->append_token(
                Token(NUMBER, number)
            );
        }
        ++p;
    }
}