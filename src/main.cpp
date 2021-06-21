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

#include <fstream>
#include <iostream>
#include <string>

#include "args.hpp"
#include "permutation.hpp"
#include "trie.hpp"

int main(int argc, char* argv[])
{
	using namespace std::string_literals;

	ada::args a;

	a.parse(argc, argv);

	switch(a.action)
	{
		case ada::trie_action::all_ptries:
		{
			int i = 0;
			for(const auto& p: ada::permutation(a.m))
			{
				std::ofstream ofs("ptrie"s + std::to_string(i) + ".gv");

				if(ofs.is_open())
					ofs << ada::trie(a.S, p);

				i++;
			}
			break;
		}

		case ada::trie_action::greedy:
			std::cout << ada::trie::greedy(a.S);
			break;
	}

	return EXIT_SUCCESS;
}
