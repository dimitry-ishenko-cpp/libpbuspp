////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef PBUS_SERIAL_PORT_HPP
#define PBUS_SERIAL_PORT_HPP

////////////////////////////////////////////////////////////////////////////////
#include <asio.hpp>

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
class serial_port
{
public:
    serial_port(asio::io_context&, const std::string& device);

    void set(baud_rate);
    void set(flow_control);
    void set(parity);
    void set(stop_bits);
    void set(char_size);

private:
    asio::serial_port port_;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
