////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "device.hpp"
#include <utility> // std::swap

////////////////////////////////////////////////////////////////////////////////
namespace pbus
{

////////////////////////////////////////////////////////////////////////////////
device::device(serial_port& port, num id) :
    port_{ &port }, id_{ id }
{
    throw_if_id_out_of_range(id_, "device::device()");

    ci_ = port_->add_recv_callback([&](std::string data)
    {
        if(data.size()) switch(data[0])
        {
        case pbus::learn:
            if(lcb_ && data.size() == 10)
            {
                auto map = to_map(data.substr(1, 6));
                auto reg = to_num(data.substr(7));
                if(map.count(id_) && reg <= max_reg) lcb_(reg);
            }
            break;

        case 'R':
            if(rcb_ && data.size() == 10) // pbus::recall
            {
                auto map = to_map(data.substr(1, 6));
                auto reg = to_num(data.substr(7));
                if(map.count(id_) && reg <= max_reg) rcb_(reg);
            }
            else if(rdb_ && data.size() == 6) // pbus::read
            {
                auto id = to_num(data.substr(1, 2));
                auto reg = to_num(data.substr(3));
                if(id == id_ && reg <= max_reg) rdb_(reg);
            }
            break;

        case pbus::trigger:
            if(tcb_ && data.size() == 8)
            {
                auto map = to_map(data.substr(1, 6));
                auto fn = to_num(data.substr(7));
                if(map.count(id_) && fn <= max_fn) tcb_(fn);
            }
            break;

        case pbus::query:
            if(qcb_ && data.size() == 3)
            {
                data.erase(0, 1);
                if(auto id = to_num(data); id == id_) qcb_();
            }
            break;

        case pbus::write:
            if(wcb_ && data.size() >= 6 && data.size() <= 6 + max_data_len)
            {
                auto id = to_num(data.substr(1, 2));
                auto reg = to_num(data.substr(3, 3));
                data.erase(0, 6);
                if(id == id_ && reg <= max_reg) wcb_(reg, data);
            }
            break;
        }
    });
}

////////////////////////////////////////////////////////////////////////////////
device::~device()
{
    if(port_) port_->remove_recv_callback(ci_);
}

////////////////////////////////////////////////////////////////////////////////
device& device::operator=(device&& rhs)
{
    std::swap(port_, rhs.port_);
    std::swap(ci_  , rhs.ci_  );
    std::swap(id_  , rhs.id_  );
    std::swap(lcb_ , rhs.lcb_ );
    std::swap(rcb_ , rhs.rcb_ );
    std::swap(tcb_ , rhs.tcb_ );
    std::swap(qcb_ , rhs.qcb_ );
    std::swap(rdb_ , rhs.rdb_ );
    std::swap(wcb_ , rhs.wcb_ );
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
void device::query_response(const std::string& data)
{
    throw_if_data_out_of_range(data, "device::query_response()");
    port_->send(pbus::query + data);
}

////////////////////////////////////////////////////////////////////////////////
void device::write_response(num reg, const std::string& data)
{
    throw_if_reg_out_of_range(reg, "device::write_response()");
    throw_if_data_out_of_range(data, "device::write_response()");

    port_->send(pbus::write + to_hex(id_, 2) + to_hex(reg, 3) + data);
}

////////////////////////////////////////////////////////////////////////////////
}

