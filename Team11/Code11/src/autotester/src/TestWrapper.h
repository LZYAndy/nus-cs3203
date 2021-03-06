#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <list>

// include your other headers here
#include "AbstractWrapper.h"
#include "Parser.h"
#include "PKB.h"
#include "QueryEvaluator.h"
#include "ErrorMessages.h"

class TestWrapper : public AbstractWrapper
{
public:
    // default constructor
    TestWrapper();

    // destructor
    ~TestWrapper();

    // method for parsing the SIMPLE source
    virtual void parse(std::string file_name);

    // method for evaluating a query
    virtual void evaluate(std::string query, std::list<std::string> &results);

private:
    PKB pkb;
    Parser parser;
};

#endif
