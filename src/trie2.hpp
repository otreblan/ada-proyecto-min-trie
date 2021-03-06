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

#include <cstdlib>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <climits>

namespace ada
{

class trie2
{
private:
	size_t nodes_n = 1;
	size_t m;
	std::set<char> sigma;
	std::unordered_map<char, size_t> sigma_order;
	std::vector<ssize_t> matrix;

	static std::set<char> get_sigma(const std::vector<std::string>& S);
	static std::unordered_map<char, size_t> get_sigma_order(const std::set<char>& s);
	static size_t get_m(const std::vector<std::string>& S);

	void add_string(std::string_view str, const std::vector<size_t>& p);

	static std::vector<size_t> greedy_p(const std::vector<std::string>& S);

	static int dp_rec_p(const std::vector<std::string>& S, int i, int j);
	static int dp_memo_p(const std::vector<std::string>& S, int i, int j, std::vector<std::vector<int>>& M);
	static std::set<int> get_k(const std::vector<std::string> &S, int i, int j);
	static std::set<int> get_r(const std::vector<std::string> &S, int i, int j);
	static std::vector<std::pair<int,int>> get_c(const std::vector<std::string> &S, int i, int j, int r);
public:

	trie2(const std::vector<std::string>& S, const std::vector<size_t>& p);
	size_t at(ssize_t node, char c) const;
	friend std::ostream& operator<<(std::ostream& os, const trie2& t);

	void print_edges(std::ostream& os, size_t node) const;
	static trie2 greedy(const std::vector<std::string>& S);
	static int dp_rec(const std::vector<std::string>& S);
	static int dp_memo(const std::vector<std::string>& S);
	static int dp(const std::vector<std::string>& S);
};

std::ostream& operator<<(std::ostream& os, const trie2& t);

};

