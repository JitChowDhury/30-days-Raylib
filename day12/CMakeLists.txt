file(GLOB SRC_FILES *.cpp)

add_executable(day12 ${SRC_FILES})

# Include Raylib headers
target_include_directories(day12 PRIVATE
    ${RAYLIB_ROOT}/include
)

# Raylib static library
target_link_directories(day12 PRIVATE
    ${RAYLIB_ROOT}/lib
)

target_link_libraries(day12 PRIVATE
    raylib
    winmm
    gdi32
    opengl32
    shell32
)
