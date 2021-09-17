////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef PBUS_SERIAL_PORT_HPP
#define PBUS_SERIAL_PORT_HPP

////////////////////////////////////////////////////////////////////////////////
#include "types.hpp"

#include <asio.hpp>
#include <functional>
#include <string>

////////////////////////////////////////////////////////////////////////////////
namespace pbus
{

////////////////////////////////////////////////////////////////////////////////
namespace literals
{

enum baud_rate { };
constexpr auto operator"" _baud(unsigned long long n) noexcept { return static_cast<baud_rate>(n); }

using flow_control = asio::serial_port::flow_control::type;
using parity = asio::serial_port::parity::type;
using stop_bits = asio::serial_port::stop_bits::type;

enum char_size { };
constexpr auto operator"" _bits(unsigned long long n) noexcept { return static_cast<char_size>(n); }

}

using namespace literals;

////////////////////////////////////////////////////////////////////////////////
using recv_callback = std::function<void (std::string)>;

////////////////////////////////////////////////////////////////////////////////
class serial_port
{
public:
    serial_port(asio::io_context&, const std::string& device);

    void set(baud_rate);
    void set(flow_control);
    void set(parity);
    void set(stop_bits);
    void set(char_size);

    void send(std::string);
    void on_recv(recv_callback cb) { cb_ = std::move(cb); }

private:
    asio::serial_port port_;
    recv_callback cb_;

    std::string recv_;
    void sched_recv();
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
