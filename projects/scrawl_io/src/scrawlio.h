#ifndef SCRAWL_IO_H_
#define SCRAWL_IO_H_

#include "Container.h"

#include <string>
#include <memory>

namespace scrawl
{
	class Point
	{
	public:

		Point(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z)
		{ }

		double x;
		double y;
		double z;
	};

	class Color
	{
	public:

		Color(double red = 0.0, double green = 0.0, double blue = 0.0, double alpha = 1.0) :
			         red(red), green(green), blue(blue), alpha(alpha)
		{ }

		double red;
		double green;
		double blue;
		double alpha;
	};

	enum class POINTS_DRAW_MODE
	{
		DOTS,
		CIRCLES,
	};

	enum class CHART_DRAW_MODE
	{
		NONE,
		LINE_STRIP,
	};

	struct Font
	{
		Color color;
		int size;
	};

	using PointsContainer = Container<Point>;

	struct  ChartSettings
	{
		//How to draw points 
		Font pointsFont;
		POINTS_DRAW_MODE pointsDrawMode;

		// How to draw line, which connects points
		Font chartFont;
		CHART_DRAW_MODE chartDrawMode;
	};

	class Chart
	{
	public:

		Chart(PointsContainer& points, ChartSettings& settings, const std::string& name = std::string("Chart")) :
			m_points(points), m_settings(settings), m_name(name)
		{ }

		const PointsContainer& GetPoints() const
		{
			return m_points;
		}

		const std::string& Name() const
		{
			return m_name;
		}

	private:

		PointsContainer m_points;
		ChartSettings m_settings;
		std::string m_name;
	};

	using ChartsContainer = Container<Chart>;

	class Scene
	{
	public:

		void AddChart(Chart& chart)
		{
			m_charts.Add(chart);
		}

		const ChartsContainer& GetCharts() const
		{
			return m_charts;
		}

	private:
		ChartsContainer m_charts;
	};

	class Stream
	{
	public:
		virtual Stream& operator << (const Scene& chart) = 0;
		virtual Stream& operator >> (Scene& chart) = 0;
	};

	class StreamProvider
	{
	public:
		virtual std::unique_ptr<Stream> GetStream(const char* file) = 0;
	};

	class JSONStreamProvider : public StreamProvider
	{
	public:
		virtual std::unique_ptr<Stream> GetStream(const char* file) override;
	};

	template<class Provider>
	class SceneStream : public Stream
	{
	public:
		SceneStream(const char* file)
		{
			m_stream = Provider().GetStream(file);
		}

		SceneStream& operator << (const Scene& data) override
		{
			*m_stream << data;
			return *this;
		}

		SceneStream& operator >> (Scene& data) override
		{
			*m_stream >> data;
			return *this;
		}

	private:
		std::unique_ptr<Stream> m_stream;
	};
}

#endif // SCRAWL_IO_H_
