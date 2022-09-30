cmake_minimum_required(VERSION 3.21)
project(macros)

set(CMAKE_CXX_STANDARD 14)

include_directories(/home/rj/root_install/include)

add_executable(macros
        Dialogs.C
        dsmacroworking.cc
        fileopen.C
        kmacro.C
        showerAxisAngles.C
        angleplots.C
        "start backup working pre loop.cc"
        start.cc
        "test (copy).cc"
        test.cc
        theanglemacro.C
        /home/rj/root_install/include/TFile.h
        /home/rj/root_install/include/TTree.h
        anglemacro.c)
