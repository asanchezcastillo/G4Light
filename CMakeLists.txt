cmake_minimum_required(VERSION 3.12)
project(Simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

find_program(MARLEY marley-config)
if(NOT MARLEY)
    message(FATAL_ERROR "The marley-config script is not present on the system PATH. Please ensure that MARLEY has been fully built and try again.")
endif()

execute_process(COMMAND ${MARLEY} --cflags OUTPUT_VARIABLE MARLEY_CXXFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${MARLEY} --libs OUTPUT_VARIABLE MARLEY_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

find_program(GEANT4_CONFIG geant4-config)
if(NOT GEANT4_CONFIG)
    message(FATAL_ERROR "The geant4-config script is not present on the system PATH. Please ensure that Geant4 has been fully built and try again.")
endif()

execute_process(COMMAND ${GEANT4_CONFIG} --cflags OUTPUT_VARIABLE GEANT4_CXXFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${GEANT4_CONFIG} --libs OUTPUT_VARIABLE GEANT4_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MARLEY_CXXFLAGS} ${GEANT4_CXXFLAGS} -Wall -Wextra -Wpedantic")

#Copy all the files that are created with the extension .mac to the build folder
file(GLOB MACRO_FILES
        "*.mac"
)
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

#Copy all the files that are created with the extension .mac to the build folder
file(GLOB DATA_FILES
        "*.dat"
)
file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${MARLEY_LIBS} ${GEANT4_LIBS})
