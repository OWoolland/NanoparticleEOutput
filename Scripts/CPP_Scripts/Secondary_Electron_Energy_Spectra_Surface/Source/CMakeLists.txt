#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Secondary_Electron_Energy_Spectra_SurfaceProj)

#----------------------------------------------------------------------------
# Setup include directory for this project
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the 2Geant4 libraries
add_executable(Secondary_Electron_Energy_Spectra_Surface Secondary_Electron_Energy_Spectra_Surface.cc ${sources} ${headers})
target_link_libraries(Secondary_Electron_Energy_Spectra_Surface pthread)
link_libraries(pthread)
#----------------------------------------------------------------------------
# Copy all scripts to the build directory
set(Secondary_Electron_Energy_Spectra_Surface_SCRIPTS
  )

foreach(_script ${Secondary_Electron_Energy_Spectra_Surface_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
install(TARGETS Secondary_Electron_Energy_Spectra_Surface DESTINATION bin)
