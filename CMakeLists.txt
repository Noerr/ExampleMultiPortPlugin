cmake_minimum_required(VERSION 3.12)
project(ExampleMultiPortPlugin)

find_package(ParaView REQUIRED)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Enable plugin by default
set("_paraview_plugin_default_ExampleMultiPortReader" ON)

paraview_plugin_scan(
  PLUGIN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Plugin/paraview.plugin"
  PROVIDES_PLUGINS plugins
  REQUIRES_MODULES required_modules)

foreach(module IN LISTS required_modules)
  if(NOT TARGET "${module}")
    message("Missing required module: ${module}")
    return()
  endif()
endforeach()

paraview_plugin_build(
  PLUGINS ${plugins}
  AUTOLOAD ${plugins})
