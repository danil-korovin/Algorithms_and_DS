#!/bin/bash


# Encoding 
echo "Default encoding"
echo "Hello, World!" | ./ascii85

echo "Not streaming encoding"
echo "Hello, World!" | ./ascii85 -e

echo "Streaming encoding"
echo "Hello, World!" | ./ascii85 -s

# Decoding
echo "Decoding"
echo "87cURD_*#4DfTZ)+US2L" | ./ascii85 -d

