people = {
    "Carter": "+1-617-495-1000",
    "David": "+1-617-495-1000",
    "John": "+1-949-458-2750",
}

name = input("name: ")

if name in people:
    print(f"Found {people[name]}")
else:
    print("Not found")
