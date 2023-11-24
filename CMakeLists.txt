cmake_minimum_required(VERSION 3.24.2)

project(hermes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_subdirectory(lib/wxWidgets)
add_subdirectory(lib/googletest-1.14.0)

add_subdirectory(src)
add_subdirectory(test)

include (FetchContent)
#----------------------------------wxWidgets------------------------------------

set(wxBUILD_SHARED ON)
set(wxWidgets_USE_STATIC 1)
set(wxBUILD_MONOLITHOC OFF)
set(wxUSE_STL ON)

include(FetchContent)
   FetchContent_Declare(
      wxWidgets
      GIT_REPOSITORY "https://github.com/wxWidgets/wxWidgets"
      GIT_TAG        "v3.2.2.1"
      GIT_PROGRESS   TRUE
      GIT_SHALLOW    TRUE
   )
   set(FETCHCONTENT_QUIET NO)
   if(NOT EMSPHINX_BUILD_SHARED)
      set(wxBUILD_SHARED OFF CACHE BOOL "Build wx libraries as shared libs")
   endif()

   # set(wxBUILD_PRECOMP OFF) # this prevents errors on recompile after the git hash changes
   if(UNIX AND NOT APPLE) # linux
      # use gtk3 on linux
      set(wxBUILD_TOOLKIT gtk3 CACHE STRING "Toolkit used by wxWidgets")

      # try to find gtk3 (this is based on wxWidget's cmake: wxWidgets/build/cmake/modules/FindGTK3.cmake)
      find_package(PkgConfig)
      pkg_check_modules(GTK3 QUIET gtk+-3.0)
      if(NOT GTK3_FOUND)
         message(FATAL_ERROR "wxWidgets needs gtk3 and libSM, make sure you have it with e.g.:\n"
                             "\tdebian 'apt-get install libgtk-3-dev libsm-dev build-essential'\n"
                             "\tcentos 'yum install gtk3-devel libSM-devel'\n")
      endif()

      # static linking has the same issue as hdf5 (the gtk .a file references commands in a .so so -ld is needed)
      if(NOT EMSPHINX_BUILD_SHARED)
         set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ldl")
      endif()
   endif()

   if(APPLE)
      set(wxUSE_WEBKIT OFF CACHE BOOL "use wxWebKitCtrl (Mac-only, use wxWebView instead)")
      set(wxUSE_WEBVIEW_WEBKIT OFF CACHE BOOL "use wxWebView WebKit background")
      set(wxUSE_LIBSDL OFF CACHE BOOL "Use SDL for wxSound implementation.")
   endif()

   FetchContent_MakeAvailable(wxWidgets)

#-----------------------------End-wxWidgets------------------------------------

set(SOURCE 
    src/main.cpp
    src/myapp.cpp
    src/myframp.cpp)

add_executable(${PROJECT_NAME}
                src/main.cpp 
                src/myapp.cpp 
                src/myframe.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE wx::base wx::core)

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


