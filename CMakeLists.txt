cmake_minimum_required(VERSION 3.5)

project(SetContainer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

set(HEADERS 
    Container.h
    GroupContainer.h
    Mem.h
    MemoryManager.h

    )

set(SOURCE
    main.cpp
    )

add_executable(ProgramSet ${SOURCE} ${HEADERS})

set_target_properties(
    ProgramSet PROPERTIES
    CXX_STANDARD 14 
    CXX_STANDARD_REQUIRED ON
    )

