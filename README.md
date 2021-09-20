# libpbus++ – PBus Library for C++

The **libpbus++** library allows one to control peripheral devices as a master (switcher), or to act as a peripheral device and be controlled using the [Peripheral Bus II (PBus II)](https://wwwapps.grassvalley.com/docs/Manuals/switchers/kalypso/071-8063-08.pdf#page=93) protocol.

## Installation

### Binary

Debian/Ubuntu/etc:

```shell
$ p=libpbus++ v=0.0
$ wget https://github.com/dimitry-ishenko-cpp/libpbuspp/releases/download/v${v}/${p}_${v}_amd64.deb
$ sudo apt install ./${p}_${v}_amd64.deb
```

Install the development package, if you are planning to develop applications with **libpbus++**:
```shell
$ p=libpbus++-dev v=0.0
$ wget https://github.com/dimitry-ishenko-cpp/libpbuspp/releases/download/v${v}/${p}_${v}_amd64.deb
$ sudo apt install ./${p}_${v}_amd64.deb
```

RaspberryPi:

```shell
$ p=libpbus++ v=0.0
$ wget https://github.com/dimitry-ishenko-cpp/libpbuspp/releases/download/v${v}/${p}_${v}_armhf.deb
$ sudo apt install ./${p}_${v}_armhf.deb
```

Install the development package, if you are planning to develop applications with **libpbus++**:
```shell
$ p=libpbus++-dev v=0.0
$ wget https://github.com/dimitry-ishenko-cpp/libpbuspp/releases/download/v${v}/${p}_${v}_armhf.deb
$ sudo apt install ./${p}_${v}_armhf.deb
```

### From source

Stable version (requires [CMake](https://cmake.org/) >= 3.1 and [asio](https://think-async.com/Asio/)):

```shell
$ p=libpbus++ v=0.0
$ wget https://github.com/dimitry-ishenko-cpp/libpbuspp/releases/download/v${v}/${p}-${v}.tar.bz2
$ tar xzf v${v}.tar.gz
$ mkdir ${p}-${v}/build
$ cd ${p}-${v}/build
$ cmake ..
$ make
$ sudo make install
```

Latest master (requires [git](https://git-scm.com/), [CMake](https://cmake.org/) >= 3.1 and [asio](https://think-async.com/Asio/)):

```shell
$ p=libpbuspp
$ git clone --recursive https://github.com/dimitry-ishenko-cpp/${p}.git
$ mkdir ${p}/build
$ cd ${p}/build
$ cmake ..
$ make
$ sudo make install
```

## Authors

* **Dimitry Ishenko** - dimitry (dot) ishenko (at) (gee) mail (dot) com

## License

This project is distributed under the GNU GPL license. See the
[LICENSE.md](LICENSE.md) file for details.
