cmake_minimum_required(VERSION 3.22)
project(projektGKIM)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules/) # podaje sciezke do FindSDL2.cmake
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${projektGKIM_SOURCE_DIR}/cmake/modules")
set(SDL2_PATH "SDL2")

find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
                    #${SDL2_IMAGE_INCLUDE_DIR}
                   # ${SDL2_TTF_INCLUDE_DIR})

add_executable(projektGKIM main.cpp)

target_link_libraries(projektGKIM   ${SDL2_LIBRARY})
                                    #${SDL2_IMAGE_LIBRARIES}
                                    #${SDL2_TTF_LIBRARIES} )