file(GLOB_RECURSE DAY16_SRC
    src/*.cpp
)

add_executable(day16 ${DAY16_SRC})

target_include_directories(day16 PRIVATE
    ${RAYLIB_ROOT}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_directories(day16 PRIVATE
    ${RAYLIB_ROOT}/lib
)

target_link_libraries(day16 PRIVATE
    raylib
    winmm
    gdi32
    opengl32
    shell32
)
