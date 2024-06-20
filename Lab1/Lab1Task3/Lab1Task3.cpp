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
	class toalg2 {

	};
	class toalg3 {

	};
	class toalg4 {

	};
	class toalg5 {

	};
}
namespace Task2 {
	namespace alg1 {
		double srz(double x, double y, double z);
	}
	namespace alg2 {
		double srs(double x, double y, double z)
		{
			if (z > y)
				return alg1::srz(x, y, z) + 1.44 * y * z;
			return y + 1.44 * alg1::srz(z, x, y);
		}
		double qrz(double x, double y)
		{
			if (y > -1 && y < 1)
				return x * srs(x, y, x);
			return y * srs(y, x, y);
		}
		double rrz(double x, double y, double z)
		{
			if (x > y)
				return x * y * qrz(y, z);
			return x * z * qrz(x, y);
		}
	}
	namespace alg3
	{
		double srs(double x, double y, double z)
		{
			if (z > y)
				return alg1::srz(x, y, z) + y * x;
			return alg1::srz(z, x, y) + y * z;
		}
		double qrz(double x, double y)
		{
			if (x > -1 && x < 1)
				return x * srs(x, y, x);
			return y * srs(y, x, y);
		}
		double rrz(double x, double y, double z)
		{
			if (x > y)
				return x * y * qrz(y, z);
			return y * z * qrz(x, y);
		}
	}

	namespace alg4 {
		double srs(double x, double y, double z)
		{
			if (z > y)
				return alg1::srz(x, y, z) + y * x;
			return y * z + alg1::srz(z, x, y);
		}
		double qrz(double x, double y)
		{
			if (x > -1 && x < 1)
				return x * srs(x, y, x);
			return x * srs(y, x, y);
		}
		double rrz(double x, double y, double z)
		{
			if (x > y)
				return y * qrz(y, z);
			return z * qrz(x, y);
		}
		double krn(double x, double y, double z)
		{
			return 83.1389 * rrz(x, y, z) + 4.838 * rrz(x, z, y);
		}
	}
	namespace alg1
	{
		string file1 = "dat_X_1_1.dat";
		string file2 = "dat_X_00_1.dat";
		string file3 = "dat_X_1_00.dat";
		double T(double x, string filename)throw (exceptions::toalg5)
		{
			try
			{
				ifstream fs(filename);
				if (!fs) throw exceptions::toalg5();
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
			catch (exceptions::toalg5) {
				throw;
			}
		}
		double T(double x)throw (exceptions::toalg5)
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
		double U(double x, string filename)
		{
			try
			{
				ifstream fs(filename);
				if (!fs) throw exceptions::toalg5();
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
			catch (exceptions::toalg5) {
				throw;
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
		double srz(double x, double y, double z) throw (exceptions::toalg5)
		{
			if (x > y)
				return T(x) + U(z) - T(y);
			return T(y) + U(y) - U(z);
		}
		double srs(double x, double y, double z) throw (exceptions::toalg2, exceptions::toalg3, exceptions::toalg5)
		{
			if (z > y && z * z + x * y > 0)
				return srz(x, y, z) + y * sqrt(z * z + x * y);
			if (z <= y && x * x + z * y > 0)
				return y + srz(x, y, z) * sqrt(x * x + z * y);
			if (z * z + x * y <= 0)
				throw exceptions::toalg2();
			throw exceptions::toalg3();
		}
		double srs1(double x, double y, double z) throw (exceptions::toalg2, exceptions::toalg4, exceptions::toalg4)
		{
			if (z > y && z * z + x * y > 0)
				return srz(x, y, z) + y * sqrt(z * z + x * y);
			if (z <= y && x * x + z * y > 0)
				return y + srz(x, y, z) * sqrt(x * x + z * y);
			if (z * z + x * y <= 0)
				throw exceptions::toalg2();
			throw exceptions::toalg4();
		}
		double qrz(double x, double y)throw (exceptions::toalg2, exceptions::toalg3, exceptions::toalg4, exceptions::toalg5)
		{
			if (x > -1 && x < 1)
				return x * srs(x, y, x);
			return y * srs1(y, x, y);
		}
		double rrz(double x, double y, double z)throw (exceptions::toalg4, exceptions::toalg5)
		{
			try
			{
				if (x > y)
					return x * z * qrz(y, z) - x;
				return y * x * qrz(x, y) + y;
			}
			catch (exceptions::toalg2)
			{
				return alg2::rrz(x, y, z);
			}
			catch (exceptions::toalg3)
			{
				return alg3::rrz(x, y, z);
			}
			catch (exceptions::toalg4)
			{
				throw;
			}
			catch (exceptions::toalg5)
			{
				throw;
			}
		}
		double krn(double x, double y, double z) throw(exceptions::toalg5)
		{
			try
			{
				return 73 * 1389 * rrz(x, y, y) + 14.83 * rrz(x - y, z, y);
			}
			catch (exceptions::toalg4)
			{
				return alg4::krn(x, y, z);
			}
			catch (exceptions::toalg5)
			{
				throw;
			}
		}
		double fun(double x, double y, double z) throw (exceptions::toalg4)
		{
			return  x * krn(x, y, z) + y * krn(x, z, y) - z * krn(x, z, y);
		}
	}

	namespace alg5 {
		double fun(double x, double y, double z)
		{
			return 4.349 * x * z + 23.23 * y - 2.348 * x * y * z;
		}
	}

}
using namespace Task2;
void main()
{
	double x, y, z;
	cin >> x >> y >> z;
	try {
		cout << Task2::alg1::fun(x, y, z) << endl;
	}
	catch (exceptions::toalg5) {
		cout << "Algorithm changed to 5" << endl;
		cout << Task2::alg5::fun(x, y, z);
	}

}