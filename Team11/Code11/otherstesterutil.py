# This file should be placed in the Code11 directory.
import os
import glob

program_query_mapping = []

autotest_directory = "./cmake-build-debug/src/autotester/"
test_program_queries_directory = "./tests/others/"
result_directory = "./tests/others_output/"

def checks():
    # General check
    if not os.path.exists(("./tests/others")):
        print("Other folder not found.")
        exit(1)
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
        if not os.path.exists("{}{}".format(test_program_queries_directory, prog_file)):
            print("{}.txt does not exist.".format(prog_file))
            exit(1)
        if not os.path.exists("{}{}".format(test_program_queries_directory, query_file)):
            print("{}.txt does not exist.".format(query_file))
            exit(1)
    print("[+] Passed all pre-checks")

def run_test():
    for i in program_query_mapping:
        prog_file = i[0]
        query_file = i[1]
        os.system("{}autotester {}{} {}{} {}{}_output.xml".format(autotest_directory, 
        test_program_queries_directory, prog_file, 
        test_program_queries_directory, query_file, 
        result_directory, query_file[:-4]))

def process_result():
    print("[+] Processing result files")
    result_files = sorted(glob.glob(result_directory + "*"))

    if "./tests/others_output/analysis.xsl" in result_files:
        result_files.remove("./tests/others_output/analysis.xsl")

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