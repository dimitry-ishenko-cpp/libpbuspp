////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef PBUS_TYPES_HPP
#define PBUS_TYPES_HPP

////////////////////////////////////////////////////////////////////////////////
#include <limits>
#include <set>
#include <string>

////////////////////////////////////////////////////////////////////////////////
namespace pbus
{

////////////////////////////////////////////////////////////////////////////////
constexpr char learn   = 'L';
constexpr char recall  = 'R';
constexpr char trigger = 'T';
constexpr char query   = 'Q';
constexpr char read    = 'R';
constexpr char write   = 'W';
constexpr char delim   = '\x0d';

using num = unsigned int;
using map = std::set<num>;

constexpr num max_id  = 23;
constexpr num max_reg = 0xfff;
constexpr num max_fn  = 0xf;

////////////////////////////////////////////////////////////////////////////////
constexpr auto bad_num = std::numeric_limits<num>::max();
num to_num(const std::string&);

void throw_if_id_out_of_range (num, const std::string& where);
void throw_if_reg_out_of_range(num, const std::string& where);
void throw_if_fn_out_of_range (num, const std::string& where);

std::string to_hex(const pbus::map&);
std::string to_hex(num, std::size_t);

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
