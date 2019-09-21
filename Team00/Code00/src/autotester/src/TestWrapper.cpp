#include "TestWrapper.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper()
{
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}

// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper()
{
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
  pkb = PKB();
  parser = Parser(&pkb);
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename)
{
	// call your parser to do the parsing
  // ...rest of your code...
    try
    {
        std::ifstream t(filename);
        std::string contents;

        t.seekg(0, std::ios::end);
        contents.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        contents.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

        parser.Parse(contents);
    }
    catch (char const* &exception)
    {
        std::cout << exception << std::flush;
        exit(0);
    }
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results)
{
// call your evaluator to evaluate the query here
  // ...code to evaluate query...

  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}
