# Лабораторная работа №3.
Реализован барьер через механизм замков. Каждый поток выводит сообщения №1-2, затем потоки синхронизируются и выводят сообщение №3.
При запуске программы сначала вызывается функция использующая обычный барьер, а затем вызывается функция, реализующая барьер через механизм замков.

## Результат
Работа программы на 8-ми поточном CPU:
```console
Original barrier:
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 3
Сообщение 3
Сообщение 3
Сообщение 3
Сообщение 3
Сообщение 3
Сообщение 3
Сообщение 3


Barrier implementation using lock:
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 1
Сообщение 2
Сообщение 3
Сообщение 3
Сообщение 3
Сообщение 3
Сообщение 3
Сообщение 3
Сообщение 3
Сообщение 3
```
