# This file should be placed in the Code11 directory.
import os
import glob

program_query_mapping = [("follows_parent", "follows_query"),
                        ("follows_parent", "followsT_query"),
                        ("follows_parent", "parent_query"),
                        ("follows_parent", "parentT_query"),
                        ("valid_calls", "calls_query"),
                        ("valid_calls", "callsT_query"),
                        ("invalid_calls_direct", "invalid_calls_direct_query"),
                        ("invalid_calls_cyclic", "invalid_calls_cyclic_query"),
                        ("invalid_calls_missing_procedure", "invalid_calls_missing_procedure_query")
                        ("modifies_uses", "modifies_query"),
                        ("modifies_uses", "uses_query"),
                        ("next_affects", "next_query"),
                        ("nextbipT", "nextbip_query"),
                        ("nextbipT", "nextbipT_query"),
                        ("affectsbip", "affectsbip_query"),
                        ("affectsbip", "affectsbipT_query"),
                        ("nextT", "nextT_query"),
                        ("next_affects", "affects_query"),
                        ("next_affects", "affectsT_query"),
                        ("pattern", "pattern_query"),
                        ("with", "with_query"),
                        ("i1_systest_test1_program", "i1_systest_test1_query"),
                        ("i1_systest_test2_program", "i1_systest_test2_query"),
                        ("i1_systest_test3_program", "i1_systest_test3_query"),
                        ("i2_systest_test_program", "i2_systest_test_query"),
                        ("i3_systest_test1_program", "i3_systest_test1_query"),
                        ("i3_systest_test2_program", "i3_systest_test2_query"),
                        ("i3_systest_test3_program", "i3_systest_test3_query"),
                        ("i3_systest_test4_program", "i3_systest_test4_query")]

autotest_directory = "./cmake-build-debug/src/autotester/"
test_program_queries_directory = "./tests/submission_test/"
result_directory = "./tests/output/"

def checks():
    # General check
    if not os.path.exists(("{}autotester".format(autotest_directory))):
            print("Autotester does not exist.")
            exit(1)
    if not os.path.isdir(("{}".format(result_directory))):
        print("Result directory does not exist. Creating output directory..")
        try:
            os.mkdir(result_directory)
        except OSError:
            print ("Creation of the result directory failed")
            exit(1)
        else:
            print ("Successfully created the directory")        

    # File checks
    for i in program_query_mapping:
        prog_file = i[0]
        query_file = i[1]
        if not os.path.exists("{}{}.txt".format(test_program_queries_directory, prog_file)):
            print("{}.txt does not exist.".format(prog_file))
            exit(1)
        if not os.path.exists("{}{}.txt".format(test_program_queries_directory, query_file)):
            print("{}.txt does not exist.".format(query_file))
            exit(1)
    print("[+] Passed all pre-checks")

def run_test():
    for i in program_query_mapping:
        prog_file = i[0]
        query_file = i[1]
        os.system("{}autotester {}{}.txt {}{}.txt {}{}_output.xml".format(autotest_directory, 
        test_program_queries_directory, prog_file, 
        test_program_queries_directory, query_file, 
        result_directory, query_file))

def process_result():
    print("[+] Processing result files")
    result_files = sorted(glob.glob(result_directory + "*"))

    if "./tests/output/analysis.xsl" in result_files:
        result_files.remove("./tests/output/analysis.xsl")

    if "./tests/output/invalid_calls_missing_procedure_output.xml" in result_files:
        result_files.remove("./tests/output/invalid_calls_missing_procedure_output.xml")

    for rf in result_files:
        with open(rf) as f:
            for line in f:
                if "failed" in line:
                    print("[!] failed found in {}".format(rf))
                    break  
    print("[+] End of processing")     

checks()
run_test()
process_result()