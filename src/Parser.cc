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
        o->r_son = parse_factor();
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
        o->r_son = parse_term();
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

void Parser::parse() {
    dfs_destroy(syntax_tree_root);
    this->current_position = 0;
    syntax_tree_root = parse_expression();
}

bool Parser::is_assignment() {
    for (auto e: this->token_stream) {
        if (e.token_type == ASSIGNMENT) {
            return true;
        }
    }
    return false;
}

Integer Parser::dfs_calculate(SyntaxTreeNode *root) {
    if (root == NULL) return Integer(0);
    if (root->token.token_type == NUMBER) {
        return Integer(std::stoll(root->token.token_value));
    }
    if (root->token.token_type == IDENTIFIER) {
        if (
            this->variable_map.find(root->token.token_value) == 
            this->variable_map.end()
        ) {
            throw UndefinedIdentifier();
        } else {
            return Integer(this->variable_map[root->token.token_value]);
        }
    }
    switch (root->token.token_type) {
        case ADD: 
            return dfs_calculate(root->l_son) + dfs_calculate(root->r_son);
            break;
        case SUB:
            return dfs_calculate(root->l_son) - dfs_calculate(root->r_son);
            break;
        case  MUL:
            return dfs_calculate(root->l_son) * dfs_calculate(root->r_son);
            break;
        case  DIV:
            return dfs_calculate(root->l_son) / dfs_calculate(root->r_son);
            break;
        default:
            break;
    }
}

std::pair <bool, Integer> Parser::calculate(VectorStream token_stream_) {
    this->token_stream = token_stream_;
    if (is_assignment()) {
        if (token_stream.size() < 3) {
            throw MissingElement();
        }
        if (token_stream[0].token_type != IDENTIFIER) {
            throw MissingIdentifier();
        }
        if (token_stream[1].token_type != ASSIGNMENT) {
            throw AssignmentMalformed();
        }

        string var_id = token_stream[0].token_value;
        for (size_t i = 2; i < token_stream.size(); ++i) {
            token_stream[i - 2] = token_stream[i];
        }
        token_stream.pop_back();
        token_stream.pop_back(); 
        this->parse();
        Integer res = this->dfs_calculate(syntax_tree_root);
        variable_map[var_id] = res;
        return {0, res};
    } else {
        this->parse();
        Integer res = this->dfs_calculate(syntax_tree_root);
        return {1, res};
    }
}




