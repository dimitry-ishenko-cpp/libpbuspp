////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef PBUS_DEVICE_HPP
#define PBUS_DEVICE_HPP

////////////////////////////////////////////////////////////////////////////////
#include "serial_port.hpp"
#include "types.hpp"

#include <functional>
#include <string>

////////////////////////////////////////////////////////////////////////////////
namespace pbus
{

////////////////////////////////////////////////////////////////////////////////
using learn_callback = std::function<void (num reg)>;
using recall_callback = std::function<void (num reg)>;
using trigger_callback = std::function<void (num fn)>;

using query_callback = std::function<void ()>;
using read_callback = std::function<void (num reg)>;
using write_callback = std::function<void (num reg, const std::string& data)>;

////////////////////////////////////////////////////////////////////////////////
class device
{
public:
    device(serial_port&, num id);
    ~device();

    device(const device&) = delete;
    device(device&& rhs) { *this = std::move(rhs); }

    device& operator=(const device&) = delete;
    device& operator=(device&&);

    ////////////////////
    auto id() const { return id_; }

    void on_learn(learn_callback cb) { lcb_ = std::move(cb); }
    void on_recall(recall_callback cb) { rcb_ = std::move(cb); }
    void on_trigger(trigger_callback cb) { tcb_ = std::move(cb); }

    void on_query(query_callback cb) { qcb_ = std::move(cb); }
    void query_response(const std::string& data);

    void on_read(read_callback cb) { rdb_ = std::move(cb); }
    void write_response(num reg, const std::string& data);

    void on_write(write_callback cb) { wcb_ = std::move(cb); }

private:
    serial_port* port_ = nullptr;
    int ci_;

    num id_;
    learn_callback lcb_;
    read_callback rcb_;
    trigger_callback tcb_;
    query_callback qcb_;
    read_callback rdb_;
    write_callback wcb_;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
