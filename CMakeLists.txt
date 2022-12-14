# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

cmake_minimum_required(VERSION 3.1...3.23)

project( cg-2d-tool )

find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)


# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )

if ( NOT CGAL_FOUND )

  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()  

endif()


# Boost and its components
find_package( Boost REQUIRED )

if ( NOT Boost_FOUND )

  message(STATUS "This project requires the Boost library, and will not be compiled.")

  return()  

endif()

# include for local directory

# include for local package


# Creating entries for all C++ files with "main" routine
# ##########################################################


create_single_source_cgal_program( "lib_show_test.cpp" )

create_single_source_cgal_program( "main.cpp" )

if(CGAL_Qt5_FOUND)
  target_link_libraries(main PUBLIC CGAL::CGAL_Basic_viewer)
endif()

create_single_source_cgal_program( "show_test.cpp" )

if(CGAL_Qt5_FOUND)
  target_link_libraries(show_test PUBLIC CGAL::CGAL_Basic_viewer)
endif()

create_single_source_cgal_program( "draw_triangulation_2.cpp" )

if(CGAL_Qt5_FOUND)
  target_link_libraries(draw_triangulation_2 PUBLIC CGAL::CGAL_Basic_viewer)
endif()

#create_single_source_cgal_program( "segemnt.cpp" )


create_single_source_cgal_program( "add_point_to_triangulation.cpp" )

if(CGAL_Qt5_FOUND)
   target_link_libraries(add_point_to_triangulation PUBLIC CGAL::CGAL_Basic_viewer)
endif()

