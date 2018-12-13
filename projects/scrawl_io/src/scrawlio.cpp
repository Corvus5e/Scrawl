
#include "scrawlio.h"

#include <string>
#include <fstream>
#include <exception>


namespace scrawl
{
	class ScrawlBinFile
	{
		std::fstream m_stream;

	public:

		ScrawlBinFile(const char* file, open_mode mode)
		{
			unsigned int ios_mode = mode == open_mode::IN ? std::fstream::in : std::fstream::out;

			m_stream.open(file, ios_mode | std::fstream::binary); 
			if (!m_stream.is_open())
				throw std::exception("ERROR: Can't open file to write");
		}

		~ScrawlBinFile()
		{
			m_stream.close();
		}

		ScrawlBinFile& operator << (const Chart& chart)
		{
			m_stream.write(reinterpret_cast<const char*>(&chart.size), sizeof(chart.size));
			m_stream.flush();
			return *this;
		}

		ScrawlBinFile& operator >> (Chart& chart)
		{
			m_stream.read(reinterpret_cast<char*>(&chart.size), sizeof(chart.size));
			return *this;
		}
	};

	BinFileStream::BinFileStream(const char* file, open_mode mode) : m_file(std::make_unique<ScrawlBinFile>(file, mode)) { }
	BinFileStream::~BinFileStream() = default;

	template<>
	BinFileStream& BinFileStream::operator<<(const Chart& data)
	{
		*m_file << data;
		return *this;
	}

	template<>
	BinFileStream& BinFileStream::operator>>(Chart& data)
	{
		*m_file >> data;
		return *this;
	}
}