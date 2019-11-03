# This file should be placed in the Code11 directory.
import os
import glob

design_abstraction_program_query_mapping = [
                        ("follows_parent", "follows"),
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
                        ("nextT", "nextT"),
                        ("next_affects", "affects"),
                        ("next_affects", "affectsT"),
                        ("pattern", "pattern"),
                        ("with", "with")]

system_test_program_query_mapping = [
                        ("i1_systest_test1_program", "i1_systest_test1_query"),
                        ("i1_systest_test2_program", "i1_systest_test2_query"),
                        ("i1_systest_test3_program", "i1_systest_test3_query"),
                        ("i2_systest_test_program", "i2_systest_test_query"),
                        #("i3_systest_test1_program", "i3_systest_test1_query"),
                        ("i3_systest_test2_program", "i3_systest_test2_query"),
                        ("i3_systest_test3_program", "i3_systest_test3_query"),
                        ("i3_systest_test4_program", "i3_systest_test4_query")]

autotest_directory = "./cmake-build-debug/src/autotester/"
design_abstraction_program_directory = "./tests/design_abstraction_test/programs/"
design_abstraction_queries_directory = "./tests/design_abstraction_test/queries/"
system_test_program_queries_directory = "./tests/system_test/"
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
    for i in design_abstraction_program_query_mapping:
        prog_file = i[0]
        query_file = i[1]
        if not os.path.exists("{}{}.txt".format(design_abstraction_program_directory, prog_file)):
            print("{}.txt does not exist.".format(prog_file))
            exit(1)
        if not os.path.exists("{}{}.txt".format(design_abstraction_queries_directory, query_file)):
            print("{}.txt does not exist.".format(query_file))
            exit(1)

    for i in system_test_program_query_mapping:
        prog_file = i[0]
        query_file = i[1]
        if not os.path.exists("{}{}.txt".format(system_test_program_queries_directory, prog_file)):
            print("{}.txt does not exist.".format(prog_file))
            exit(1)
        if not os.path.exists("{}{}.txt".format(system_test_program_queries_directory, query_file)):
            print("{}.txt does not exist.".format(query_file))
            exit(1)

    print("[+] Passed all pre-checks")

def run_test():
    for i in design_abstraction_program_query_mapping:
        prog_file = i[0]
        query_file = i[1]
        os.system("{}autotester {}{}.txt {}{}.txt {}{}_output.xml".format(autotest_directory, 
        design_abstraction_program_directory, prog_file, 
        design_abstraction_queries_directory, query_file, 
        result_directory, query_file))

    for i in system_test_program_query_mapping:
        prog_file = i[0]
        query_file = i[1]
        os.system("{}autotester {}{}.txt {}{}.txt {}{}_output.xml".format(autotest_directory, 
        system_test_program_queries_directory, prog_file, 
        system_test_program_queries_directory, query_file, 
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