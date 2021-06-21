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
#include <iostream>

#include "trie.hpp"

const ada::trie::node ada::trie::root = 0;

ada::trie::node ada::trie::next_node(node n, char c)
{
	auto range = edges.equal_range(n);
	for(auto it = range.first; it != range.second; it++)
	{
		auto c_it = f.find(*it);
		if(c_it != f.end() && c_it->second == c)
		{
			return it->second;
		}
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

std::vector<size_t> ada::trie::greedy_p(const std::vector<std::string>& S)
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

	for(size_t i = 0; i < m-1; i++)
	{
		if(h(p[i+1]) < h(p[i]))
			std::swap(p[i], p[i+1]);
	}

	return p;
}

ada::trie ada::trie::greedy(const std::vector<std::string>& S)
{
	return trie(S, greedy_p(S));
}

std::ostream& ada::operator<<(std::ostream& os, const ada::trie& t)
{
	os <<
		"digraph D {\n"
		"\tforcelabels=true;\n"
		"\tlabelloc=\"t\";\n"
		"\tlabeljust=\"l\";\n"
		"\tlabel=\"# aristas: " << t.edges.size() << "\";\n"
	;

	os << "\n\t//Nodes\n";
	for(const auto& n: t.nodes)
	{
		os << '\t' << n << " [label=\"\"];\n";
	}

	os << "\n\t//Edges\n";
	for(const auto& e: t.edges)
	{
		os
			<< '\t'
			<< e.first
			<< " -> "
			<< e.second
			<< " [label=\""
			<< t.f.at(e)
			<< "\"];\n"
		;
	}

	os << "}\n";
	return os;
}
