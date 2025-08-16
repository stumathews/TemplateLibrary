cmake_minimum_required(VERSION 4.0)
project(testlib VERSION 1.0)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(headerFiles
 messages.h
)

set(sourceFiles
 messages.cpp
)

set(sourceAndHeaderFiles 
 ${headerFiles}
 )

 list (APPEND sourceAndHeaderFiles 
  ${sourceFiles})

add_library(testlib STATIC)

target_sources(testlib
 PRIVATE 
  ${sourceFiles}
 PUBLIC
  FILE_SET public_headers
  TYPE HEADERS
  FILES ${headerFiles}
)

add_library(testlib::testlib ALIAS testlib)

generate_export_header(testlib)

set_target_properties(testlib 
 PROPERTIES 
 LINKER_LANGUAGE CXX 
)

include(GNUInstallDirs)

install(
    TARGETS testlib 
        EXPORT testlib # produce target exports for this target
    RUNTIME 
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY 
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE 
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FILE_SET public_headers
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}       
    INCLUDES 
     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Create/write the targets exports to the specified file name in the lib directory (as this is where downstream packages look for it via find_package())

install(EXPORT testlib
 DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/testlib
 NAMESPACE testlib::
)

# Write a basic package config version file for us please
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/testlib/testlibConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

set(ConfigPackageLocation lib/cmake/testlib)

install(
  FILES
    cmake/testlibConfig.cmake # This file must be created by us
    "${CMAKE_CURRENT_BINARY_DIR}/testlib/testlibConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)
