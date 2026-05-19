Задание 1-4: Диагностика процессов
Требования:
•Используйте утилиты: ps, top, lsof, /proc, kill
•Сохраните команды и результаты

Вариант 6:
1 Найти процессы systemd: ps aux | grep systemd
2 Выбрать PID
3 Вывести дерево: pstree -p [PID]
4 Вывести /proc/[PID]/cmdline
5 Сохранить в analysis.txt

Используемые команды:
ps aux | grep systemd - поиск процессов systemd
pstree -p [PID] - отображение дерева процессов
/proc/[PID]/ - виртуальная файловая система с информацией о процессах
cat /proc/[PID]/cmdline - аргументы командной строки процесса
head -10 /proc/[PID]/status - основные параметры статуса процесса

Используемые утилиты:
ps - отображение процессов
pstree - отображение дерева процессов
grep - поиск текста
cat - вывод содержимого файлов
head - вывод первых строк файла

Пример вывода:
komar@DESKTOP-DAHGGQB:/mnt/c/Users/komar/Downloads/system-programming-labs_Old-main/system-programming-labs/practice-1/1-4$ ./task
Введите PID процесса systemd: 8

Результаты сохранены в analysis.txt

Содержимое analysis.txt:
Процессы systemd:
root          62  0.2  0.4  50380 16000 ?        S<s  22:14   0:01 /usr/lib/systemd/systemd-journald
systemd+      99  0.1  0.3  22524 13824 ?        Ss   22:14   0:00 /usr/lib/systemd/systemd-resolved
root         115  1.2  0.2  35056 11264 ?        Ss   22:14   0:06 /usr/lib/systemd/systemd-udevd
root         137  0.0  0.0   2880  1792 ?        Ss   22:14   0:00 /bin/sh /usr/lib/systemd/scripts/chronyd-starter.sh -n -F 1
message+     156  0.0  0.1   8800  4864 ?        Ss   22:14   0:00 @dbus-daemon --system --address=systemd: --nofork --nopidfile --systemd-activation --syslog-only
root         180  0.0  0.2  18408  8832 ?        Ss   22:14   0:00 /usr/lib/systemd/systemd-logind
komar        317  0.1  0.3  22488 12928 ?        Ss   22:14   0:00 /usr/lib/systemd/systemd --user
komar       1076  0.0  0.0   2880  1792 pts/0    S+   22:22   0:00 sh -c -- ps aux | grep systemd
komar       1078  0.0  0.0   4120  2304 pts/0    S+   22:22   0:00 grep systemd

Анализируем процесс с PID: 8

Дерево процессов для PID 8:
{init}(8)

Содержимое /proc/8/cmdline:
plan9

Статус процесса :
Name:   init
Umask:  0022
State:  S (sleeping)
Tgid:   7
Ngid:   0
Pid:    8
PPid:   2
TracerPid:      0
Uid:    0       0       0       0
Gid:    0       0       0       0