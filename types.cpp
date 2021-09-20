////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "types.hpp"

#include <bitset>
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
void throw_if_data_out_of_range(const std::string& data, const std::string& where)
{
    if(data.size() > max_data_len) throw std::out_of_range{
        "Length of data out of range in " + where
    };
}

////////////////////////////////////////////////////////////////////////////////
std::string to_hex(const pbus::map& map)
{
    std::bitset<max_id + 1> mask;
    for(auto id : map)
    {
        throw_if_id_out_of_range(id, "to_hex()");
        mask.set(id);
    }

    return to_hex(mask.to_ulong(), 6);
}

////////////////////////////////////////////////////////////////////////////////
std::string to_hex(num n, std::size_t size)
{
    std::string s;
    for(auto i = size; i > 0; --i)
    {
        char c = (n >> (i * 4 - 4)) & 0xf;
        s += c < 10 ? c + '0' : c + 'A' - 10;
    }

    return s;
}

////////////////////////////////////////////////////////////////////////////////
map to_map(const std::string& s)
{
    pbus::map map;
    if(auto n = to_num(s); n != bad_num)
    {
        std::bitset<max_id + 1> mask{ n };
        for(auto i = 0; i < mask.size(); ++i) if(mask[i]) map.insert(i);
    }

    return map;
}

////////////////////////////////////////////////////////////////////////////////
}
