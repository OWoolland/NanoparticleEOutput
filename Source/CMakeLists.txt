#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(NanoparticleEOutputProj)

#----------------------------------------------------------------------------
# Find local packages
find_library(libXmu NAMES libXmu.so PATHS /pc2013-data1/woolland/local/libXmu/lib/)

#----------------------------------------------------------------------------
# Find Geant4 package
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
add_executable(NanoparticleEOutput NanoparticleEOutput.cc ${sources} ${headers})
target_link_libraries(NanoparticleEOutput ${Geant4_LIBRARIES})
target_link_libraries(NanoparticleEOutput libXmu)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory
set(DIODE_SCRIPTS
  NanoparticleEOutput.mac
  vis.mac
  )

foreach(_script ${DIODE_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use 
add_custom_target(NanoparticleEOutputProj DEPENDS NanoparticleEOutput)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
install(TARGETS NanoparticleEOutput DESTINATION bin)
