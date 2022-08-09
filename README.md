# 2D tool

Implementation of DCEL data structure for 2D environment in dcel.hpp header file

supported file formats are .plt and .gid

main file reads .gid and .plt files and adds points, edges and faces to the data structure and draws it with CGAL::draw function

show.hpp header file contains required function to show the triangular mesh of the points given in the .gid or .plt file

you can add points to triangualtion and rebuild the triangulation with add_point_to_triangulation.cpp
It'll add points to triangles with area greater than threshold given in the code
you can specify area threshold with variable AREA_TREASHOLD in the code add_point_to_triangulation.cpp