#!/bin/bash
# --- C Compilation and Execution Helper ---
#
# This script automates the compilation and linking process of C programs
# using utilities in the 'utils/' directory.
#
# USAGE: ./run_c.sh <main_c_file>
# EXAMPLE: ./run_c.sh closestSubsetSum.c

# Parse and check agrs
EXECUTABLE_NAME="a.out"
USE_LEAKS=0
while [[ $# -gt 0 ]]; do
  case $1 in
  -l | --leaks)
    USE_LEAKS=1
    shift
    ;;
  *)
    MAIN_FILE="$1"
    shift
    ;;
  esac
done

if [ -z "$MAIN_FILE" ]; then
  echo "Error: Please provide the name of the main C file to execute."
  echo "Usage: $0 [-l|--leaks] <main_c_file>"
  echo "Example: $0 closestSubsetSum.c"
  echo "Example: $0 -l closestSubsetSum.c"
  exit 1
fi
if [ ! -f "$MAIN_FILE" ]; then
  echo "Error: Main file '$MAIN_FILE' not found."
  exit 1
fi

# Define the utility source files.
UTILITY_FILES="utils/src/*.c"
INCLUDE_PATH="-Iutils/include"

echo "-> Compiling $MAIN_FILE with utilities..."
# Compiling and linking
gcc "$MAIN_FILE" \
  $UTILITY_FILES \
  $INCLUDE_PATH \
  -o "$EXECUTABLE_NAME"
# Check the exit status of the compilation command
if [ $? -eq 0 ]; then
  echo "-> Compilation successful!"
  if [ "$USE_LEAKS" = "1" ]; then
    echo "-> Leak detection enabled"
  fi
  echo "-> Running program..."
  echo "----------------------------------------"
  # --- EXECUTION ---
  # Run the newly created executable
  if [ "$USE_LEAKS" = "1" ]; then
    leaks --atExit -- ./"$EXECUTABLE_NAME"
  else
    ./"$EXECUTABLE_NAME"
  fi
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
