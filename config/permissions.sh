#!/bin/bash

# Get the directory where the script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Change permissions
chmod -R 775 "$SCRIPT_DIR"/../config
chmod -R 777 "$SCRIPT_DIR"/../cpp/source
chmod -R 777 "$SCRIPT_DIR"/../cpp/bin
chmod -R 775 "$SCRIPT_DIR"/../html
chmod -R 777 "$SCRIPT_DIR"/../user
