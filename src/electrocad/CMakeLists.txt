# Standalone model target is used by ElectroCAD's focused unit tests.
# The same implementation is also compiled into QElectroTech's shared object
# library below, because upstream test executables link that object library.
add_library(electrocad_core OBJECT
    electricalmodel.cpp
    electricalmodel.h
)

target_compile_features(electrocad_core PUBLIC cxx_std_17)
target_include_directories(electrocad_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# QElectroTech's application and its native test executables all consume
# qelectrotech_objects. Compile both ElectroCAD implementation units there so
# every consumer of the adapter also receives its model definitions.
target_sources(qelectrotech_objects PRIVATE
    electricalmodel.cpp
    electricalmodel.h
    qetdiagramadapter.cpp
    qetdiagramadapter.h
    qetdiagramtopology.cpp
    qetdiagramtopology.h
)
target_include_directories(qelectrotech_objects PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(CTest)
if(BUILD_TESTING)
    add_executable(electrocad_model_tests
        tests/electricalmodel_tests.cpp
    )
    target_link_libraries(electrocad_model_tests PRIVATE electrocad_core)
    add_test(NAME electrocad_model_tests COMMAND electrocad_model_tests)
endif()
