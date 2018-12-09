#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "gtest/gtest.h"

#include "scrawlio.h"

using namespace scrawl;

TEST(IO, WriteReadAreEqual)
{
	const char* testFileName = "..\\..\\..\\result\\out\\Debug\\1.bin";

	PointCollection out;
	out.size = 123;

	ASSERT_TRUE(WritePointCollection(out, testFileName));

	PointCollection in;
	ASSERT_TRUE(ReadPointCollection(testFileName, in));

	EXPECT_EQ(out.size, out.size);
}