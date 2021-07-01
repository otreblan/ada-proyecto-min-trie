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

#include <iostream>

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
