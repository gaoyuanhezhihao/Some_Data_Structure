import subprocess
from random import randrange, random, choice, shuffle, sample
import string
# with open("./input.txt", 'r') as f:
    # text = f.read()


def test(src, pats):
    text = '\n'.join([str(len(pats))] + pats + [src])
    proc = subprocess.Popen(
        '../bin/demo', stdout=subprocess.PIPE,
        stdin=subprocess.PIPE)
    proc.stdin.write(text)
    proc.stdin.close()
    result = proc.stdout.read()
    proc.wait()
    return result


def random_str(l):
    option = string.ascii_lowercase
    # s = option * (l/len(option))
    # shuffle(s)
    # return ''.join([choice(option) for _ in range(l)])
    return ''.join(sample(option*l, l))


def positive_case(pat_max_len, pat_cnt, src_len):
    pats = [random_str(randrange(1, pat_max_len)) for _ in range(pat_cnt)]
    match_pat = choice(pats)
    src = random_str(src_len)
    pos = randrange(0, len(src))
    src = src[:pos] + match_pat + src[pos:]
    return pats, src


def negative_case(pat_max_len, pat_cnt, src_len):
    pats = [random_str(randrange(pat_max_len/2, pat_max_len)) for _ in range(pat_cnt)]
    src = random_str(src_len)
    while any([-1 != src.find(p) for p in pats]):
        src = random_str(src_len, chars)
    return pats, src


def occurrences(string, sub):
    count = start = 0
    while True:
        start = string.find(sub, start) + 1
        if start > 0:
            count += 1
        else:
            return count

def push(text):
    proc = subprocess.Popen(
        './bin/runner',stdout=subprocess.PIPE,
        stdin=subprocess.PIPE)
    proc.stdin.write(text)
    proc.stdin.close()
    result = proc.stdout.read()
    proc.wait()
    return result

def total_test(cnt=100):
    text_list = [str(cnt)]
    for i in range(cnt):
        pat, src = create_test_case()
        text_list.append(pat)
        text_list.append(src)

    text = '\n'.join(text_list)
    ans_vec = push(text)
    ans_vec = ans_vec.splitlines()
    for i in range(cnt):
        pat = text_list[2*i+1]
        src = text_list[2*i+2]
        expect = occurrences(src, pat)
        print ans_vec[i]
        ans = int(ans_vec[i])
        if expect != ans:
            with open("./WR_case.txt", 'w') as f:
                f.write('\n'.join((pat, src)))
            print "pat: ", pat, '\nsrc: ', src
            print "expect=", expect, " answer=", ans
            return -1
    print "AC all"
    return 0


def test_1by1(cnt, pat_max_len, pat_cnt, src_len):
    # positive_case
    for i in range(cnt):
        pats, src = positive_case(pat_max_len, pat_cnt, src_len)
        ans = test(src, pats)
        if "YES\n" == ans:
            print i, 'is ok'
        else:
            with open("./WR_case.txt", 'w') as f:
                f.write('\n'.join(pats + [src]))
            # print "pat: ", pats, '\nsrc: ', src
            print "expect=true", " answer=", ans
            raise "fail"

    # negative_case
    for i in range(cnt):
        pats, src = negative_case(pat_max_len, pat_cnt, src_len)
        ans = test(src, pats)
        if "NO\n" == ans:
            print "negative %d is ok" % i
        else:
            print "Error! negative %d is wrong" % i
            with open("./WR_case.txt", 'w') as f:
                f.write('\n'.join(pats+[src]))
            raise "fail"


if __name__ == '__main__':
    test_1by1(10, 10**3, 1000, 10**4)
# if __name__ == '__main__':
    # # total_test(10000)
