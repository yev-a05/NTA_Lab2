#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <windows.h>

using namespace std;


// ������� ��� ��������, �� � ����� �����������
bool is_generator(long long a, long long n) {
    int p = n+1;
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

    long long n, a, b;

        cout << "������ ������� ����� n: ";
        cin >> n;

    // �������� �� ��������� a

    while (true) {
        cout << "������ ��������� a: ";
        cin >> a;

        if (is_generator(a, n)) {
            cout << "����� a � ����������� ����� Z*_" << n+1 << ".\n";
            break;
        }
        else {
            cout << "����� a �� � �����������. ��������� �� ���.\n";
        }
    }

    cout << "������ ������� b: ";
    cin >> b;


    return 0;
}