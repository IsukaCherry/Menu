cmake_minimum_required(VERSION 3.30)
project(Menu C)

set(CMAKE_C_STANDARD 11)

add_executable(Menu src/main.c
        src/logiAndRegister/LoginRegister.c
        src/logiAndRegister/LoginRegister.h
        src/entity/struct.h
        src/wordBook/WordBookManagement.c
        src/wordBook/WordBookManagement.h
        src/memorizeWord/MemorizeWords.c
        src/memorizeWord/MemorizeWords.h)
