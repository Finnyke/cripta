#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <locale>

using namespace boost::multiprecision;

int128_t v = 1;

long long gcd(long long a, long long b) {
	long long r;
	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

long long lcm(long long a, long long b) {
	return a * b / gcd(a, b);
}

long long foo(long long a, long long b, long long p) {
	auto A = static_cast<uint128_t>(a);
	auto B = static_cast<uint128_t>(b);
	return static_cast<long long>((A * B) % static_cast<uint128_t>(p));
}

long long power(long long base, long long pow, long long m) {
	uint128_t ba, po, mo;
	ba = static_cast<uint128_t>(base);
	po = static_cast<uint128_t>(pow);
	mo = static_cast<uint128_t>(m);
	uint128_t r, res = 1;
	uint128_t s = ba;
	while (po) {
		r = po % 2;
		po /= 2;
		uint128_t temp = s % mo;
		if (temp < 0) temp += mo;
		if (r == 1) {
			uint128_t temp2 = (res % mo);
			if (temp2 < 0) temp2 += mo;
			uint128_t temp3 = (temp2 * temp) % mo;
			if (temp3 < 0) temp3 += mo;
			res = temp3;
		}
		uint128_t temp2 = (temp * temp) % mo;
		if (temp2 < 0) temp2 += mo;
		s = temp2;
	}
	if (res < 0) res += mo;
	return static_cast<long long>(res);
}

long long inverse(long long a, long long m) {
	long long q, u[2]{ 0 }, v[2]{ 0 }, t[2]{ 0 };
	q = 0;
	u[0] = a;
	u[1] = 1;
	v[0] = m;
	while (v[0]) {
		q = u[0] / v[0];
		t[0] = u[0] % v[0];
		t[1] = u[1] - q * v[1];

		u[0] = v[0];
		u[1] = v[1];

		v[0] = t[0];
		v[1] = t[1];
	}
	if (u[1] < 0) u[1] += m;
	return u[1];
}

char alphabet[26]{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
char RUalphabet[33]{ 'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ё', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П',
'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я' };

char toupperRU(char c) {
	if (c >= 'а' && c <= 'я') return c - 32;
	else if (c == 'ё') return 'Ё';
	return c;
}

void elg() {
	std::string M;
	std::cout << "Введите сообщение M английскими буквами: ";
	std::cin >> M;
	for (auto& c : M) c = toupper(c);
	std::cout << "M = " << M << " = ";
	long long m = 0;
	for (long long i = M.length() - 1; i >= 0; --i) {
		for (auto j = 0u; j < 26; ++j) {
			if (M[M.length() - 1 - i] == alphabet[j]) {
				m += pow(26ull, i) * j;
				std::cout << j << " * 26^" << i << " + ";
				break;
			}
		}
	}
	std::cout << '\b' << '\b' << "= " << m << std::endl;
	std::string temp;
	std::cout << "Введите простое число p: ";
	std::cin >> temp;
	long long p, g, x;
	p = atoll(temp.c_str());
	std::cout << "Введите число g, меньшее p: ";
	std::cin >> temp;
	g = atoll(temp.c_str());
	std::cout << "Введите число x, меньшее p: ";
	std::cin >> temp;
	x = atoll(temp.c_str());
	long long y = power(g, x, p);
	std::cout << "p = " << p << "\ng = " << g << "\nx = " << x << "\ny = g^x(mod p) = " << y << std::endl;
	std::cout << "открытый ключ = (y,g,p) = (" << y << ", " << g << ", " << p << ")\nсекретный ключ = x = " << x << std::endl;
	bool f = true;
	long long k;
	while (f) {
		f = !f;
		std::cout << "Введите k (НОД(k, p-1) = 1): ";
		std::cin >> temp;
		k = atoll(temp.c_str());
		if (gcd(k, p - 1) != 1) {
			std::cout << "НОД(k, p-1) = " << gcd(k, p - 1) << std::endl;
			f = !f;
		}
	}
	long long a, b;
	a = power(g, k, p);
	std::cout << "a = g^k(mod p) = " << a << std::endl;
	std::cout << "M = (xa + kb)(mod p-1) => b = ";
	b = (inverse(k, p - 1) * (m - (x % (p - 1)) * (a % (p - 1)) % (p - 1))) % (p - 1);
	if (b < 0) b += (p - 1);
	std::cout << b << std::endl;
	std::cout << "(y^a * a^b)(mod p) = " << foo(power(y, a, p), power(a, b, p), p) << "\ng^M(mod p) = " << power(g, m, p);
}

void rsa() {
	std::string M;
	std::cout << "Введите сообщение M русскими буквами: ";
	std::cin >> M;
	long long p;
	long long q;
	long long e;
	long long H0;
	std::string temp;
	std::cout << "Введите простое число p: ";
	std::cin >> temp;
	p = atoll(temp.c_str());
	std::cout << "Введите простое число q: ";
	std::cin >> temp;
	q = atoll(temp.c_str());
	long long N = p * q;
	long long phiN = (p - 1) * (q - 1);
	std::cout << "Введите e: ";
	std::cin >> temp;
	e = atoll(temp.c_str());
	std::cout << "q = " << q << "\np = " << p << "\nN = p * q = " << N << "\nphi(N) = (p - 1) * (q - 1) = " << phiN << std::endl;
	long long D = inverse(e, phiN);
	std::cout << "e = " << e << "\nD = e^(-1)mod(phi(N)) = " << D << "\nсекретный ключ = (D, N) = (" << D
		<< ", " << N << ')' << std::endl;
	for (auto& c : M) c = toupperRU(c);
	std::cout << "M = " << M << std::endl;
	std::cout << "Введите H0: ";
	std::cin >> temp;
	H0 = atoll(temp.c_str());
	std::vector<long long> Ms;
	for (auto i = 0ll; i < M.length(); ++i) {
		for (auto j = 1ll; j <= 33; ++j) {
			if (M[i] == RUalphabet[j - 1]) {
				std::cout << "M" << i + 1 << " = " << RUalphabet[j - 1] << " = " << j << std::endl;
				Ms.push_back(j);
			}
		}
	}
	std::cout << "H0 = " << H0 << std::endl;
	for (auto i = 0ll; i < Ms.size(); ++i) {
		std::cout << "H" << i + 1 << " = ((H" << i << " + M" << i + 1 << ")^2)(mod N) = ";
		H0 = power((H0 + Ms[i]), 2, N);
		std::cout << H0 << std::endl;
	}
	long long r = H0;
	std::cout << "r = H" << Ms.size() << " = " << H0 << std::endl;
	long long S = power(r, D, N);
	long long r1 = power(S, e, N);
	std::cout << "S = r^D(mod N) = " << S << "\nr' = S^e(mod N) = " << r1 << std::endl;
}

int main() {
	try {
		setlocale(LC_ALL, "Russian");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		std::string answer;
	m1:
		std::cout << "Практика 2.\n1. Подпись по алгоритму Эль Гамаля\n2. Подпись по алгоритму RSA" << std::endl;
		std::cin >> answer;
		if (answer.at(0) != '1' && answer.at(0) != '2') {
			system("cls");
			goto m1;
		}
		switch (answer.at(0)) {
		case '1':
			elg();
			break;
		case '2':
			rsa();
			break;
		default:
			throw "Unexpected runtime error in switch: entered default";
		}

	}
	catch (...) {
		std::cerr << "An exception occured. Shutting down.";
	}

	std::cin.get();
	std::cin.get();
	return 0;
}
