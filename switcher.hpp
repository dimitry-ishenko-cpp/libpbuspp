////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef PBUS_SWITCHER_HPP
#define PBUS_SWITCHER_HPP

////////////////////////////////////////////////////////////////////////////////
#include "serial_port.hpp"
#include "types.hpp"

#include <functional>
#include <string>

////////////////////////////////////////////////////////////////////////////////
namespace pbus
{

////////////////////////////////////////////////////////////////////////////////
using query_response_callback = std::function<void (const std::string& data)>;
using write_response_callback = std::function<void (num id, num reg, const std::string& data)>;

////////////////////////////////////////////////////////////////////////////////
class switcher
{
public:
    explicit switcher(serial_port&);
    ~switcher();

    switcher(const switcher&) = delete;
    switcher(switcher&& rhs) { *this = std::move(rhs); }

    switcher& operator=(const switcher&) = delete;
    switcher& operator=(switcher&&);

    ////////////////////
    void learn(const map&, num reg);
    void recall(const map&, num reg);
    void trigger(const map&, num fn);

    void query(num id);
    void on_query_response(query_response_callback cb) { qcb_ = std::move(cb); }

    void read(num id, num reg);
    void on_write_response(write_response_callback cb) { wcb_ = std::move(cb); }

    void write(num id, num reg, const std::string& data);

private:
    serial_port* port_ = nullptr;
    int ci_;

    query_response_callback qcb_;
    write_response_callback wcb_;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif