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

#include "args.hpp"
#include "permutation.hpp"

int main(int argc, char* argv[])
{
	ada::args a;

	a.parse(argc, argv);

	std::cout << "S:\n";
	for(const auto& str: a.S)
	{
		std::cout << str << '\n';
	}

	for(const auto& pi: ada::permutation(a.m))
	{
		for(const auto& i: pi)
		{
			std::cout << i << ' ';
		}
		std::cout << '\n';
	}

	return EXIT_SUCCESS;
}
