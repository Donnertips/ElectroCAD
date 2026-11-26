add_library(electrocad_core OBJECT
    electricalmodel.cpp
    electricalmodel.h
)

target_compile_features(electrocad_core PUBLIC cxx_std_17)
target_include_directories(electrocad_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Compile the ElectroCAD core directly into the single QElectroTech-based
# application executable. No second application is produced.
target_sources(qelectrotech PRIVATE $<TARGET_OBJECTS:electrocad_core>)

include(CTest)
if(BUILD_TESTING)
    add_executable(electrocad_model_tests
        tests/electricalmodel_tests.cpp
    )
    target_link_libraries(electrocad_model_tests PRIVATE electrocad_core)
    add_test(NAME electrocad_model_tests COMMAND electrocad_model_tests)
endif()
