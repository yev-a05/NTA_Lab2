﻿// NTA_Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <set>
#include <algorithm>
#include <windows.h>

using namespace std;
using namespace chrono;

// Функція для перевірки, чи є число генератором
bool is_generator(long long a, long long p) {
    if (a >= p) return false;

    set<long long> residues;
    long long current = 1;
    for (long long i = 0; i < p - 1; ++i) {
        residues.insert(current);
        current = (current * a) % p;
    }
    return residues.size() == p - 1;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    long long p, a, b;
    cout << "Введіть просте число p: ";
    cin >> p;

    while (true) {
        cout << "Введіть можливий генератор a: ";
        cin >> a;

        if (is_generator(a, p)) {
            cout << "Число a є генератором групи Z*_" << p << ".\n";
            break;
        }
        else {
            cout << "Число a не є генератором. Спробуйте ще раз.\n";
        }
    }

    cout << "Введіть елемент b: ";
    cin >> b;

    auto start_time = high_resolution_clock::now();

    // Вектор для зберігання всіх рішень
    vector<long long> solutions;

    // Звичайний перебір для знаходження всіх можливих x
    for (long long x = 0; x <= p - 1; ++x) {
        if (static_cast<long long>(pow(a, x)) % p == b) {
            solutions.push_back(x);
        }
        // Перевірка часу кожну 1000 ітерацій
        if (x % 1000 == 0) {
            auto current_time = high_resolution_clock::now();
            duration<double> elapsed = current_time - start_time;
            if (elapsed.count() > 300) { // 300 секунд = 5 хвилин
                cout << "Програма перевищила обмеження часу (5 хвилин)." << endl;
                return 1;
            }
        }
    }

    if (!solutions.empty()) {
        cout << "Знайдені розв'язки: ";
        for (const auto& sol : solutions) {
            cout << endl << "x = " << sol;
        }
        cout << endl;
    }
    else {
        cout << "Розв'язок не знайдено." << endl;
    }

    return 0;
}