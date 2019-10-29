# This file should be placed in the Code11 directory.
import os

test_queries_mapping = [("follows_parent", "follows"),
                        ("follows_parent", "followsT"),
                        ("follows_parent", "parent"),
                        ("follows_parent", "parentT"),
                        ("valid_calls", "calls"),
                        ("valid_calls", "callsT"),
                        ("invalid_calls_direct", "invalid_calls_direct"),
                        ("invalid_calls_cyclic", "invalid_calls_cyclic"),
                        ("invalid_calls_missing_procedure", "invalid_calls_missing_procedure"),
                        ("modifies_uses", "modifies"),
                        ("modifies_uses", "uses"),
                        ("next_affects", "next"),
                        ("next_affects", "nextT"),
                        ("next_affects", "affects"),
                        ("next_affects", "affectsT"),
                        ("pattern", "pattern"),
                        ("with", "with")]

autotest_directory = "./cmake-build-debug/src/autotester/"
design_abstraction_program_directory = "./tests/design_abstraction_test/programs/"
design_abstraction_queries_directory = "./tests/design_abstraction_test/queries/"
result_directory = "./tests/output/"

def checks():
    if not os.path.exists(("{}autotester".format(autotest_directory))):
            print("Autotester does not exist.")
            exit(1)
    if not os.path.isdir(("{}".format(result_directory))):
        print("Result directory does not exist.")
        exit(1)
    for i in test_queries_mapping:
        prog_file = i[0]
        query_file = i[1]
        if not os.path.exists("{}{}.txt".format(design_abstraction_program_directory, prog_file)):
            print("{}.txt does not exist.".format(prog_file))
            exit(1)
        if not os.path.exists("{}{}.txt".format(design_abstraction_queries_directory, query_file)):
            print("{}.txt does not exist.".format(query_file))
            exit(1)
    print("[+] Passed all pre-checks")

def run_test():
    for i in test_queries_mapping:
        prog_file = i[0]
        query_file = i[1]
        os.system("{}autotester {}{}.txt {}{}.txt {}{}_output.xml".format(autotest_directory, 
        design_abstraction_program_directory, prog_file, 
        design_abstraction_queries_directory, query_file, 
        result_directory, query_file))

checks()
run_test()