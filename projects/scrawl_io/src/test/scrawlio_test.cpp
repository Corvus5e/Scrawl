#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "gtest/gtest.h"

#include "scrawlio.h"

using namespace scrawl;

TEST(Container, Basic)
{
	Container<int> c;
	c.Add(1);
	c.Add(2);

	std::vector<int> result;
	std::vector<int> expected = { 1, 2 };

	for (auto& i : c)
	{
		result.push_back(i);
	}

	EXPECT_EQ(result, expected);
}