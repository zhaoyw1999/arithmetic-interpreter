#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

using std::string;
using std::exception;

class Exception : public exception {
protected:
    string exception_infomation;
public:
    Exception(string exception_infomation_);
    virtual ~Exception();
    string to_string();
};

class NumberRedundant : public Exception {
public:
    NumberRedundant();
};

class MissingNumbers : public Exception {
public:
    MissingNumbers();
};

class UndefinedIdentifier : public Exception {
public:
    UndefinedIdentifier();
};

class IdentifierRedundant : public Exception {
public:
    IdentifierRedundant();
};

class MissingIdentifier : public Exception {
public:
    MissingIdentifier();
};

class FactorStructureError : public Exception {
public:
    FactorStructureError();
};

class BracketMatchError : public Exception {
public:
    BracketMatchError();
};

class TermStructureError : public Exception {
public:
    TermStructureError();
};

class MissingElement : public Exception {
public:
    MissingElement();
};

class AssignmentMalformed : public Exception {
public:
    AssignmentMalformed();
};

class ExceptionHandler {
public:
    static void log(Exception e);
};

#endif