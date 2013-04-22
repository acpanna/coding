#!/bin/sh

echo "World writable files:"
echo "---------------------"
find / -type f -perm -o+w -exec ls -l  {} \; 2>&1 | grep -v "find:"

echo "World writable directories:"
echo "------------------------"
find / -type d -perm -o+w -exec ls -ld {} \; 2>&1 | grep -v "find:"

echo "Setuid files:"
echo "------------------------"
ls -lut $(find / -type f \( -perm -4000 -o -perm -2000 \) 2>&1 | grep -v "find:")

read input
