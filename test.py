import os
import time


RED = '\033[91m'
GREEN = '\033[92m'
YELLOW = '\033[93m'
BLUE = '\033[94m'
MAGENTA = '\033[95m'
CYAN = '\033[96m'
RESET = '\033[0m'


def main():

    files = []
    files.append("fileout")
    files.append("newfile")
    files.append("compressed_file")
    files.append("unique_values")
    files.append("locked")

    base = []
    case = []
    base.append("< file sort | cat -e > fileout")
    case.append("file sort \"cat -e\" fileout")
    base.append("< file wc -w | sort > fileout")
    case.append("file \"wc -w\" sort fileout")
    base.append("< notafile sort | cat > newfile")
    case.append("notafile sort cat newfile")
    base.append("< file gzip | base64 > compressed_file")
    case.append("file gzip base64 compressed_file")
    base.append("< file sort | uniq > unique_values")
    case.append("file sort uniq unique_values")
    base.append("< notafile sort | sdfjh > fileout")
    case.append("notafile sort sdfjh fileout")

    os.system('touch locked && chmod 000 locked')

    base.append("< locked sort | cat > fileout")
    case.append("locked sort cat fileout")
    base.append("< file sort | cat > locked")
    case.append("file sort cat locked")
    base.append("""< file echo "$num 1" | awk '{printf "%02d", $1 + $2}' > fileout""")
    case.append("""file 'echo "$num 1"'  'awk "{printf "%02d", $1 + $2}"' fileout""")

    print("------------------------------------------")

    for i in range(0, len(case)):

        print(MAGENTA + f" test {i}:" + RESET)
        print(f"({base[i]})")
        r1 = os.system(f'{base[i]}')
        print(r1 >> 8)
        print(f"(./pipex {case[i]})")
        r2 = os.system(f'./pipex {case[i]}')
        print(r2 >> 8)
        if (r1 >> 8) == (r2 >> 8):
            print(GREEN + " OK" + RESET)
        else:
            print(RED + " KO" + RESET)
        print("------------------------------------------")
        time.sleep(1)

    for i in range(0, len(case)):

        print(BLUE + f" mem leak test {i}:" + RESET)
        print(f"(./pipex {case[i]})")
        os.system(f'valgrind --trace-children=yes {case[i]}')
        print("------------------------------------------")
        time.sleep(1)

    os.system('chmod 777 locked')

    for i in files:
        os.system(f'rm {i}')

    print("Enter a few lines of input the hit <ctrl-d>")
    os.system("./pipex /dev/stdin sort cat fileout")


if __name__ == "__main__":
    main()
