////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "serial_port.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace pbus
{

////////////////////////////////////////////////////////////////////////////////
serial_port::serial_port(asio::io_context& io, const std::string& device) :
    port_{ io, device }
{
    sched_recv();
}

////////////////////////////////////////////////////////////////////////////////
void serial_port::set(baud_rate    br) { port_.set_option(asio::serial_port::baud_rate     { br }); }
void serial_port::set(flow_control fc) { port_.set_option(asio::serial_port::flow_control  { fc }); }
void serial_port::set(parity       pr) { port_.set_option(asio::serial_port::parity        { pr }); }
void serial_port::set(stop_bits    sb) { port_.set_option(asio::serial_port::stop_bits     { sb }); }
void serial_port::set(char_size    cs) { port_.set_option(asio::serial_port::character_size{ cs }); }

////////////////////////////////////////////////////////////////////////////////
void serial_port::send(std::string cmd)
{
    cmd.push_back(delim);
    asio::write(port_, asio::buffer(std::move(cmd)));
}

////////////////////////////////////////////////////////////////////////////////
void serial_port::sched_recv()
{
    asio::async_read_until(port_, asio::dynamic_buffer(recv_), delim,
        [&](asio::error_code ec, std::size_t n)
        {
            if(ec) return;

            auto cmd = recv_.substr(0, n - 1);
            recv_.erase(0, n);

            for(auto& [_, cb] : cb_) cb(cmd);

            sched_recv();
        }
    );
}

////////////////////////////////////////////////////////////////////////////////
}

