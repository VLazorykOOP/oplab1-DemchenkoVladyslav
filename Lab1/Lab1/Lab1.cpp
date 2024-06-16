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
	class NoFileException
	{
		string Message = "No file found: ";
	public:
		NoFileException(string filename)
		{
			Message = "No file found: " + filename;
		}
		string getMessage()
		{
			return Message;
		}
	};
	class WrongParameterException
	{
		string
			Message = "Wrong parameters";
	public:
		WrongParameterException()
		{
		}
		string getMessage()
		{
			return Message;
		}
	};
}
namespace alg1
{
	string file1 = "dat_X_1_1.dat";
	string file2 = "dat_X_00_1.dat";
	string file3 = "dat_X_1_00.dat";
	double T(double x, string filename)throw (exceptions::NoFileException)
	{
		try
		{
			ifstream fs(filename);
			if (!fs) throw exceptions::NoFileException(filename);
			if (filename == file1 || filename == file2)
			{
				float Xp, Tp, Up;
				fs >> Xp >> Tp >> Up;
				if (x == Xp)
				{
					return Tp;
				}
				float Xc, Tc, Uc;
				fs >> Xc >> Tc >> Uc;
				while (Xc < x)
				{
					Xp = Xc;
					Tp = Tc;
					Up = Uc;
					fs >> Xc >> Tc >> Uc;
				}
				if (x == Xc)
				{
					fs.close();
					return Tc;
				}
				if (x > Xp && x < Xc)
				{
					fs.close();
					return T(Xp, filename) + (T(Xc, filename) - T(Xp, filename)) * (x - Xp) / (Xc - Xp);
				}
				fs.close();
			}
			else
			{
				float Xp, Tp, Up;
				fs >> Xp >> Tp >> Up;
				if (x == Xp)
				{
					return Tp;
				}
				float Xc, Tc, Uc;
				fs >> Xc >> Tc >> Uc;
				while (Xc > x)
				{
					Xp = Xc;
					Tp = Tc;
					Up = Uc;
					fs >> Xc >> Tc >> Uc;
				}
				if (x == Xc)
				{
					fs.close();
					return Tc;
				}
				if (x < Xp && x > Xc)
				{
					fs.close();
					return T(Xp, filename) + (T(Xc, filename) - T(Xp, filename)) * (x - Xp) / (Xc - Xp);
				}
				fs.close();
			}
		}
		catch (exceptions::NoFileException e) {
			throw;
			//змінити алгоритм на 3
		}
	}
	double T(double x)throw (exceptions::NoFileException)
	{
		try
		{
			if (abs(x) <= 1)
			{
				return T(x, file1);
			}
			if (x < -1)
			{
				return T(1 / x, file2);
			}
			if (x > 1)
			{
				return T(-1 / x, file3);
			}
		}
		catch (exceptions::NoFileException ek)
		{
			throw;
			//перехід на 3 алгоритм
		}
	}
	double U(double x, string filename)
	{
		try
		{
			ifstream fs(filename);
			if (!fs) throw exceptions::NoFileException(filename);
			if (filename == file1 || filename == file2)
			{
				double Xp, Tp, Up;
				fs >> Xp >> Tp >> Up;
				if (x == Xp)
				{
					return Up;
				}
				double Xc, Tc, Uc;
				fs >> Xc >> Tc >> Uc;
				while (Xc < x)
				{
					Xp = Xc;
					Tp = Tc;
					Up = Uc;
					fs >> Xc >> Tc >> Uc;
				}
				if (x == Xc)
				{
					fs.close();
					return Uc;
				}
				if (x > Xp && x < Xc)
				{
					fs.close();
					return U(Xp, filename) + (U(Xc, filename) - U(Xp, filename)) * (x - Xp) / (Xc - Xp);
				}
				fs.close();
			}
			else
			{
				float Xp, Tp, Up;
				fs >> Xp >> Tp >> Up;
				if (x == Xp)
				{
					return Up;
				}
				float Xc, Tc, Uc;
				fs >> Xc >> Tc >> Uc;
				while (Xc > x)
				{
					Xp = Xc;
					Tp = Tc;
					Up = Uc;
					fs >> Xc >> Tc >> Uc;
				}
				if (x == Xc)
				{
					fs.close();
					return Uc;
				}
				if (x < Xp && x > Xc)
				{
					fs.close();
					return U(Xp, filename) + (U(Xc, filename) - U(Xp, filename)) * (x - Xp) / (Xc - Xp);
				}
				fs.close();
			}
		}
		catch (exceptions::NoFileException e) {
			throw;
			//змінити алгоритм на 3
		}
	}
	double U(double x)
	{
		if (abs(x) <= 1)
		{
			return U(x, file1);
		}
		if (x < -1)
		{
			return U(1 / x, file2);
		}
		if (x > 1)
		{
			return U(1 / x, file3);
		}
	}
	double srz(double x, double y, double z) throw (exceptions::NoFileException)
	{
		if (x > y)
			return T(x) + U(z) - T(y);
		return T(y) + U(y) - U(z);
	}
	double glr(double x, double y) throw (exceptions::WrongParameterException)
	{
		if (abs(x) < 1) return x;
		if (abs(x) >= 1 && abs(y) < 1)return y;
		if (sqrt(x * x + y * y - 4) < 0.1) throw exceptions::WrongParameterException();
		return y / sqrt(x * x + y * y - 4);
	}
	double gold(double x, double y) throw (exceptions::NoFileException)
	{
		if (y != 0 && x > y)
			return x / y;
		if (x != 0 && x < y)
			return y / x;
		throw exceptions::WrongParameterException();
	}
	double grs(double x, double y) throw (exceptions::NoFileException)
	{
		return 0.1389 * srz(x + y, gold(x, y), glr(x, x * y)) + 1.8389 * srz(x - y, gold(y, x / 5), glr(5 * x, x * y))
			+ 0, 83 * srz(x - 0.9, glr(y, x / 5), gold(5 * y, y));
	}
	double fun(double x, double y, double z) throw (exceptions::NoFileException)
	{
		return x * x * grs(y, z) + y * y * grs(x, z) + 0.33 * x * y * grs(x, z);
	}
}
namespace alg2 {
	double glr(double x, double y) throw (exceptions::WrongParameterException)
	{
		if (abs(x) < 1) return x;
		return y;
	}
	double gold(double x, double y) throw (exceptions::NoFileException)
	{
		if (x > y && abs(y) > 0.1)
		{
			return x / y;
		}if (x <= y && abs(x) > 0.1)
		{
			return y / x;
		}if (x < y && abs(x) > 0.1)
		{
			return 0.15;
		}
		return 0.1;
	}
	double grs(double x, double y) throw (exceptions::NoFileException)
	{
		return 0.14 * alg1::srz(x + y, gold(x, y), glr(x, x * y)) + 1.83 * alg1::srz(x - y, gold(y, x / 5), glr(4 * x, x * y)) + 0.83 * alg1::srz(x, glr(y, x / 4), gold(4 * y, y));
	}
	double fun(double x, double y, double z) throw (exceptions::NoFileException)
	{
		return x * grs(x, y) + y * grs(y, z) + z * grs(z, x);
	}
}
namespace alg3
{
	double fun(double x, double y, double z)
	{
		return 1.3498 * z + 2.2362 * y - 2.348 * x * y;
	}
}
int main()
{
	double x, y, z;
	cin >> x >> y >> z;
	try {
		cout << alg1::fun(x, y, z) << endl;
	}
	catch (exceptions::NoFileException e) {
		cout << "Algorithm changed to 3" << endl;
		cout << alg3::fun(x, y, z);
	}
	catch (exceptions::WrongParameterException e) {
		cout << "Algorithm changed to 2" << endl;
		cout << alg2::fun(x, y, z);
	}
}