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

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace ada
{

class trie
{
private:
	using node = int;
	static const node root;

	std::set<node> nodes;
	std::unordered_multimap<node, node> edges;

	std::map<std::pair<node, node>, char> f;

	node next_node(node n, char c);
	void add_s(const std::string& s, const std::vector<size_t>& p);

	void ptrie_internal(const std::vector<std::string>& S, const std::vector<size_t>& p);

	static std::vector<size_t> greedy_p(const std::vector<std::string>& S);
public:
	trie();
	trie(const std::vector<std::string>& S, const std::vector<size_t>& p = {});

	static trie greedy(const std::vector<std::string>& S);

	friend std::ostream& operator<<(std::ostream& os, const trie& t);
};

std::ostream& operator<<(std::ostream& os, const trie& t);

};

