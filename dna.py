import sys
import csv

if len(sys.argv) != 3:
    sys.exit

people = []
genes = []
genecounts = []
found = 0
with open(sys.argv[1], "r") as database:
    reader = csv.DictReader(database)
    for i in reader:
        for x in range(1, len(i)):
            x = int(x)
        people.append(i)
    genes = reader.fieldnames
    genes.pop(0)


with open(sys.argv[2], "r") as sequence:
    string = sequence.read()
    for z in range(len(genes)):
        biggest = 0
        for i in range(len(string)):
            count = 0
            x = string.find(genes[z], i, len(string))
            while string[x:x+len(genes[z])] == genes[z]:
                x = x + len(genes[z])
                count += 1
                if count > biggest:
                    biggest = count
        genecounts.append(biggest)

genesdict = dict(zip(genes, genecounts))

for i in range(len(people)):
    genematch = 0
    for x in range(len(genes)):
        if int(people[i][genes[x]]) == int(genesdict[genes[x]]):
            genematch += 1
    if genematch == len(genesdict):
        found = 1
        print(people[i]["name"])


if found == 0:
    print("No match.")
