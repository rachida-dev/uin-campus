# UIN-Campus

Systeme de gestion academique de l'UIN (squelette du projet, version 0.1.0).

## Versions des outils

-cmake 4.2.3
-g++ 15.2.0
-clang++ 21.1.8
-clang-format 21.1.8
-clang-tidy 21.1.8
-clangd 21.1.8
-gdb 17.1
-valgrind 3.26.0

## Compilation et execution

'''
cd uin-campus
cmake --preset debug
cmake --build --preset debug
./build/debug/uin-campus
'''

## qualite du code

'''
clang-format -i include/uincampus/*.hpp src/*.cpp app/*.cpp
clang-tidy -p build/debug src/*.cpp app/*.cpp
'''
