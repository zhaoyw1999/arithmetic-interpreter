#include "Parser.h"
#include "Exception.h"

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

SyntaxTreeNode::~SyntaxTreeNode() {
    if (this->l_son != NULL) {
        delete this->l_son;
    }
    if (this->r_son != NULL) {
        delete this->r_son;
    }
}

Parser::Parser() {}

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
    if (current_position == this->token_stream.size()) {
        return NULL;
    }
    Token current_token = this->token_stream.at(current_position);
    if (current_token.token_type == NUMBER) {
        return parse_number();
    } else if (current_token.token_type == IDENTIFIER) {
        return parse_identifier();
    } else if (current_token.token_type == L_BRACKET) {
        SyntaxTreeNode *o = parse_expression();
        ++this->current_position;
        return o;
    } else {
        throw FactorStructureError();
    }
}

SyntaxTreeNode *Parser::parse_term() {
    if (current_position == this->token_stream.size()) {
        return NULL;
    }
    SyntaxTreeNode *factor = parse_factor();
    if (current_position == this->token_stream.size()) {
        return factor;
    } else {
        
    }

}






