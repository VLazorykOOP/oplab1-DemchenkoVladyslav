#include <iostream> 
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>
#include <cstdarg>
using namespace std;
namespace exceptions
{
	class recount {

	};
	class toalg2Qnk {
	};
	class toalg2func {
	};
	class MtsToZero {  };
	class MToZero {  };
	class MToOne {  };
}
using namespace exceptions;
namespace Task5 {
	double Min(double ...) {
		va_list args;
		int a = 0;
		va_start(args, a);
		double min_val = va_arg(args, double);
		for (int i = 1; i < a; ++i) {
			double val = va_arg(args, double);
			if (val < min_val) {
				min_val = val;
			}
		}
		va_end(args);
		return min_val;
	}
	string file1 = "dat1.dat";
	string file2 = "dat2.dat";
	string file3 = "dat3.dat";
	namespace alg2
	{
		double T(double x)
		{
			return atan(acos(sin(2 * x)));
		}
		double U(double x)
		{
			return atan(acos(sin(3 * x)));
		}
		double Qqn(double x, double y, double z)
		{
			return x / U(x) + y * T(y) - U(z) * T(z);
		}
		double Qnk1(double x, double y)
		{
			return	1.15 * Qqn(x, y, x + y) - 0.95 * Qqn(y, x, x - y);
		}
		double Qnk(double x, double y)
		{
			return x * Qnk1(x, y) + y * Qnk1(y, x) - 0.05 * Qnk1(x, y) * Qnk1(y, x);
		}
	}
	namespace alg1
	{
		double T(double x)
		{
			fstream fs(file2);
			if (!fs)throw toalg2func();
			if (x >= -10 || x <= 10)throw toalg2Qnk();
			double X, value;
			fs >> X >> value;
			while (X < x)
			{
				fs >> X >> value;
				if (X == x)return value;
			}
			double nX, nValue;
			fs >> nX >> nValue;
			return value + (nValue - value) * (x - X) / (nX - X);
		}
		double U(double x)
		{
			fstream fs(file1);
			if (!fs)throw toalg2Qnk();
			if (x >= -5 || x <= 5)throw toalg2Qnk();
			double X, value;
			fs >> X >> value;
			while (X < x)
			{
				fs >> X >> value;
				if (X == x)return value;
			}
			double nX, nValue;
			fs >> nX >> nValue;
			return value + (nValue - value) * (x - X) / (nX - X);
		}
		double func_regr(double r, double k, double m)
		{
			return 10 * k * r * r - m * r;
		}
		double Qkn(double x, double y) throw (toalg2Qnk, toalg2func)
		{
			return x / U(x) + y * T(y);
		}
		double Qnk(double x, double y)throw (toalg2func)
		{
			try {
				return Qkn(x, y) + x * Qkn(y, x);
			}
			catch (toalg2Qnk)
			{
				return alg2::Qnk(x, y);
			}
			catch (...)
			{
				throw;
			}
		}
		double Rsv(double x, double y, double z)
		{
			if (z > y && z > x)
				return z * Qnk(x, y) - x * y;
			if (x > y && x > z)
				return x * Qnk(z, y) + y * z;
			if (y > x && y > z)
				return y * Qnk(x, z) + x * z;
			return z * Qnk(y, z) - Qnk(z, x);
		}
		double func(double x, double y, double z)
		{
			return Rsv(x, y, z) + 0.5 * Rsv(y, z, x) * Rsv(z, x, y);
		}
		double GetFrom(string text)
		{
			fstream fs(file3);
			if (!fs)
				return 0;
			string s;
			double value;
			fs >> s >> value;
			while (!fs.eof())
			{
				fs >> s >> value;
				if (s == text)
					return value;
			}
			return 0;

		}
		double SText(double x, string text)
		{
			if (x > 0)
				return GetFrom(text) + x;
			if (text == "")
				return GetFrom("tet") + GetFrom("set") - x;
			return GetFrom("get") + GetFrom(text);
		}
		double KText(double x, double y, double z, string text)
		{
			if (z < 0)
				return SText(Min(x, y, x - z, y - z), text);
			return SText(Min(x, y, z - x, z - y), text);
		}
		double Y(double x)throw(MToOne, MToZero)
		{
			if (100 - x * x)
				throw MToZero();
			if (x * sqrt(100 - x * x) < 1)
				throw MToOne();
			return log(x * sqrt(100 - x * x));
		}
		double Ysm(double x, double y) throw(MToOne, MToZero)
		{
			return Y(x) * y + 0.7 * Y(y);
		}
		double Tsm(double x, double y)throw(MToOne, MToZero)
		{
			if (4 * y * y * y * y - x * x < 0)
				throw MtsToZero();
			if (5 * x * x * x * x - 3 * x * x + 2 * sqrt(4 * y * y * y * y - x * x) < 0)
				throw MToZero();
			return log2(5 * x * x * x * x - 3 * x * x + 2 * sqrt(4 * y * y * y * y - x * x)) * Ysm(y, x);
		}
		double Mts(double x, double y)throw(MToOne, MToZero)
		{
			try
			{
				return x * Tsm(x, y) - y * Tsm(x, x);
			}
			catch (MtsToZero)
			{
				return 0;
			}
			catch (...)
			{
				throw;
			}
		}
		double Mtl(double x, double y, double z)throw(MToOne, MToZero)
		{
			return x * Mts(x, y) + z * Mts(z, y);
		}

	}

}
using namespace Task5;
void main()
{
	double x, y, z;
	string text;
	cin >> x >> y >> z >> text;
	double r = alg1::func(x, y, z);
	double k = alg1::KText(x, y, z, text);
	double m;
	try {
		m = alg1::Mtl(x, y, z);
	}
	catch (MToZero)
	{
		m = 0;
	}
	catch (MToOne)
	{
		m = 1;
	}
	cout << alg1::func_regr(r, k, m);
}