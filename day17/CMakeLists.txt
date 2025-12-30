file(GLOB_RECURSE DAY17_SRC
    src/*.cpp
)

add_executable(day17 ${DAY17_SRC})

target_include_directories(day17 PRIVATE
    ${RAYLIB_ROOT}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_directories(day17 PRIVATE
    ${RAYLIB_ROOT}/lib
)

target_link_libraries(day17 PRIVATE
    raylib
    winmm
    gdi32
    opengl32
    shell32
)
