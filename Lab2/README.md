# Лабораторная работа №2.
Реализовано численное интегрирование методом трапеций по формуле Котеса.
  - однопоточное умножение;
  - многопоточное умножение (отрезки интегрирования равномерно распределяются между потоками):

Для синхронизации между потоками используется директива reduction.

## Результат
Скорость умножения при количестве разбиений отрезка = 10000000 для Ryzen 3 3100 (4 cores, 8 threads):
```console
Введите количество разбиений отрезка [a; b]: 10000000

Single result = 3.14159
Single thread time = 0.628sec.


Multithread result = 3.14159
Multi thread time = 0.116sec.
```
