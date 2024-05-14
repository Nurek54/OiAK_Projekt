cmake_minimum_required(VERSION 3.27)
project(OiAK)

set(CMAKE_CXX_STANDARD 23)

add_executable(OiAK main.cpp
        BoothRadix4.cpp
        BoothRadix4.h
        Booth.cpp
        Booth.h
        BinaryUtils.cpp
        BinaryUtils.h
        Modulo.cpp
        Modulo.h
        Modulo.h
)
