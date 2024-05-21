import os
import time


def main():

    base = []
    case = []
    # case.append("file sort cat fileout")
    # case.append("file sort \"cat -e\" fileout")
    # case.append("file sort cat newfile")
    # case.append("notafile sort cat newfile")
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

    print("------------------------------------------")

    for i in range(0, len(case)):

        print(f" test {i}:")
        print(f"({base[i]})")
        r = os.system(f'{base[i]}')
        print(r >> 8)
        print(f"(./pipex {case[i]})")
        r = os.system(f'./pipex {case[i]}')
        print(r >> 8)
        print("------------------------------------------")
        time.sleep(1)


if __name__ == "__main__":
    main()
