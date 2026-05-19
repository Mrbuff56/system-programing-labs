Задание 1-3: Файловая система и права
Требования:
•Bash скрипты
•Работа с правами доступа (chmod)
•Запуск: chmod +x script.sh && ./script.sh

Вариант 6: Создать директорию archive, 10 файлов внутри. Заархивировать: tar -czf
archive.tar.gz archive/. Удалить archive. Распаковать и проверить

Используемые команды:
mkdir -p - создание директории 
echo - создание содержимого файлов
chmod - изменение прав доступа к файлам
tar -czf - создание сжатого tar-архива 
tar -xzf - распаковка сжатого tar-архива
rm -rf - рекурсивное удаление директории
ls -la - вывод подробной информации о файлах и директориях
Запуск: chmod +x script.sh && ./script.sh

Пример вывода:
Проверка:
total 0
drwxrwxrwx 1 komar komar 512 Feb  5 15:46 .
drwxrwxrwx 1 komar komar 512 Feb  5 18:00 ..
-rwxrwxrwx 1 komar komar   7 Feb  5 18:00 file1.txt
-rwxrwxrwx 1 komar komar   8 Feb  5 18:00 file10.txt
-rwxrwxrwx 1 komar komar   7 Feb  5 18:00 file2.txt
-rwxrwxrwx 1 komar komar   7 Feb  5 18:00 file3.txt
-rwxrwxrwx 1 komar komar   7 Feb  5 18:00 file4.txt
-rwxrwxrwx 1 komar komar   7 Feb  5 18:00 file5.txt
-rwxrwxrwx 1 komar komar   7 Feb  5 18:00 file6.txt
-rwxrwxrwx 1 komar komar   7 Feb  5 18:00 file7.txt
-rwxrwxrwx 1 komar komar   7 Feb  5 18:00 file8.txt
-rwxrwxrwx 1 komar komar   7 Feb  5 18:00 file9.txt
