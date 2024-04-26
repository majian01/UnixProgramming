# 基于李慧琴Linux C编程
本项目基于李慧琴Linux系统编程课，链接地址 【Linux系统编程（李慧琴）】 https://www.bilibili.com/video/BV1yJ411S7r6/?share_source=copy_web&vd_source=38476c984866d09e3b834e11d765b9b0
本项目基于CMake构建

# 编译环境
OS        Ubuntu 20.04
Kernel    5.15.0-102-generic
CMake     3.16.3
make      4.2.1
GCC       7.5.0
CPU       E3-1230v2(4Core 8Threads)
RAM       16G


# 编译方式
```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j${nproc}
```
