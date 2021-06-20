// Min trie
// Copyright © 2021 otreblan
//
// min-trie is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// min-trie is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with min-trie.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <algorithm>
#include <cstdlib>
#include <vector>

namespace ada
{

class permutation
{
private:
	std::vector<size_t> v;

public:

	class iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type   = std::ptrdiff_t;
		using value_type        = std::vector<size_t>;
		using pointer           = value_type*;
		using reference         = value_type&;

	private:
		pointer v;

	public:
		iterator(pointer v):
			v(v)
		{};

		iterator():
			v(nullptr)
		{};

		reference operator*() const
		{
			return *v;
		}

		pointer operator->()
		{
			return v;
		}

		iterator& operator++()
		{
			if(v && !std::next_permutation(v->begin(), v->end()))
				v = nullptr;

			return *this;
		}

		friend bool operator==(const iterator& l, const iterator& r)
		{
			return l.v == r.v;
		}

		friend bool operator!=(const iterator& l, const iterator& r)
		{
			return !(l == r);
		}
	};

	const iterator begin();
	const iterator end();

	permutation(size_t h);
};

};
