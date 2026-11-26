add_library(electrocad_core OBJECT
    electricalmodel.cpp
    electricalmodel.h
)

target_compile_features(electrocad_core PUBLIC cxx_std_17)
target_include_directories(electrocad_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Compile the adapter as part of QElectroTech's own object library. This
# deliberately inherits the exact include paths, compile definitions and
# dependency usage requirements established by the pinned upstream project.
# A separate target cannot safely assume that every Qt imported target is
# globally available in all supported QElectroTech/MSYS2 configurations.
target_sources(qelectrotech_objects PRIVATE
    qetdiagramadapter.cpp
    qetdiagramadapter.h
)
target_include_directories(qelectrotech_objects PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Compile the ElectroCAD core directly into the single QElectroTech-based
# application executable. No second application is produced.
target_sources(qelectrotech PRIVATE
    $<TARGET_OBJECTS:electrocad_core>
)

include(CTest)
if(BUILD_TESTING)
    add_executable(electrocad_model_tests
        tests/electricalmodel_tests.cpp
    )
    target_link_libraries(electrocad_model_tests PRIVATE electrocad_core)
    add_test(NAME electrocad_model_tests COMMAND electrocad_model_tests)
endif()
