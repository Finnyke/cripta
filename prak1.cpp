#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
#include <boost/multiprecision/cpp_int.hpp>

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


std::string creator = "Program by Maxim Pupykin";

char alphabet[26]{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

int main() {
	try {
		std::string M;
		std::cout << "Input message M: ";
		std::cin >> M;
		long long p;
		long long q;
		long long e;
		std::string temp;
		std::cout << "Input prime number p (i.e. 35279): ";
		std::cin >> temp;
		p = atoll(temp.c_str());
		std::cout << "Input prime number q (i.e. 34361): ";
		std::cin >> temp;
		q = atoll(temp.c_str());
		long long N = p * q;
		long long phiN = (p - 1) * (q - 1);
		std::cout << "Input prime number e (i.e. 65537): ";
		std::cin >> temp;
		e = atoll(temp.c_str());
		std::cout << "q = " << q << "\np = " << p << "\nN = p * q = " << N << "\nphi(N) = (p - 1) * (q - 1) = " << phiN << std::endl;
		long long D = inverse(e, phiN);
		std::cout << "e = " << e << "\nprivate key D = e^(-1)mod(phi(N)) = " << D << "\npublic key = (e, N) = (" << e
			<< ", " << N << ')' << std::endl;
		std::cout << "M = " << M << " = ";
		long long m = 0;
		for (auto& c : M) c = toupper(c);
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
		long long C = power(m, e, N);
		std::cout << "C = M^e(mod N) = " << C << std::endl;
		std::vector<long long> buf;
		long long Ct = C;
		std::cout << std::endl;
		for (;Ct >= 26;) {
			auto temp = Ct;
			auto tempC = Ct;
			std::cout << Ct << " / 26 = ";
			Ct /= 26;
			buf.push_back(temp % 26);
			std::cout << Ct << "\n" << Ct << " * 26 = " << Ct * 26 << "\n" << tempC << " - " << Ct * 26 << " = " << temp % 26 << std::endl;
			std::cout << std::endl;
		}
		buf.push_back(Ct);
		std::string c;
		std::cout << "C = ";
		for (int i = buf.size() - 1; i >= 0; --i) {
			c.push_back(alphabet[buf[i]]);
			std::cout << buf[i] << " * 26^" << i << " + ";
		}
		std::cout << '\b' << '\b' << "= " << c << std::endl;
		long long m1 = power(C, D, N);
		std::cout << "M = C^D(mod N) = " << m1 << std::endl;
		std::vector<long long> buf1;
		long long Ct1 = m1;
		std::cout << std::endl;
		for (; Ct1 >= 26;) {
			auto temp = Ct1;
			auto tempC = Ct1;
			std::cout << Ct1 << " / 26 = ";
			Ct1 /= 26;
			buf1.push_back(temp % 26);
			std::cout << Ct1 << "\n" << Ct1 << " * 26 = " << Ct1 * 26 << "\n" << tempC << " - " << Ct1 * 26 << " = " << temp % 26 << std::endl;
			std::cout << std::endl;
		}
		buf1.push_back(Ct1);
		std::string c1;
		std::cout << "M = ";
		for (int i = buf1.size() - 1; i >= 0; --i) {
			c1.push_back(alphabet[buf1[i]]);
			std::cout << buf1[i] << " * 26^" << i << " + ";
		}
		std::cout << '\b' << '\b' << "= " << c1 << std::endl;
	}
	catch (...) {
		std::cerr << "An exception occured. Shutting down.";
	}

	std::cin.get();
	std::cin.get();
	return 0;
}
