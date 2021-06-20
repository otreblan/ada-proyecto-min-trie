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

#include <string>
#include <vector>

namespace ada
{

class trie
{
private:
	void ptrie_internal(const std::vector<std::string>& S, const std::vector<size_t>& p);
public:
	trie();
	trie(const std::vector<std::string>& S, const std::vector<size_t>& p = {});
};

};
