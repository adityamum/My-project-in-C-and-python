import csv
import sys


def main():

    # TODO: Check for command-line usage

    if(len(sys.argv) != 3):
        print("Usage: dna [.csv][.txt]")

    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as file:
        file_reader = csv.DictReader(file)
        dlist = list(file_reader)



    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as f:
        f_contents = f.read()
        

    # TODO: Find longest match of each STR in DNA sequence
    str_d = {}

    n = dlist[0]

    for key, values in n.items():
        if key != "name":
            str_d[key] = values


    for STR in str_d:
        str_d[STR] = longest_match(f_contents, STR)
    # TODO: Check database for matching profiles

    flag = 0

    for i in range(len(dlist)):
        match = 0
        no_match = 0
        for key in str_d:
            if int(dlist[i][key]) == str_d[key]:
                match = match + 1



        if match == len(str_d):
            print(dlist[i]['name'])
            flag = 1


    if flag != 1:
        print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
