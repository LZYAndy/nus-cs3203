#include <iostream>
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

TEST_CASE("Test analyse() method for multiple procedures input.")
{
    std::string string_of_proc = "procedure main { a = 1; } procedure main2 { b = 2;} ";
    ProcedureAnalyser procedureAnalyser = ProcedureAnalyser(string_of_proc);
    std::vector<Procedure> list_of_proc = procedureAnalyser.analyse();
    int num_of_proc = list_of_proc.size();

    // Test the procedure is correct or not.
    Procedure procedure1 = list_of_proc[0];
    std::string correct_name1 = "main";
    std::string correct_body1 = " a = 1; ";
    std::string name_got1 = procedure1.get_name();
    std::string body_got1 = procedure1.get_body();

    Procedure procedure2 = list_of_proc[1];
    std::string correct_name2 = "main2";
    std::string correct_body2 = " b = 2;";
    std::string name_got2 = procedure2.get_name();
    std::string body_got2 = procedure2.get_body();

    REQUIRE(num_of_proc == 2);

    REQUIRE(correct_name1 == name_got1);
    REQUIRE(correct_body1 == body_got1);

    REQUIRE(correct_name2 == name_got2);
    REQUIRE(correct_body2 == body_got2);
}

