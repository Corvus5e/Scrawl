#ifndef SCRAWL_IO_H_
#define SCRAWL_IO_H_

namespace scrawl
{
	struct Point
	{
		double x;
		double y;
		double z;
	};

	struct Color
	{
		int red;
		int green;
		int blue;
		float alpha;
	};

	struct PointCollection
	{
		int size;
		Point *points;
		Color color;
	};

	bool WritePointCollection(const PointCollection points, const char* filename);

	bool ReadPointCollection(const char* filename, PointCollection& points);
}

#endif // SCRAWL_IO_H_
