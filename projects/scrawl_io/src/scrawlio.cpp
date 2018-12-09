
#include "scrawlio.h"

#include <fstream>

using namespace scrawl;

bool scrawl::WritePointCollection(const PointCollection points, const char* filename)
{
	std::ofstream os;
	os.open(filename, std::ofstream::out | std::ofstream::binary);

	if (os.is_open())
	{
		os.write(reinterpret_cast<const char*>(&points.size), sizeof(points.size));
		os.close();

		return true;
	}

	return false;
}


bool scrawl::ReadPointCollection(const char* filename, PointCollection& points)
{
	std::ifstream is;
	is.open(filename, std::ofstream::in | std::ofstream::binary);

	if (is.is_open())
	{
		is.read(reinterpret_cast<char*>(&points.size), sizeof(points.size));
		is.close();

		return true;
	}

	return false;
}