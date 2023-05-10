#!/bin/bash

# Change the path to your minirt executable if needed
MINIRT_EXECUTABLE="./minirt"
MAPS_DIR="scene/error_management"
VALGRIND_OUTPUT="valgrind_output.txt"

if ! command -v valgrind &> /dev/null; then
    echo "Valgrind is not installed. Please install it and try again."
    exit 1
fi

if [ ! -f "$MINIRT_EXECUTABLE" ]; then
    echo "minirt executable not found. Please check the path."
    exit 1
fi

if [ ! -d "$MAPS_DIR" ]; then
    echo "Maps directory not found. Please check the path."
    exit 1
fi

for map in "$MAPS_DIR"/*.rt; do
    echo "Running minirt with map: $map"

    # Run minirt with valgrind
    valgrind --leak-check=full --log-file="$VALGRIND_OUTPUT" "$MINIRT_EXECUTABLE" "$map"

    # Check if there are any memory leaks
    if grep -q "definitely lost: [1-9][0-9]* bytes" "$VALGRIND_OUTPUT"; then
        echo "Memory leak detected when running minirt with map: $map"
    else
        echo "No memory leaks detected for map: $map"
    fi

    # Remove valgrind output file
    rm -f "$VALGRIND_OUTPUT"
    echo "--------------------------------------"
done

echo "Testing completed."

