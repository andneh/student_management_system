#! /bin/bash
cmake -G Ninja -B ./build;
cd build;
ninja;
./student_management_system.bin;
