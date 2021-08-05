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

#include <algorithm>
#include <iostream>
#include <numeric>

#include "trie2.hpp"

size_t ada::trie2::get_m(const std::vector<std::string>& S)
{
	if(S.empty())
		return 0;

	return S.front().size();
}

std::set<char> ada::trie2::get_sigma(const std::vector<std::string>& S)
{
	std::set<char> s;
	for(const auto& str: S)
	{
		s.insert(str.begin(), str.end());
	}
	return s;
}

std::unordered_map<char, size_t> ada::trie2::get_sigma_order(const std::set<char>& s)
{
	std::vector<char> sv(s.begin(), s.end());

	std::unordered_map<char, size_t> m;
	int order = 0;
	for(char c: sv)
		m[c] = order++;

	return m;
}

void ada::trie2::add_string(std::string_view str, const std::vector<size_t>& p)
{
	size_t nodo_i = at(0, str.at(p.at(0)));
	if(matrix.at(nodo_i) == -1)
		matrix.at(nodo_i) = nodes_n++;

	for(size_t i = 1; i < p.size(); i++)
	{
		char c = str.at(p.at(i));

		nodo_i = at(matrix.at(nodo_i), c);
		if(matrix.at(nodo_i) == -1)
			matrix.at(nodo_i) = nodes_n++;
	}
}

ada::trie2::trie2(const std::vector<std::string>& S, const std::vector<size_t>& p):
	m(get_m(S)),
	sigma(get_sigma(S)),
	sigma_order(get_sigma_order(sigma)),
	matrix(sigma_order.size()*m*(1+S.size()), -1)
{
	for(const auto& s: S)
		add_string(s, p);
}

size_t ada::trie2::at(ssize_t node, char c) const
{
	return node*sigma_order.size()+sigma_order.at(c);
}

void ada::trie2::print_edges(std::ostream& os, size_t node) const
{
	for(char c: sigma)
	{
		size_t i = at(node, c);

		if(matrix.at(i) != -1)
		{
			os
				<< '\t'
				<< node
				<< " -> "
				<< matrix.at(i)
				<< " [label=\""
				<< c
				<< "\"];\n"
			;
			print_edges(os, matrix.at(i));
		}
	}
}

std::ostream& ada::operator<<(std::ostream& os, const trie2& t)
{
	os <<
		"digraph D {\n"
		"\tforcelabels=true;\n"
		"\tlabelloc=\"t\";\n"
		"\tlabeljust=\"l\";\n"
		"\tlabel=\"# aristas: " << t.nodes_n-1 << "\";\n"
	;

	os << "\n\t//Nodes\n";
	for(size_t n = 0; n < t.nodes_n; n++)
	{
		os << '\t' << n << " [label=\"\"];\n";
	}

	os << "\n\t//Edges\n";
	t.print_edges(os, 0);

	os << "}\n";
	return os;
}

std::vector<size_t> ada::trie2::greedy_p(const std::vector<std::string>& S)
{
	if(S.empty())
		return {};

	auto h = [&](size_t i)
	{
		std::set<char> sigma;
		for(const auto& s: S)
			sigma.insert(s.at(i));

		return sigma.size();
	};

	size_t m = S.front().size();

	std::vector<size_t> p(m);
	std::iota(p.begin(), p.end(), 0);

	// Los índices con menos caracteres al comienzo.
	std::sort(p.begin(), p.end(),
		[&](size_t l, size_t r)
		{
			return h(l) < h(r);
		}
	);

	return p;
}

ada::trie2 ada::trie2::greedy(const std::vector<std::string>& S)
{
	return trie2(S, greedy_p(S));
}

int ada::trie2::dp_rec_p(const std::vector<std::string> &S, int i, int j) {
    if (i == j)
        return 0;
    auto R = get_r(S, i, j);
    int min = INT_MAX;
    for (const auto& r : R) {
        int sum = 0;
        for (auto p : get_c(S, i, j, r)) {
            sum += dp_rec_p(S, p.first, p.second) + get_k(S, p.first, p.second).size() - get_k(S, i, j).size();
        }
        if (sum < min) min = sum;
    }
    return min;
}

std::set<int> ada::trie2::get_k(const std::vector<std::string> &S, int i, int j) {
    std::set<int> k_set;
    for (int r = 0;  r <= get_m(S) - 1; r++) {
        std::set<char> temp_set;
        for (int k = i; k <= j; k++)
            temp_set.insert(S[k][r]);
        if (temp_set.size() == 1) k_set.insert(r);
    }
    return k_set;
}

std::set<int> ada::trie2::get_r(const std::vector<std::string> &S, int i, int j) {
    std::set<int> r_set;
    for (int x = 0; x <= get_m(S) - 1; x++) r_set.insert(x);
    auto k_set = get_k(S, i, j);
    for (auto y : k_set) {
        r_set.erase(y);
    }
    return r_set;
}

std::vector<std::pair<int, int>> ada::trie2::get_c(const std::vector<std::string> &S, int i, int j, int r) {
    std::vector<std::pair<int,int>> c_set;
    for (int x = i; x <= j; x++) {
        auto start = x;
        while (x < j && S[x][r] == S[x+1][r]) {
            x++;
        }
        c_set.emplace_back(start, x);
    }
    return c_set;
}

int ada::trie2::dp_rec(const std::vector<std::string> &S) {
    return dp_rec_p(S, 0, S.size() - 1) + get_k(S, 0, S.size() - 1).size();
}

int ada::trie2::dp_memo_p(const std::vector<std::string> &S, int i, int j, std::vector<std::vector<int>> &M) {
    if (i == j)
        return 0;
    if (M[i][j] != -1)
        return M[i][j];
    auto R = get_r(S, i, j);
    int min = INT_MAX;
    for (const auto& r : R) {
        int sum = 0;
        for (auto p : get_c(S, i, j, r)) {
            sum += dp_rec_p(S, p.first, p.second) + get_k(S, p.first, p.second).size() - get_k(S, i, j).size();
        }
        if (sum < min) {
            min = sum;
        }
    }
    M[i][j] = min;
    return min;
}

int ada::trie2::dp_memo(const std::vector<std::string> &S) {
    auto M = new std::vector<std::vector<int>>(S.size(), std::vector<int>(S.size(), -1));

    return dp_memo_p(S, 0, S.size() - 1, *M) + get_k(S, 0, S.size() - 1).size();
}

int ada::trie2::dp(const std::vector<std::string> &S) {
    auto M = new std::vector<std::vector<int>>(S.size(), std::vector<int>(S.size(), -1));
    // TODO check bounds and make DAG. Not working
    for (int i = 0; i < S.size(); i++) {
        for (int j = i; j < S.size(); j++) {

            auto R = get_r(S, i, j);
            int min = INT_MAX;
            for (const auto& r : R) {
                int sum = 0;
                for (auto p : get_c(S, i, j, r)) {
                    sum += (*M)[p.first][p.second] + get_k(S, p.first, p.second).size() - get_k(S, i, j).size();
                }
                if (sum < min) {
                    min = sum;
                }
            }
            (*M)[i][j] = min;
        }
    }

    return (*M)[0][S.size()-1];
}
