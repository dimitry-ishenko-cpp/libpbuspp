////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "types.hpp"
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
namespace pbus
{

////////////////////////////////////////////////////////////////////////////////
num to_num(const std::string& s)
{
    num n = 0;
    for(auto c : s)
             if(c >= '0' && c <= '9') n = (n << 4) + c - '0';
        else if(c >= 'A' && c <= 'F') n = (n << 4) + c - 'A' + 10;
        else return bad_num;

    return n;
}

////////////////////////////////////////////////////////////////////////////////
void throw_if_id_out_of_range(num id, const std::string& where)
{
    if(id > max_id) throw std::out_of_range{
        "Device # out of range in " + where
    };
}

////////////////////////////////////////////////////////////////////////////////
void throw_if_reg_out_of_range(num reg, const std::string& where)
{
    if(reg > max_reg) throw std::out_of_range{
        "Register # out of range in " + where
    };
}

////////////////////////////////////////////////////////////////////////////////
void throw_if_fn_out_of_range(num fn, const std::string& where)
{
    if(fn > max_fn) throw std::out_of_range{
        "Function # out of range in " + where
    };
}

////////////////////////////////////////////////////////////////////////////////
}
