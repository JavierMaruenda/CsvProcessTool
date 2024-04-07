#!/bin/bash

# Destination directory for compiled files
destination="../bin"

# Source files without extension
sources=("processData" "writeFile" "readFile")

# Compile and move each source file
for file in "${sources[@]}"; do
    g++ -o "$destination/$file" "$file.cpp"
    if [ $? -eq 0 ]; then
        echo -e "Compilation of \t $file \t successful. \t Executable saved in \t $destination directory."
    else
        echo "Compilation of $file.cpp failed."
    fi
done
