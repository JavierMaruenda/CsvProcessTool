#!/usr/bin/env python3

import cgi
import sys
import csv
import json
import os

# Get the file name from the POST request
form = cgi.FieldStorage()
fileName = form.getvalue("file", "")
csvFilePath = os.path.abspath("../../user/input/" + fileName)

print("Content-Type: application/json")
print()

# Initialize lists to store channel names and data
names = []
data = []

# Call the specified executable passing the number as an argument
try:
    # Read data from the CSV file
    with open(csvFilePath, "r") as file:
        reader = csv.reader(file)
        # Read the first row containing channel names
        names = next(reader)
        # Read the rest of the rows containing data
        for row in reader:
            data.append(row)

    # Transpose the data
    data = list(zip(*data))

    # Prepare JSON object
    json_data = {
        "fileName": fileName,
        "names": names,
        "data": data
    }

    # Return JSON data
    print(json.dumps(json_data))
except Exception as e:
    # Print any exceptions raised
    print(json.dumps({"error": str(e)}))
    sys.exit(1)
