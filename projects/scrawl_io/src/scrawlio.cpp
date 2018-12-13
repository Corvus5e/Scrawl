
#include "scrawlio.h"

#include <string>
#include <fstream>
#include <exception>
#include <filesystem>

namespace scrawl
{
	class ScrawlFileImpl
	{
		std::fstream m_stream;

	public:

		ScrawlFileImpl(const char* file)
		{
			unsigned int open_mode = std::fstream::in | std::fstream::out | std::fstream::binary;

			if (!std::filesystem::exists(file))
				open_mode |= std::fstream::trunc;

			m_stream.open(file, open_mode);
			if (!m_stream.is_open())
				throw std::exception("ERROR: Can't open file to write");
		}

		~ScrawlFileImpl()
		{
			m_stream.close();
		}

		ScrawlFileImpl& operator << (const Chart& chart)
		{
			m_stream.write(reinterpret_cast<const char*>(&chart.size), sizeof(chart.size));

			return *this;
		}

		ScrawlFileImpl& operator >> (Chart& chart)
		{
			m_stream.read(reinterpret_cast<char*>(&chart.size), sizeof(chart.size));
			return *this;
		}
	};

	FileStream::FileStream(const char* file) : m_file(std::make_unique<ScrawlFileImpl>(file)) { }
	FileStream::~FileStream() = default;

	template<>
	FileStream& FileStream::operator<<(const Chart& data) { *m_file << data; return *this; }
	template<>
	FileStream& FileStream::operator>>(Chart& data) { *m_file >> data; return *this; }
}