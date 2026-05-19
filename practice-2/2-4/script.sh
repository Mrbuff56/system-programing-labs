#!/bin/bash

echo "Анализ системных вызовов cat /etc/passwd" > analysis.txt

echo "Размер файла /etc/passwd:" >> analysis.txt
ls -l /etc/passwd >> analysis.txt
echo "" >> analysis.txt

echo "Системные вызовы read() и write():" >> analysis.txt
strace -e trace=read,write cat /etc/passwd 2>&1 >> analysis.txt
echo "" >> analysis.txt

echo "Подсчет байтов в вызовах read():" >> analysis.txt
strace -e trace=read cat /etc/passwd 2>&1 | grep "read(" | awk -F'= ' '{print $2}' | while read bytes; do
    if [ "$bytes" -gt 0 ] 2>/dev/null; then
        echo "read: $bytes байт" >> analysis.txt
    fi
done
echo "" >> analysis.txt

echo "Подсчет байтов в вызовах write():" >> analysis.txt
strace -e trace=write cat /etc/passwd 2>&1 | grep "write(" | awk -F'= ' '{print $2}' | while read bytes; do
    if [ "$bytes" -gt 0 ] 2>/dev/null; then
        echo "write: $bytes байт" >> analysis.txt
    fi
done
echo "" >> analysis.txt

echo "Сравнение с размером файла:" >> analysis.txt
filesize=$(stat -c%s /etc/passwd 2>/dev/null || ls -l /etc/passwd | awk '{print $5}')
echo "Размер /etc/passwd: $filesize байт" >> analysis.txt

cat analysis.txt