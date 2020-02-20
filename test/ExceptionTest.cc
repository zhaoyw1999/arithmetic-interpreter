#include <iostream>

#include "../src/Exception.h"
#include "../src/Exception.cc"

void fun() {
    throw NumberRedundant();
    cout << "Test INT" << endl;
}

int main() {
    try {
        throw NumberRedundant();
    } catch (NumberRedundant &e) {
        ExceptionHandler::log(e);
    }

    try {
        throw MissingIdentifier();
    } catch (MissingIdentifier &e) {
        ExceptionHandler::log(e);
    }

    try {
        throw UndefinedIdentifier();
    } catch (UndefinedIdentifier &e) {
        ExceptionHandler::log(e);
    }

    try {
        throw IdentifierRedundant();
    } catch (IdentifierRedundant &e) {
        ExceptionHandler::log(e);
    }

    try {
        throw MissingIdentifier();
    } catch (MissingIdentifier &e) {
        ExceptionHandler::log(e);
    }

    try {
        throw FactorStructureError();
    } catch (FactorStructureError &e) {
        ExceptionHandler::log(e);
    }

    try {
        throw BracketMatchError();
    } catch (BracketMatchError &e) {
        ExceptionHandler::log(e);
    }

    try {
        throw TermStructureError();
    } catch (TermStructureError &e) {
        ExceptionHandler::log(e);
    }

}