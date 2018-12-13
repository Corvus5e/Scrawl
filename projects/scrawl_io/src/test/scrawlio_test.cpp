#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "gtest/gtest.h"

#include "scrawlio.h"

using namespace scrawl;

TEST(IO, WriteReadAreEqual)
{
	const char* testFileName = "..\\..\\..\\result\\out\\Debug\\1.bin";

	Chart out;
	out.size = 123;
	{
		ScrawlStream<FileStream> scrawlStream(testFileName);
		scrawlStream << out;
	}

	Chart in;
	{
		ScrawlStream<FileStream> scrawlStream(testFileName);
		scrawlStream >> in;
	}

	EXPECT_EQ(in.size, out.size);
	
}