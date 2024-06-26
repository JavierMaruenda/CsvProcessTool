#!/usr/bin/env python3

import cgi
import os
import subprocess

# Get the text area content and file name from the POST request
form = cgi.FieldStorage()
text_content = form.getvalue("text", "")
filename = form.getvalue("filename", "unnamed.txt")  # Default filename if not provided

# Call permissions.sh (Not working when called from python)
# subprocess.run(["bash", "../../config/permissions.sh"])

# Construct the full path to save the file
filepath = os.path.abspath("../../user/processes/" + filename)

process = subprocess.Popen(["../../cpp/bin/writeFile", filepath, text_content], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout, stderr = process.communicate()  # Capture stdout and stderr

# Print a success message or any relevant output
print("Content-Type: text/html")
print()
print("File saved")
