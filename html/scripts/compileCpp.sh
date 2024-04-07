#!/bin/bash

# Define file paths
templatePath="../../cpp/source/template.cpp"
finalPath="../../cpp/source/processData.cpp"

# Read template code
sourceCode=$(<"$templatePath")

# Replace occurrences of '<<DATAPROCESS>>' with the content of the provided argument
finalCode="${sourceCode//<<DATAPROCESS>>/$1}"

# Write the modified content back to file B
rm -f "../../cpp/source/processData.cpp"
echo "$finalCode" > "$finalPath"

g++ -o "../../cpp/bin/processData" "../../cpp/source/processData.cpp"
rm -f "../../cpp/source/processData.cpp"
