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
#include <map>
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
using recv_callback = std::function<void (const std::string&)>;

////////////////////////////////////////////////////////////////////////////////
class serial_port
{
public:
    serial_port(asio::io_context&, const std::string& device);

    serial_port(const serial_port&) = delete;
    serial_port(serial_port&&) = default;

    serial_port& operator=(const serial_port&) = delete;
    serial_port& operator=(serial_port&&) = default;

    void set(baud_rate);
    void set(flow_control);
    void set(parity);
    void set(stop_bits);
    void set(char_size);

private:
    asio::serial_port port_;

    int ci_ = 0;
    std::map<int, recv_callback> cb_;

    std::string recv_;
    void sched_recv();

    void send(std::string);

    int add_recv_callback(recv_callback cb)
    {
        cb_[ci_] = std::move(cb);
        return ci_++;
    }
    void remove_recv_callback(int ci) { cb_.erase(ci); }

    friend class switcher;
    friend class device;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
