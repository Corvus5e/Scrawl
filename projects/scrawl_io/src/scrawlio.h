#ifndef SCRAWL_IO_H_
#define SCRAWL_IO_H_

#include <memory>
#include <iterator>

namespace scrawl
{
	class Point
	{
	public:

		Point(double x = 0.0, double y = 0.0, double z = 0.0);

		double x;
		double y;
		double z;
	};

	class Color
	{
	public:

		Color(double red = 0.0, double green = 0.0, double blue = 0.0, double alpha = 1.0);

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

	template <typename T>
	class Iterator : std::iterator<std::input_iterator_tag, T>
	{
	public:
		virtual bool operator!=(Iterator const& rhs) = 0;
		virtual bool operator==(Iterator const& rhs) = 0;
		virtual typename Iterator::reference operator*() const = 0;
		virtual typename Iterator::pointer operator->() = 0;
		virtual Iterator& operator++() = 0;
		virtual Iterator& operator++(int) = 0;
	};

	template <typename T>
	class Container
	{
	public:

		using iterator = Iterator<T>;

		virtual size_t Size() const = 0;

		virtual void Add(T&) = 0;

		virtual iterator Begin() = 0;

		virtual iterator End() = 0;
	};

	class Chart : public Container<Point>
	{
	public:

		// TODO: Add constructor to init all

		// Container
		size_t Size() const override;

		void Add(Point& point) override;

		Container<Point>::iterator Begin() override;

		Container<Point>::iterator End() override;

		// Chart
		void SetPointFont(const Font& font);

		void SetChartFont(const Font& font);

		void SetPointDrawMode(POINTS_DRAW_MODE mode);

		void SetChartDrawMode(CHART_DRAW_MODE mode);

	protected:

		std::unique_ptr<Container<Point>> m_points;

		Font m_pointFont;
		Font m_chartFont;
		POINTS_DRAW_MODE m_pointsDrawMode;
		CHART_DRAW_MODE m_chartDrawMode;
	};

	class Stream
	{
	public:
		virtual Stream& operator << (const Chart& chart) = 0;
		virtual Stream& operator >> (Chart& chart) = 0;
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
	class SceneStream
	{
	public:
		SceneStream(const char* file)
		{
			m_stream = Provider().GetStream(file);
		}

		template<class Data>
		SceneStream& operator << (const Data& data)
		{
			m_stream << data;
			return *this;
		}

		template<class Data>
		SceneStream& operator >> (Data& data)
		{
			m_stream >> data;
			return *this;
		}

	private:
		std::unique_ptr<Stream> m_stream;
	};
}

#endif // SCRAWL_IO_H_
