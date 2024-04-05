#!/bin/bash

# Get the directory where the script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Change permissions recursively to 775 from one level up
chmod -R 775 "$SCRIPT_DIR"/..

# Change permissions of the 'processed' folder to 777
chmod -R 777 "$SCRIPT_DIR"/../user/data/processed
