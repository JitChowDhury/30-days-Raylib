file(GLOB SRC_FILES *.cpp)

add_executable(day01 ${SRC_FILES})

# Include Raylib headers
target_include_directories(day01 PRIVATE
    ${RAYLIB_ROOT}/include
)

# Raylib static library
target_link_directories(day01 PRIVATE
    ${RAYLIB_ROOT}/lib
)

target_link_libraries(day01 PRIVATE
    raylib
    winmm
    gdi32
    opengl32
    shell32
)
