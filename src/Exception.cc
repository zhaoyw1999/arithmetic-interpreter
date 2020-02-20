#include <iostream>
#include "Exception.h"

using std::cout;
using std::endl;

Exception::Exception(string exception_infomation_ = "") {
    this->exception_infomation = exception_infomation_;
}

Exception::~Exception() {}

string Exception::to_string() {
    return this->exception_infomation;
}

NumberRedundant::NumberRedundant() :
    Exception(
        string("Syntax error: there is more than one integer.")
    ) {}

MissingNumbers::MissingNumbers() :
    Exception(
        string("Syntax error: missing an integer.")
    ) {}

UndefinedIdentifier::UndefinedIdentifier() :
    Exception(
        string("Syntax error: an undeclared identifier was used.")
    ) {}

IdentifierRedundant::IdentifierRedundant() :
    Exception(
        string("Syntax error: there is more than one identifier.")
    ) {}

MissingIdentifier::MissingIdentifier() :
    Exception(
        string("Syntax error: missing an identifier.")
    ) {}

FactorStructureError::FactorStructureError() :
    Exception(
        string(
            "Syntax error:\n"
            "    The internal structure of the factor is wrong.\n"
            "    The factor can only be a number or an expression with parentheses.\n"
            "    That is, [f => x | (e), x => number | identifier]."
        )
    ) {}

BracketMatchError::BracketMatchError() :
    Exception(
        string("Syntax error: bracket mismatch.")
    ) {}

void ExceptionHandler::log(Exception e) {
    cout 
        << "\033[31m"
        << e.to_string()
        << "\033[0m"
        << endl;
}