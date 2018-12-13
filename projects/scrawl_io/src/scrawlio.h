#ifndef SCRAWL_IO_H_
#define SCRAWL_IO_H_

#include <memory>
#include <vector>

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

	struct Chart
	{
		int size; // wiil be removed
		std::vector<Point> points;
		Color color;
	};


	class ScrawlFileImpl;

	class FileStream
	{
	public: 

		FileStream(const char* file);

		~FileStream();

		template<class Data>
		FileStream& operator << (const Data& data);

		template<class Data>
		FileStream& operator >> (Data& data);

	private:
		std::unique_ptr<ScrawlFileImpl> m_file;
	};

	template<class Writer>
	class ScrawlStream
	{
	public:
		template<typename... Args>
		ScrawlStream(Args... args) : m_writer(args...)
		{ }

		template<class Data>
		ScrawlStream& operator << (const Data& data)
		{
			m_writer << data;
			return *this;
		}

		template<class Data>
		ScrawlStream& operator >> (Data& data)
		{
			m_writer >> data;
			return *this;
		}

	private:
		Writer m_writer;
	};
}

#endif // SCRAWL_IO_H_
