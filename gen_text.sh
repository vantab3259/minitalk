#!/bin/bash

# Set the output file name and size
output_file="output.txt"
output_size=$((5000000))

# Generate random characters using /dev/urandom, remove any null bytes, and write to file
tr -cd '[:print:]' </dev/urandom | head -c "$output_size" > "$output_file"

# Print message to indicate file generation is complete
echo "File generation complete. Output file: $output_file"
