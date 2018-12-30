
#include "scrawlio.h"

#include "nlohmann/json.hpp"
#include <fstream>
#include <iomanip>
#include <exception>
#include <iostream>

using namespace scrawl;
using json = nlohmann::json;

namespace
{
	const std::string cChartNameKey = "ChartName";
	const std::string cChartsKey = "Charts";
	const std::string cPointsKey = "Points";

	class JSONStreamImpl : public Stream
	{
	public:

		JSONStreamImpl(const char* file) : m_file(file)
		{ }

		Stream& operator << (const Scene& scene) override
		{
			//TODO: Opening file each time: probably need to remove "Stream" from class name
			// as mostly there will be 1 scene and 1 write/read
			std::ofstream os(m_file);
			if (!os.is_open())
				throw std::exception("Filed to open file");

			json sceneJSON; 

			ChartsContainer charts = scene.GetCharts();

			for (auto& chart : charts)
			{
				json chartJSON;
				std::string chartName = chart.Name();
				chartJSON[cChartNameKey] = chart.Name();

				PointsContainer points = chart.GetPoints();

				for (auto& point : points)
				{
					chartJSON[cPointsKey].push_back({point.x, point.y, point.z});
				}

				sceneJSON[cChartsKey].push_back(chartJSON);
			}

			os << std::setw(4) << sceneJSON << std::endl;
			os.close();

			return *this;
		}

		Stream& operator >> (Scene& scene) override
		{
			std::ifstream is(m_file);
			if (!is.is_open())
				throw std::exception("Filed to open file");

			json sceneJSON;
			is >> sceneJSON;

			for (auto chartJSON : sceneJSON[cChartsKey])
			{
				PointsContainer points;
				ChartSettings chartSettings;
				
				for (auto pointJSON : chartJSON[cPointsKey])
				{
					Point point;
					auto pointIter = pointJSON.begin();
					point.x = pointIter->get<double>();
					point.y = (++pointIter)->get<double>();
					point.z = (++pointIter)->get<double>();

					points.Add(point);
				}

				std::string chartName = chartJSON[cChartNameKey].get<std::string>();

				Chart chart(points, chartSettings, chartName);
				scene.AddChart(chart);
			}

			return *this;
		}

	private:
		std::string m_file;
	};
}

std::unique_ptr<Stream> JSONStreamProvider::GetStream(const char* file)
{
	return std::make_unique<JSONStreamImpl>(file);
}
