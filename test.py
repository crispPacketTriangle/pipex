import os
import time
import argparse


RED = '\033[91m'
GREEN = '\033[92m'
YELLOW = '\033[93m'
BLUE = '\033[94m'
MAGENTA = '\033[95m'
CYAN = '\033[96m'
RESET = '\033[0m'

# The report from Valgrind about calls originating "below main"
# usually relates to the runtime environment or library
# initialization. These are typically not issues you need to
# fix unless they cause significant problems or excessive
# memory usage. Some "still reachable" memory from library
# initialization is normal and expected.


# Allocation Call Stack:
#         Memory was allocated using malloc.
#         The call to malloc was made from an address within the sort program.
#         The call stack traces back to a point "below main" in the C standard
#         library (libc.so.6), indicating this allocation happened during the
#         library initialization.
#
# Interpretation
#
#        "Below Main": The term indicates that the allocation was performed by
#        the C runtime library before entering the main function of your
#        program or as part of the initialization/finalization process of the
#        shared library.
#        libc Initialization: This specific memory allocation might be part of
#        the initialization routines in the C standard library. These routines
#        set up various library-level constructs before main is executed.

def main():

    p = argparse.ArgumentParser(description='PIPEX TESTER')
    p.add_argument('valgrind', metavar='valgrind', type=str, help='run valgrind y/n')
    args = p.parse_args()
    if args.valgrind != "y" and args.valgrind != "n":
        print("not valid input")
        return 0

    base = []
    case = []
    out = []

    os.system('mkdir ../temp_files')
    init_tests(base, case, out)

    print("------------------------------------------")

    for i in range(0, len(case)):

        print(MAGENTA + f" test {i}:" + RESET)
        print(f"({base[i]})")
        r1 = os.system(f'{base[i]}')
        print(r1 >> 8)
        print(f"(./pipex {case[i]})")
        r2 = os.system(f'./pipex {case[i]}')
        print(r2 >> 8)
        print(CYAN + " return value" + RESET)
        if (r1 >> 8) == (r2 >> 8):
            print(GREEN + " OK" + RESET)
        else:
            print(RED + " KO" + RESET)

        check_output(out[i * 2], out[(i * 2) + 1])  # add files from list case[i] + list[i]
                                                    # ls -l command fileout1 and fileout2 have to be in diff directory
        print("------------------------------------------")
        time.sleep(1)

    if args.valgrind == "n":
        return 0

    for i in range(0, len(case)):

        print(BLUE + f" mem leak test {i}:" + RESET)
        print(f"(./pipex {case[i]})")
        os.system(f'valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./pipex {case[i]}')
        print("------------------------------------------")
        time.sleep(1)

    os.system('chmod 777 ../temp_files/locked')

    os.system('rm -rf ../temp_files')

    print(MAGENTA + " test reading from stdin:" + RESET)
    print("(./pipex /dev/stdin sort cat fileout)")
    print("Enter a few lines of input then hit <ctrl-d>")
    os.system("./pipex /dev/stdin sort cat fileout")
    print("\ncat fileout")
    os.system("cat fileout")
    os.system('rm fileout')


def init_tests(base, case, out):

    base.append("< file ls -l | cat > ../temp_files/fileout1")
    case.append("""file "ls -l" cat ../temp_files/fileout2""")

    base.append("< file sort | cat -e > ../temp_files/fileout1")
    case.append("""file sort "cat -e" ../temp_files/fileout2""")

    base.append("< file wc -w | sort > ../temp_files/fileout1")
    case.append("""file "wc -w" sort ../temp_files/fileout2""")

    base.append("< notafile sort | cat > ../temp_files/newfile1")
    case.append("notafile sort cat ../temp_files/newfile2")

    base.append("< file gzip | base64 > ../temp_files/compressed_file1")
    case.append("file gzip base64 ../temp_files/compressed_file2")

    base.append("< file sort | uniq > ../temp_files/unique_values1")
    case.append("file sort uniq ../temp_files/unique_values2")

    base.append("< notafile sort | sdfjh > ../temp_files/fileout1")
    case.append("notafile sort sdfjh ../temp_files/fileout2")

    os.system('touch ../temp_files/locked && chmod 000 temp_files/locked')

    base.append("< locked sort | cat > ../temp_files/fileout1")
    case.append("locked sort cat ../temp_files/fileout2")

    base.append("< file sort | cat > ../temp_files/locked1")
    case.append("file sort cat ../temp_files/locked2")

    base.append("""< file echo "$num 1" | awk '{printf "%02d", $1 + $2}' > ../temp_files/fileout1""")
    case.append("""file 'echo "$num 1"'  'awk "{printf "%02d", $1 + $2}"' ../temp_files/fileout2""")

    out.append("../temp_files/fileout1")
    out.append("../temp_files/fileout2")
    out.append("../temp_files/fileout1")
    out.append("../temp_files/fileout2")
    out.append("../temp_files/fileout1")
    out.append("../temp_files/fileout2")
    out.append("../temp_files/newfile1")
    out.append("../temp_files/newfile2")
    out.append("../temp_files/compressed_file1")
    out.append("../temp_files/compressed_file2")
    out.append("../temp_files/unique_values1")
    out.append("../temp_files/unique_values2")
    out.append("../temp_files/fileout1")
    out.append("../temp_files/fileout2")
    out.append("../temp_files/fileout1")
    out.append("../temp_files/fileout2")
    out.append("../temp_files/locked1")
    out.append("../temp_files/locked2")
    out.append("../temp_files/fileout1")
    out.append("../temp_files/fileout2")

def check_output(f1, f2):

    print(CYAN + " output the same" + RESET)
    r = os.popen(f"diff {f1} {f2}")
    output = r.read()
    print(output)
    if not output:
        print(GREEN + " OK" + RESET)
    else:
        print(RED + " KO" + RESET)
    r.close()


if __name__ == "__main__":
    main()
