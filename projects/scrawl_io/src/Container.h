#ifndef SCRAWL_CONTAINER_H_
#define SCRAWL_CONTAINER_H_

#include <vector>

namespace scrawl
{
	template <typename T>
	class Container
	{
	public:

		using UnderlyingContainer = std::vector<T>;
		using iterator = typename UnderlyingContainer::iterator;

		size_t Size() const
		{
			return m_data.size();
		}


		void Add(const T& element)
		{
			m_data.push_back(element);
		}

		iterator begin()
		{
			return m_data.begin();
		}

		iterator end()
		{
			return m_data.end();
		}

	private:

		UnderlyingContainer m_data;
	};
}

#endif