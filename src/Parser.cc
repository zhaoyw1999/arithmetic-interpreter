#include "Parser.h"
#include "Exception.h"
#include <iostream>

using std::cout;
using std::endl;

SyntaxTreeNode::SyntaxTreeNode() {}

SyntaxTreeNode::SyntaxTreeNode(
    Token token_, 
    SyntaxTreeNode *l_son_ = NULL, 
    SyntaxTreeNode *r_son_ = NULL
) {
    this->token = token_;
    this->l_son = l_son_;
    this->r_son = r_son_;
}

SyntaxTreeNode::~SyntaxTreeNode() {}

Parser::Parser() {
    this->syntax_tree_root = NULL;
}

Parser::Parser(VectorStream token_stream_) {
    this->token_stream = token_stream_;
}

Parser::~Parser() {
    dfs_destroy(this->syntax_tree_root);
}

void Parser::dfs_destroy(SyntaxTreeNode *root) {
    if (root == NULL) return;
    if (root->l_son != NULL) dfs_destroy(root->l_son);
    if (root->r_son != NULL) dfs_destroy(root->r_son);
    delete root;
}

SyntaxTreeNode *Parser::parse_number() {
    cout << current_position << " parse_number" << endl; 
    if (current_position == this->token_stream.size()) {
        return NULL;
    }
    Token current_token = this->token_stream.at(current_position);
    if (current_token.token_type == NUMBER) {
        SyntaxTreeNode *o = new SyntaxTreeNode(current_token);
        ++this->current_position;
        return o;
    } else {
        throw MissingNumbers();
    }
}

SyntaxTreeNode *Parser::parse_identifier() {
    cout << current_position << " parse_identifer" << endl; 
    if (current_position == this->token_stream.size()) {
        return NULL;
    }
    Token current_token = this->token_stream.at(current_position);
    if (current_token.token_type == IDENTIFIER) {
        SyntaxTreeNode *o = new SyntaxTreeNode(current_token);
        ++this->current_position;
        return o;
    } else {
        throw MissingIdentifier();
    }
}

SyntaxTreeNode *Parser::parse_factor() {
    cout << current_position << " parse_factor" << endl; 
    if (current_position == this->token_stream.size()) {
        return NULL;
    }
    Token current_token = this->token_stream.at(current_position);
    if (current_token.token_type == NUMBER) {
        return parse_number();
    } else if (current_token.token_type == IDENTIFIER) {
        return parse_identifier();
    } else if (current_token.token_type == L_BRACKET) {
        ++this->current_position;
        SyntaxTreeNode *o = parse_expression();
        ++this->current_position;
        return o;
    } else {
        throw FactorStructureError();
    }
}

SyntaxTreeNode *Parser::parse_term() {
    cout << current_position << " parse_term" << endl; 
    if (current_position == this->token_stream.size()) {
        return NULL;
    }
    SyntaxTreeNode *factor = parse_factor();
    if (
        current_position == this->token_stream.size() ||
        (
            this->token_stream[current_position].token_type != MUL && 
            this->token_stream[current_position].token_type != DIV
        )
    ) {
        return factor;
    } 
    Token current_token = this->token_stream.at(current_position);
    TokenType token_type = current_token.token_type;
    SyntaxTreeNode *o = NULL;
    while (token_type == MUL || token_type == DIV) {
        o = new SyntaxTreeNode(current_token);
        o->l_son = factor;
        ++this->current_position;
        o->r_son = parse_term();
        factor = o;
        if (this->current_position == this->token_stream.size()) break;
        current_token = this->token_stream.at(current_position);
        token_type = current_token.token_type;
    }
    return o;
}

SyntaxTreeNode *Parser::parse_expression() {
    cout << current_position << " parse_expression" << endl; 
    if (current_position == this->token_stream.size()) {
        return NULL;
    }
    SyntaxTreeNode *term = parse_term();
    if (current_position == this->token_stream.size()) {
        return term;
    } 
    Token current_token = this->token_stream.at(current_position);
    TokenType token_type = current_token.token_type;
    SyntaxTreeNode *o = NULL;
    if (token_type == R_BRACKET) {
        return term;
    }
    while (token_type == ADD || token_type == SUB) {
        o = new SyntaxTreeNode(current_token);
        o->l_son = term;
        ++this->current_position;
        o->r_son = parse_expression();
        term = o;
        if (this->current_position == this->token_stream.size()) break;
        current_token = this->token_stream.at(current_position);
        token_type = current_token.token_type;
    }
    return o;
}

void Parser::get_preorder_traversal(
    VectorStream &tar, 
    SyntaxTreeNode *root
) {
    if (root == NULL) return;
    tar.push_back(root->token);
    if (root->l_son != NULL) get_preorder_traversal(tar, root->l_son);
    if (root->r_son != NULL) get_preorder_traversal(tar, root->r_son);
}

void Parser::get_preorder_traversal(VectorStream &tar) {
    get_preorder_traversal(tar, this->syntax_tree_root);
}

void Parser::get_inorder_traversal(
    VectorStream &tar,
    SyntaxTreeNode *root
) {
    if (root == NULL) return;
    if (root->l_son != NULL) get_preorder_traversal(tar, root->l_son);
    tar.push_back(root->token);
    if (root->r_son != NULL) get_preorder_traversal(tar, root->r_son);
}

void Parser::get_inorder_traversal(VectorStream &tar) {
    get_inorder_traversal(tar, this->syntax_tree_root);
}

void Parser::parse(VectorStream to_parse) {
    dfs_destroy(syntax_tree_root);
    this->token_stream = to_parse;
    this->current_position = 0;
    syntax_tree_root = parse_expression();
}






