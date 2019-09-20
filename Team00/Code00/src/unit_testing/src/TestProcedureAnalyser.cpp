#include "catch.hpp"
#include "ProcedureAnalyser.h"

TEST_CASE("Test analyse() method for no procedure input.")
{
    std::string no_proc = " ";

    ProcedureAnalyser procedureAnalyser = ProcedureAnalyser(no_proc);
    std::vector<Procedure> list_of_proc = procedureAnalyser.analyse();
    int num_of_proc = list_of_proc.size();
    REQUIRE(num_of_proc == 0);
}

TEST_CASE("Test analyse() method for one procedure input.")
{
    std::string string_of_proc = "procedure main { a = 1; } ";
    ProcedureAnalyser procedureAnalyser = ProcedureAnalyser(string_of_proc);
    std::vector<Procedure> list_of_proc = procedureAnalyser.analyse();
    int num_of_proc = list_of_proc.size();

    // Test the procedure is correct or not.
    Procedure procedure = list_of_proc[0];
    std::string correct_name = "main";
    std::string correct_body = " a = 1; ";
    std::string name_got = procedure.get_name();
    std::string body_got = procedure.get_body();

    REQUIRE(num_of_proc == 1);

    REQUIRE(correct_name == name_got);
    REQUIRE(correct_body == body_got);
}
