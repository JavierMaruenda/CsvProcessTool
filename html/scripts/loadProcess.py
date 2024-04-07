#!/usr/bin/env python3

import cgi
import os
import subprocess
import sys
import json

# Get the text area content and file name from the POST request
form = cgi.FieldStorage()
filename = form.getvalue("file", "unnamed.txt")  # Default filename if not provided

# Construct the full path to read the file
filepath = os.path.abspath("../../user/processes/" + filename)

print("Content-Type: application/json")
print()

# Read the file content
#with open(filepath, 'r') as file:
#    content = file.read()

process = subprocess.Popen(["../../cpp/bin/readFile", filepath], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout, stderr = process.communicate()  # Capture stdout and stderr
content = stdout.decode().strip()

# Send the response back as JSON
response = {"content": content}
print(json.dumps(response))
