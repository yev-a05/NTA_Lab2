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

// ������� ��� �������� ����� n �� ����� ��������
vector<pair<int, int>> primeFactorization(int n) {
    vector<pair<int, int>> factors;
    
    // ������� �� 2
    int count = 0;
    while (n % 2 == 0) {
        count++;
        n /= 2;
    }
    if (count > 0) {
        factors.push_back({ 2, count });
    }

    // ������� �� ������ ����� �����
    for (int i = 3; i <= sqrt(n); i += 2) {
        count = 0;
        while (n % i == 0) {
            count++;
            n /= i;
        }
        if (count > 0) {
            factors.push_back({ i, count });
        }
    }

    // ���� n - ������ ����� ����� 2
    if (n > 2) {
        factors.push_back({ n, 1 });
    }

    return factors;
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

    vector<pair<int, int>> factors = primeFactorization(n);

    cout << "��������� ������� ����� " << n << ": ";
    for (size_t i = 0; i < factors.size(); ++i) {
        std::cout << factors[i].first << "^" << factors[i].second;
        if (i != factors.size() - 1) {
            std::cout << " � ";
        }
    }
    cout << endl;


    return 0;
}