
#include "scrawlio.h"

#include <string>
#include <fstream>
#include <exception>
#include <filesystem>

namespace scrawl
{

	Point::Point(double x, double y, double z) : x(x), y(y), z(z)
	{ }

	Color::Color(double red, double green, double blue, double alpha) : red(red), green(green), blue(blue), alpha(alpha)
	{ }

}