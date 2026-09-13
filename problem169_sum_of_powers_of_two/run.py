import re




if __name__ == "__main__":

    binstr = bin(10**25)
    print(binstr)

    sets = []

    while binstr != "0b":
        x = re.search("^(.*)(10*)$", binstr)
        l = len(x.group(2))
        sets.append(l)
        binstr = x.group(1)
    
    print(sets)

    num_ways = 1
    num_ways_substr_lose_msb = 0
    for s in sets:
        temp = num_ways
        num_ways = num_ways*s + num_ways_substr_lose_msb
        num_ways_substr_lose_msb = temp*(s-1) + num_ways_substr_lose_msb

    print(num_ways)