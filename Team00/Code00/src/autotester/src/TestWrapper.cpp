#include "TestWrapper.h"

// implementation code of WrapperFactory - do NOT modify the next 8 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper()
{
    if (wrapper == 0)
    {
        wrapper = new TestWrapper;
    }
    return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper()
{
    // create any objects here as instance variables of this class
    // as well as any initialization required for your spa program
    parser = Parser(&pkb);
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string file_name)
{
    // call your parser to do the parsing
    // ...rest of your code...
    try
    {
        std::ifstream t(file_name);
        std::string contents;

        t.seekg(0, std::ios::end);
        int end_position = t.tellg();
        if (end_position == -1)
        {
            throw std::runtime_error(error_messages::invalid_file);
        }
        contents.reserve(end_position);
        t.seekg(0, std::ios::beg);

        contents.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

        parser.parse(contents);
    }
    catch (const std::runtime_error error)
    {
        std::cout << error.what() << std::flush;
        exit(0);
    }
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string> &results)
{
    // call your evaluator to evaluate the query here
    // ...code to evaluate query...
    std::unordered_set<std::string> answers = QueryEvaluator::get_result(query, pkb);
    for (std::string answer: answers)
    {
        results.push_back(answer);
    }
    // store the answers to the query in the results list (it is initially empty)
    // each result must be a string.
}
