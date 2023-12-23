cmake_minimum_required(VERSION 3.24.2)

project(hermes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_subdirectory(lib/wxWidgets)
add_subdirectory(lib/googletest-1.14.0)

add_subdirectory(src)
add_subdirectory(test)

set(SOURCE 
    src/main.cpp
    src/myapp.cpp
    src/myframp.cpp)


find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()
set(wxUSE_GUI ON)
add_executable(${PROJECT_NAME}
                src/main.cpp 
                src/myapp.cpp 
                src/myframe.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/wx-3.2/)
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})

#-----------------------------Documentation(Doxygen)----------------------------
# Require dot, treat the other components as optional
# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


#------------------------End--Documentation(Doxygen)----------------------------


