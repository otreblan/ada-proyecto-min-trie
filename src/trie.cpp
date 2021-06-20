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
#include <cassert>

#include "trie.hpp"

const ada::trie::node ada::trie::root = 0;

ada::trie::node ada::trie::next_node(node n, char c)
{
	auto range = edges.equal_range(n);
	for(auto it = range.first; it != range.second; it++)
	{
		if(f.find(*it) != f.end())
			return it->second;
	}

	// New node
	node next_n = nodes.size();

	nodes.insert(next_n);
	edges.emplace(n, next_n);
	f[{n, next_n}] = c;

	return next_n;
}

void ada::trie::add_s(const std::string& s, const std::vector<size_t>& p)
{
	node n = root;

	if(nodes.empty())
		nodes.insert(root);

	for(char i: p)
		n = next_node(n, s.at(i));
}

void ada::trie::ptrie_internal(const std::vector<std::string>& S, const std::vector<size_t>& p)
{
	assert(S.front().size() == p.size());

	for(const auto& s: S)
		add_s(s, p);
}

ada::trie::trie(){};

ada::trie::trie(const std::vector<std::string>& S, const std::vector<size_t>& p)
{
	if(S.empty())
		return;

	if(p.empty())
	{
		std::vector<size_t> p2(S.front().size());
		std::iota(p2.begin(), p2.end(), 0);
		ptrie_internal(S, p2);
	}
	else
	{
		ptrie_internal(S, p);
	}
}
