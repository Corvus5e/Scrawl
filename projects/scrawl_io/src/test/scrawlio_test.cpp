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

TEST(JSONStream, Basic)
{
	PointsContainer pc;
	pc.Add({1, 1, 1});
	pc.Add({ 2, 2, 2 });
	pc.Add({ 3, 3, 3 });

	ChartSettings cs;
	Chart a(pc, cs, "A");
	Chart b(pc, cs, "B");

	Scene outScene;
	outScene.AddChart(a);
	outScene.AddChart(b);


	SceneStream<JSONStreamProvider> ss("1.txt");
	ss << outScene;

	Scene inScene;
	ss >> inScene;

	//TODO: How to compare scenes ? operator == ?
}