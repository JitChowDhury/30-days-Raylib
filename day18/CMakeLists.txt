file(GLOB_RECURSE DAY18_SRC
    src/*.cpp
)

add_executable(day18 ${DAY18_SRC})

target_include_directories(day18 PRIVATE
    ${RAYLIB_ROOT}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_directories(day18 PRIVATE
    ${RAYLIB_ROOT}/lib
)

target_link_libraries(day18 PRIVATE
    raylib
    winmm
    gdi32
    opengl32
    shell32
)
