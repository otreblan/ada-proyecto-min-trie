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

#include <numeric>
#include <iostream>

#include "permutation.hpp"

const ada::permutation::iterator ada::permutation::begin()
{
	return {&v};
}

const ada::permutation::iterator ada::permutation::end()
{
	return {nullptr};
}

ada::permutation::permutation(size_t h):
	v(h)
{
	std::iota(v.begin(), v.end(), 0);
}
