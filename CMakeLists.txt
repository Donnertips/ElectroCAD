cmake_minimum_required(VERSION 3.25)

project(ElectroCAD
    VERSION 0.1.0
    DESCRIPTION "Electrical CAD application based on QElectroTech"
    LANGUAGES C CXX
)

# Initial integration proof: CI checks out the pinned upstream source into
# this directory. This is intentionally a required external source path until
# the submodule layout is introduced.
set(ELECTROCAD_UPSTREAM_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/upstream"
    CACHE PATH "Path to the pinned QElectroTech source tree")

if(NOT EXISTS "${ELECTROCAD_UPSTREAM_SOURCE_DIR}/CMakeLists.txt")
    message(FATAL_ERROR
        "QElectroTech source not found at '${ELECTROCAD_UPSTREAM_SOURCE_DIR}'. "
        "Check out the pinned upstream source and its submodules first.")
endif()

# QElectroTech creates qelectrotech_objects and qelectrotech. Its executable
# is the host application; ElectroCAD's own core is compiled into that target.
add_subdirectory("${ELECTROCAD_UPSTREAM_SOURCE_DIR}"
                 "${CMAKE_CURRENT_BINARY_DIR}/qelectrotech")
add_subdirectory(src/electrocad)
