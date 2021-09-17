////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "port.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace pbus
{

////////////////////////////////////////////////////////////////////////////////
serial_port::serial_port(asio::io_context& io, const std::string& device) :
    port_{ io, device }
{ }

////////////////////////////////////////////////////////////////////////////////
void serial_port::set(baud_rate    br) { port_.set_option(asio::serial_port::baud_rate     { br }); }
void serial_port::set(flow_control fc) { port_.set_option(asio::serial_port::flow_control  { fc }); }
void serial_port::set(parity       pr) { port_.set_option(asio::serial_port::parity        { pr }); }
void serial_port::set(stop_bits    sb) { port_.set_option(asio::serial_port::stop_bits     { sb }); }
void serial_port::set(char_size    cs) { port_.set_option(asio::serial_port::character_size{ cs }); }

////////////////////////////////////////////////////////////////////////////////
}

