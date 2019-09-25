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

TEST_CASE("Test analyse() method for multiple procedures input 2.")
{
    std::string string_of_proc = "procedure main { a = 1; while (a > v) { if (x > y) then { k = 1; } else { n = 1; } } } procedure main2 { b = 2;} ";
    ProcedureAnalyser procedureAnalyser = ProcedureAnalyser(string_of_proc);
    std::vector<Procedure> list_of_proc = procedureAnalyser.analyse();
    int num_of_proc = list_of_proc.size();

    // Test the procedure is correct or not.
    Procedure procedure1 = list_of_proc[0];
    std::string correct_name1 = "main";
    std::string correct_body1 = " a = 1; while (a > v) { if (x > y) then { k = 1; } else { n = 1; } } ";
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

//TEST_CASE("Test analyse() method for multiple procedures input 3.")
//{
//    std::string string_of_proc = "procedure main { flag = 0; call computeCentroid; call printResults; } procedure readPoint { read x; read y; } procedure printResults { print flag; print cenX; print cenY; print normSq; } procedure computeCentroid { count = 0; cenX = 0; cenY = 0; call readPoint; while ((x != 0) && (y != 0)) { count = count + 1; cenX = cenX + x; cenY = cenY + y; call readPoint; } if (count == 0) then { flag = cenX; } else { cenX = cenX / count; cenY = cenY / count; } normSq = cenX * cenX + cenY * cenY;}";
//    ProcedureAnalyser procedureAnalyser = ProcedureAnalyser(string_of_proc);
//    std::vector<Procedure> list_of_proc = procedureAnalyser.analyse();
//    int num_of_proc = list_of_proc.size();

    // Test the procedure is correct or not.
//    Procedure procedure1 = list_of_proc[0];
//    Procedure procedure2 = list_of_proc[1];
//    Procedure procedure3 = list_of_proc[2];
//    Procedure procedure4 = list_of_proc[3];

//    std::string correct_name1 = "main";
//    std::string correct_body1 = " a = 1; while (a > v) { if (x > y) then { k = 1; } else { n = 1; } } ";
//    std::string name_got1 = procedure1.get_name();
//    std::string body_got1 = procedure1.get_body();
//    std::string body_got2 = procedure2.get_body();
//    std::string body_got3 = procedure3.get_body();
//    std::string body_got4 = procedure4.get_body();
//
//    std::cout << body_got1;
//    std::cout << "\n";
//    std::cout << body_got2;
//    std::cout << "\n";
//
//    std::cout << body_got3;
//    std::cout << "\n";
//
//    std::cout << body_got4;


//
//    Procedure procedure2 = list_of_proc[1];
//    std::string correct_name2 = "main2";
//    std::string correct_body2 = " b = 2;";
//    std::string name_got2 = procedure2.get_name();
//    std::string body_got2 = procedure2.get_body();
//
//    REQUIRE(num_of_proc == 4);
//
//    REQUIRE(correct_name1 == name_got1);
//    REQUIRE(correct_body1 == body_got1);
//
//    REQUIRE(correct_name2 == name_got2);
//    REQUIRE(correct_body2 == body_got2);
//}

//"procedure main { flag = 0; call computeCentroid; call printResults; } procedure readPoint { read x; read y; } procedure printResults { print flag; print cenX; print cenY; print normSq; } procedure computeCentroid { count = 0; cenX = 0; cenY = 0; call readPoint; while ((x != 0) && (y != 0)) { count = count + 1; cenX = cenX + x; cenY = cenY + y; call readPoint; } if (count == 0) then { flag = cenX; } else { cenX = cenX / count; cenY = cenY / count; } normSq = cenX * cenX + cenY * cenY;}"
//procedure whileIfProc {
//        while (x != 0) {
//            if (y == 0) {
//                while (count != 0) {
//                    if (cenX == 0) {
//                        count = 2 * y;
//                    } else {
//                        count = 0;
//                        x = 1;
//                    }
//                }
//            } else {
//                count = 2;
//                y = 3;
//            }
//        }