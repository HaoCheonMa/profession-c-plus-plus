add_executable(computer main.cpp cpu.cpp disk.cpp gpu.cpp kbd.cpp ram.cpp )
target_include_directories(computer PUBLIC ${MY_INCLUDE_DIR})