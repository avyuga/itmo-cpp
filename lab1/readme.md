# Лабораторная работа №1
Запуск программы-генератора:
```bash
g++ -std=c++20 .\lab1.cpp -o lab1.exe
.\lab1.exe
```

Запуск проверки сгенерированного файла:
```bash
g++ -c .\function.cpp
g++ -c .\main.cpp    
g++ *.o -o output.exe
.\output.exe
```