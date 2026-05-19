#!/bin/bash

mkdir -p archive

for i in {1..10}; do
    echo "File $i" > "archive/file$i.txt"
    chmod 755 "archive/file$i.txt"
done

tar -czf archive.tar.gz archive/
rm -rf archive/
tar -xzf archive.tar.gz

echo "Проверка:"
ls -la archive/

