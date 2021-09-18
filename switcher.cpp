////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "switcher.hpp"
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
namespace pbus
{

////////////////////////////////////////////////////////////////////////////////
switcher::switcher(serial_port port) :
    port_{ std::move(port) }
{
    port.on_recv([&](std::string data)
    {
        if(data.size()) switch(data[0])
        {
        case pbus::query:
            if(qcb_)
            {
                data.erase(0, 1);
                qcb_(data);
            }
            break;

        case pbus::write:
            if(wcb_ && data.size() >= 6)
            {
                auto id = to_num(data.substr(1, 2));
                auto reg = to_num(data.substr(3, 3));
                data.erase(0, 6);
                if(id <= max_id && reg <= max_reg) wcb_(id, reg, data);
            }
            break;
        }
    });
}

////////////////////////////////////////////////////////////////////////////////
void switcher::learn(const pbus::map& map, num reg)
{
    throw_if_reg_out_of_range(reg, "switcher::learn()");
    port_.send(pbus::learn + to_hex(map) + to_hex(reg, 3));
}

////////////////////////////////////////////////////////////////////////////////
void switcher::recall(const pbus::map& map, num reg)
{
    throw_if_reg_out_of_range(reg, "switcher::recall()");
    port_.send(pbus::recall + to_hex(map) + to_hex(reg, 3));
}

////////////////////////////////////////////////////////////////////////////////
void switcher::trigger(const pbus::map& map, num fn)
{
    throw_if_fn_out_of_range(fn, "switcher::trigger()");
    port_.send(pbus::trigger + to_hex(map) + to_hex(fn, 1));
}

////////////////////////////////////////////////////////////////////////////////
void switcher::query(num id)
{
    throw_if_id_out_of_range(id, "switcher::query()");
    port_.send(pbus::query + to_hex(id, 2));
}

////////////////////////////////////////////////////////////////////////////////
void switcher::read(num id, num reg)
{
    throw_if_id_out_of_range(id, "switcher::read()");
    throw_if_reg_out_of_range(reg, "switcher::read()");

    port_.send(pbus::read + to_hex(id, 2) + to_hex(reg, 3));
}

////////////////////////////////////////////////////////////////////////////////
void switcher::write(num id, num reg, const std::string& data)
{
    throw_if_id_out_of_range(id, "switcher::write()");
    throw_if_reg_out_of_range(reg, "switcher::write()");

    port_.send(pbus::write + to_hex(id, 2) + to_hex(reg, 3) + data);
}

////////////////////////////////////////////////////////////////////////////////
}
