#ifndef SCRAWL_IO_H_
#define SCRAWL_IO_H_

#include <memory>

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
		int size;
		Point *points;
		Color color;
	};


	enum class open_mode { IN, OUT };

	class ScrawlBinFile;

	class BinFileStream
	{
	public: 

		BinFileStream(const char* file, open_mode mode);

		~BinFileStream();

		template<class Data>
		BinFileStream& operator << (const Data& data);

		template<class Data>
		BinFileStream& operator >> (Data& data);

	private:
		std::unique_ptr<ScrawlBinFile> m_file;
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
