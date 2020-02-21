#ifndef PARSER_H
#define PARSER_H

#include <map>
#include "Tokenizer.h"

/*
    e: expression
    t: term
    f: factor

    e => e + t | e - t | t
    t => t * f | t / f | f
    f => x | (e)
    x => number | id

    e  => t | t e'
    e' => + t e' | - t e' | eps
    t  => f | f t'
    t' => * f t' | / f t' | eps
    f  => x | (e)
    x  => number | id
*/

using std::map;
using Integer = long long;
using VariableMap = map <string, Integer>;

struct SyntaxTreeNode {
    Token token;
    SyntaxTreeNode *l_son;
    SyntaxTreeNode *r_son;

    SyntaxTreeNode();
    SyntaxTreeNode(
        Token token_, 
        SyntaxTreeNode *l_son_, 
        SyntaxTreeNode *r_son_
    );
    ~SyntaxTreeNode();
};

class Parser {
private:
    SyntaxTreeNode *syntax_tree_root;
    VectorStream token_stream;
    VariableMap variable_map;
    int current_position;

    SyntaxTreeNode *parse_expression();
    // SyntaxTreeNode *parse_as_expression();
    SyntaxTreeNode *parse_term();
    // SyntaxTreeNode *parse_md_term();
    SyntaxTreeNode *parse_factor();
    SyntaxTreeNode *parse_number();
    SyntaxTreeNode *parse_identifier();

    bool is_assignment();
    void dfs_destroy(SyntaxTreeNode *root);
    Integer dfs_calculate(SyntaxTreeNode *root);

public:
    Parser();
    Parser(VectorStream token_stream_);
    ~Parser();

    void parse();

    void get_preorder_traversal(
        VectorStream &tar,
        SyntaxTreeNode *root
    );
    void get_preorder_traversal(VectorStream &tar);

    void get_inorder_traversal(
        VectorStream &tar,
        SyntaxTreeNode *root
    );

    void get_inorder_traversal(VectorStream &tar);

    std::pair <bool, Integer> calculate(VectorStream token_stream_);
};

#endif