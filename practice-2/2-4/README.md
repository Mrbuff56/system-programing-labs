Задание 2-4: Отладка с strace
Требования:
•Используйте strace для анализа системных вызовов
•Сохраните команды и результаты в analysis.txt

Вариант 6: Использовать strace cat /etc/passwd. Найти вызовы read() и write().
Подсчитать байты. Сравнить с размером файла ls -l /etc/passwd

Инициализация файла анализа - создание файла analysis.txt
Определение размера файла - использование ls -l /etc/passwd
Трассировка системных вызовов - strace -e trace=read,write
Анализ вызовов read() - фильтрация, извлечение и подсчет байт
Анализ вызовов write() - аналогично для write
Сравнение с фактическим размером - использование stat или ls
Вывод результатов - отображение содержимого analysis.txt
Запуск: chmod +x script.sh && ./script.sh

Пример вывода:
komar@DESKTOP-DAHGGQB:/mnt/c/Users/komar/Downloads/system-programming-labs_Old-main/system-programming-labs/practice-2/2-4$ sudo chmod +x script.sh && sudo ./script.sh
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0 \250\2\0\0\0\0\0"..., 832) = 832
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
read(3, "nodev\tsysfs\nnodev\ttmpfs\nnodev\tbd"..., 1024) = 442
read(3, "none /usr/lib/modules/6.6.87.2-m"..., 1024) = 1024
read(3, "\ndevpts /dev/pts devpts rw,nosui"..., 1024) = 1024
read(3, "lient,msize=65536,trans=fd,rfd=6"..., 1024) = 1024
read(3, " /mnt/wslg/run/user/1000 tmpfs r"..., 1024) = 393
read(3, "", 1024)                       = 0
read(3, "5ae341f41000-5ae342033000 r--p 0"..., 1024) = 1024
read(3, "77fe000-78a9f77ff000 r--p 000a90"..., 1024) = 1024
read(3, "00 08:30 14387                  "..., 1024) = 1024
read(3, "             /usr/lib/x86_64-lin"..., 1024) = 1024
read(3, "                      /usr/lib/x"..., 1024) = 479
read(3, "# Common strings shared across a"..., 4080) = 4080
read(3, "", 32)                         = 0
read(4, "root:x:0:0:root:/root:/bin/bash\n"..., 16384) = 1378
write(1, "root:x:0:0:root:/root:/bin/bash\n"..., 1378) = 1378
read(3, "", 65536)                      = 0
+++ exited with 0 +++
Анализ системных вызовов cat /etc/passwd
Размер файла /etc/passwd:
-rw-r--r-- 1 root root 1378 May 19 18:24 /etc/passwd

Системные вызовы read() и write():
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
sync:x:4:65534:sync:/bin:/bin/sync
games:x:5:60:games:/usr/games:/usr/sbin/nologin
man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
irc:x:39:39:ircd:/run/ircd:/usr/sbin/nologin
_apt:x:42:65534::/nonexistent:/usr/sbin/nologin
nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
systemd-network:x:998:998:systemd Network Management:/:/usr/sbin/nologin
dhcpcd:x:996:996:DHCP Client Daemon:/usr/lib/dhcpcd:/bin/false
messagebus:x:995:995:System Message Bus:/nonexistent:/usr/sbin/nologin
syslog:x:100:101::/nonexistent:/usr/sbin/nologin
systemd-resolve:x:989:989:systemd Resolver:/:/usr/sbin/nologin
_chrony:x:988:988:Chrony Daemon:/var/lib/chrony:/usr/sbin/nologin
landscape:x:101:103::/var/lib/landscape:/usr/sbin/nologin
polkitd:x:987:987:User for polkitd:/:/usr/sbin/nologin
komar:x:1000:1000::/home/komar:/bin/bash

Подсчет байтов в вызовах read():
read: 832 байт
read: 832 байт
read: 832 байт
read: 832 байт
read: 832 байт
read: 442 байт
read: 1024 байт
read: 1024 байт
read: 1024 байт
read: 393 байт
read: 1024 байт
read: 1024 байт
read: 1024 байт
read: 1024 байт
read: 479 байт
read: 4080 байт

Подсчет байтов в вызовах write():

Сравнение с размером файла:
Размер /etc/passwd: 1378 байт