////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef PBUS_TYPES_HPP
#define PBUS_TYPES_HPP

////////////////////////////////////////////////////////////////////////////////
namespace pbus
{

enum token
{
    learn   = 'L',
    recall  = 'R',
    trigger = 'T',
    query   = 'Q',
    read    = 'R',
    write   = 'W',
    delim   = '\x0d'
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif