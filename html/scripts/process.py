#!/usr/bin/env python3

import cgi
import sys
import csv
import json
import os
import subprocess
from io import StringIO

# Get the data file name from the POST request
form = cgi.FieldStorage()
fileName = form.getvalue("file", "")
userProcess = form.getvalue("text", "")

# Form all required file paths
csvFilePath = os.path.abspath("../../user/data/" + fileName)
processedcsvFilePath = os.path.abspath("../../user/data/processed/" + fileName)
cppExecPath = "../../cpp/bin/processData"

# Initialize output
print("Content-Type: application/json")
print()

# Initialize lists to store channel names and data
names = []
data = []
errors = ""

# Call permissions.sh (Ensures process folder has write permission)
# subprocess.run(["bash", "../../config/permissions.sh"])

# Call the specified executable passing the number as an argument
try:
    # Process the data with the c++ executable
    process = subprocess.Popen([cppExecPath, csvFilePath], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = process.communicate()

    # Capture errors from stderr
    errors = err.decode("utf-8")

    if process.returncode != 0:
        raise Exception(errors)

    # Read data from the CSV file
    with open(processedcsvFilePath, "r") as file:
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
        "data": data,
        "userProcess": userProcess,
        "processLog": errors  # Include errors in the JSON output
    }

    # Return JSON data
    print(json.dumps(json_data))
except Exception as e:
    # Print any exceptions raised
    print(json.dumps({"error": str(e), "errors": errors}))
    sys.exit(1)
