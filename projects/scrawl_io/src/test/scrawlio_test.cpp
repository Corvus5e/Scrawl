#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "gtest/gtest.h"

#include "scrawlio.h"

using namespace scrawl;

TEST(IO, WriteReadAreEqual)
{
	const char* testFileName = "..\\..\\..\\result\\out\\Debug\\2.bin";

	Chart out;
	out.size = 123;
	{
		ScrawlStream<BinFileStream> scrawlStream(testFileName, open_mode::OUT);
		scrawlStream << out;
	}

	Chart in;
	{
		ScrawlStream<BinFileStream> scrawlStream(testFileName, open_mode::IN);
		scrawlStream >> in;
	}

	EXPECT_EQ(in.size, out.size);
	
}