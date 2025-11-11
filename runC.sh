#!/bin/bash

# --- C Compilation and Execution Helper ---
#
# This script automates the compilation and linking process for your C programs,
# especially those utilizing the utilities in the 'utils/' directory.
#
# USAGE: ./run_c.sh <main_c_file>
# EXAMPLE: ./run_c.sh closestSubsetSum.c

# Set the name for the final executable
EXECUTABLE_NAME="a.out"

# --- CHECK FOR INPUT FILE ---
if [ -z "$1" ]; then
  echo "Error: Please provide the name of the main C file to execute."
  echo "Usage: $0 <main_c_file>"
  echo "Exampple: $0 closestSubsetSum.c"
  exit 1
fi

MAIN_FILE="$1"

if [ ! -f "$MAIN_FILE" ]; then
  echo "Error: Main file '$MAIN_FILE' not found."
  exit 1
fi

# Define the utility source files.
# *** UPDATED: Now automatically includes ALL .c files in utils/src/ using a wildcard. ***
UTILITY_FILES="utils/src/*.c"

# Define the include path for header files in utils/include/
INCLUDE_PATH="-Iutils/include"

echo "-> Compiling $MAIN_FILE with utilities..."

# --- COMPILATION AND LINKING ---
# We use all source files ($MAIN_FILE and $UTILITY_FILES) and the include path.
# If you need external libraries (like -lm for math functions), you can add
# them here.
# Note: The $UTILITY_FILES variable will be expanded by the shell to the list of found files.
gcc \
  "$MAIN_FILE" \
  $UTILITY_FILES \
  $INCLUDE_PATH \
  -o "$EXECUTABLE_NAME"

# Check the exit status of the compilation command
if [ $? -eq 0 ]; then
  echo "-> Compilation successful! Running program..."
  echo "----------------------------------------"

  # --- EXECUTION ---
  # Run the newly created executable
  ./"$EXECUTABLE_NAME"

  EXEC_STATUS=$?

  echo "----------------------------------------"
  echo "-> Program finished with exit status $EXEC_STATUS."

  # --- CLEANUP (Optional but recommended) ---
  # Uncomment the line below if you want the script to remove the executable
  # after it runs.
  # rm -f "$EXECUTABLE_NAME"
else
  echo "-> Compilation FAILED."
  exit 1
fi
