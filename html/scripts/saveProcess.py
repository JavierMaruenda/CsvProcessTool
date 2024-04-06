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

# Save the text content to the file
#with open(filepath, 'w') as file:
#    file.write(text_content)
#os.chmod(filepath, 0o777)

process = subprocess.Popen(["../../cpp/bin/writeFile", filepath, text_content], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Print a success message or any relevant output
print("Content-Type: text/html")
print()
print("File saved")
