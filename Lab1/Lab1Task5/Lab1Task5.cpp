#include <iostream> 
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;
namespace exceptions
{
	class recount {

	};
	class toalg2 {
	public:
		double zValue;
		toalg2(double z)
		{
			zValue = z;
		}
	};
	class toalg3 {

	};
	class toalg4 {

	};
}
using namespace exceptions;
namespace Task5 {
	string file1 = "dat1.dat";
	string file2 = "dat2.dat";
	string file3 = "dat3.dat";
	namespace alg2
	{
		double Qnr(double x, double y)
		{
			if (y == 0)return 1;
			if (x > y)
				return x * x * (10 * y * y - x / 2);
			if (3 * x > y)
				return x * x * x * x * y;
			return y * y * y * y * x;
		}
		double Qnk(double x, double y)
		{
			return 12 * Qnr(2.5 * x, y) - 3 * Qnr(x, 1.5 * y);
		}
		double Rnk(double x, double y, double z)
		{
			return 1.15 * x * Qnk(x, y) + 0.95 * y * Qnk(y, x) + 0.9 * z * Qnk(z, x);
		}
	}

	namespace alg3
	{
		double T(double x)
		{
			return atan(acos(sin(2 * x)));
		}
		double U(double x)
		{
			return atan(acos(sin(3 * x)));
		}
		double Wnr(double x, double y)
		{
			if (x > y)
				return T(x) - 0.9 * U(x) * U(y);
			return 0.9 * T(x) * T(y) - U(x);
		}
		double Wnk(double x, double y)
		{
			return 10 * Wnr(2.5 * x, y) - 4 * Wnr(x, 2.5 * y);
		}
	}
	namespace alg4 {
		double T(double x)
		{
			fstream fs(file2);
			if (!fs)return 0;
			if (x >= -10 || x <= 10)throw toalg4();
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
			if (!fs)return 0;
			if (x >= -5 || x <= 5)throw toalg4();
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
		double Wnr(double x, double y)
		{
			if (x > y)
				return 0.9 * T(x) - U(x) * U(y);
			return T(x) * T(y) - 0.9 * U(x);
		}
		double Wnk(double x, double y)
		{
			return 10 * Wnr(x, y) - 3 * Wnr(x, y);
		}
		double Gnk(double x, double y, double z)
		{
			if (x * x + y * y + z * z >= 0.001)
				return
				x * Wnk(x / sqrt(x * x + y * y + z * z), y / sqrt(x * x + y * y + z * z)) +
				y * Wnk(y / sqrt(x * x + y * y + z * z), x / sqrt(x * x + y * y + z * z)) +
				z * Wnk(z / sqrt(x * x + y * y + z * z), y / sqrt(x * x + y * y + z * z));
			return 0;
		}
	}
	namespace alg1
	{
		double T(double x)
		{
			fstream fs(file2);
			if (!fs)throw toalg3();
			if (x >= -10 || x <= 10)throw toalg4();
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
			if (!fs)throw toalg3();
			if (x >= -5 || x <= 5)throw toalg4();
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
		double Wnr(double x, double y) throw (toalg3, toalg4)
		{
			if (x > y)
				return T(x) - U(x) * U(y);
			return T(x) * T(y) - U(x);
		}
		double Wnk(double x, double y) throw (toalg4)
		{
			try {
				return 10.5 * Wnr(2 * x, y) - 3.75 * Wnr(x, 2 * y);
			}
			catch (toalg3) {
				return alg3::Wnk(x, y);
			}
			catch (...)
			{
				throw;
			}
		}
		double Gnk(double x, double y, double z)
		{
			try {
				return x * Wnk(x, y) + y * Wnk(y, x) + z * Wnk(z, x);
			}
			catch (toalg4)
			{
				return alg4::Gnk(x, y, z);
			}
		}
		double Gold(double x, double y, double z)
		{
			return x * Gnk(x, y, z) + Gnk(y, z, x) * Gnk(z, x, y);
		}
		double Qnr(double x, double y)
		{
			if (y == 0)
				return 1;
			if (x > y && 10 * y * y * y * y - x >= 0)
				return x * x * sqrt(10 * y * y * y * y - x);
			if (x <= y && 3 * x > y && 10 * x * x * x * x - y >= 0)
				return x * x * x * log(10 * x * x * x * x - y);
			if (x <= y && 3 * x <= y && y * y * y * y - 2 * x >= 0)
				return y * y * sqrt(y * y * y * y - 2 * x);
			if (10 * y * y - x < 0)
				throw toalg2(1.25);
			if (y * y - 2 * x < 0)
				throw toalg2(1.5);
			if (10 * x * x - y < 0)
				throw recount();
		}
		double Qnk(double x, double y) throw(toalg2)
		{
			try
			{
				return 10.5 * Qnr(2 * x, y) - 3.75 * Qnr(x, 2 * y);
			}
			catch (recount)
			{
				return Qnk(x, 0);
			}
			catch (...)
			{
				throw;
			}
		}
		double Rnk(double x, double y, double z)
		{
			return x * Qnk(x, y) + y * Qnk(y, x) + z * Qnk(z, x);
		}
		double fun(double x, double y, double z)
		{
			return x * Rnk(x, y, z) + Rnk(y, z, x) * Rnk(z, x, y);
		}
		double Tfun(double u, double v, string text)
		{
			fstream fs(file3);
			double r = 0;
			if (!fs) r = 0;
			else
			{
				string s;
				double value;
				bool fl = false;
				while (!fs.eof())
				{
					fs >> s >> value;
					if (s == text) {
						r = value;
						fl = true;
						break;
					}
				}
				if (!fl)
					r = 1;
			}
			return u * u + v * v - r * (u + v) + r * r;
		}
		double func(double u, double v, string text)
		{
			if (u <= 0.5 && u >= -0.5)
				return Tfun(0, v, text);
			if (u < v)
				return Tfun(u, v, text);
			return Tfun(u, 0, text) - Tfun(0, v, "set");
		}
	}

}
using namespace Task5;
void main()
{
	double x, y, z;
	string text;
	cin >> x >> y >> z >> text;
	double u = alg1::fun(x, y, z);
	double v = alg1::Gold(x, y, z);
	cout << alg1::func(u, v, text);
}