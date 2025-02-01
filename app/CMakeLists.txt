add_executable(app main.cpp)

#set_target_properties(mathmodule PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src/include)

#target_link_libraries(app PRIVATE mathmodule)