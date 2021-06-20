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

#include <cstdlib>
#include <getopt.h>
#include <iostream>

#include "args.hpp"

void ada::args::usage(int exit_code) const
{
	std::cout <<
		"Usage: min-trie [ACTION] [--] S...\n"
		"\t-h, --help       Show this help.\n"
		"\t-a, --all-ptries Get all ptries of S.\n"
		"\t-g, --greedy     Get a S-ptrie with a greedy heuristic.\n"
	;

	exit(exit_code);
}

void ada::args::parse(int argc, char* argv[])
{
	int c;
	static char shortopts[] = "hag";
	static option options[] =
	{
		{"help",       no_argument, nullptr, 'h'},
		{"all-ptries", no_argument, nullptr, 'a'},
		{"greedy",     no_argument, nullptr, 'g'},
		{0, 0, 0, 0},
	};

	while((c = getopt_long(argc, argv, shortopts, options, nullptr)) != -1)
	{
		switch(c)
		{
			case 'h':
				usage(EXIT_SUCCESS);
				break;

			case 'a':
				action = trie_action::all_ptries;
				break;

			case 'g':
				action = trie_action::greedy;
				break;

			default:
				exit(EXIT_FAILURE);
		}
	}

	for(int i = optind; i < argc; i++)
	{
		S.emplace_back(argv[i]);
	}
}
