import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py DATABASE SEQUENCE")
        sys.exit(1)

    database_fname = sys.argv[1]
    sequence_fname = sys.argv[2]

    database = []

    with open(database_fname) as d_f:
        reader = csv.DictReader(d_f)
        for row in reader:
            database.append(row)

    with open(sequence_fname) as s_f:
        sequence = s_f.read()

    # Check all STR keys available for testing.
    str_keys = []
    for key in database[0].keys():
        if key != "name":
            str_keys.append(key)

    # Create a dict storing all longest_matches found in the DNA sequence.
    sequence_strs = {}
    for str in str_keys:
        sequence_strs[str] = longest_match(sequence, str)

    # Create an list of dicts storing all people STRs in the database for checking
    people_strs = []
    for person in database:
        person_strs = {}
        for str in str_keys:
            person_strs[str] = int(person[str])
        people_strs.append(person_strs)

    # For each person_strs in people_strs, check if any of them matches sequence_strs
    for index, person_strs in enumerate(people_strs):
        if person_strs == sequence_strs:
            found_name = database[index]["name"]
            print(found_name)
            break
    else:
        print("No match")

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
