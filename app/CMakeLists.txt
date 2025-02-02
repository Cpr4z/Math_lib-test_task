add_executable(app main.cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src/include)