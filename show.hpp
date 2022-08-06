#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/draw_triangulation_2.h>
#include <fstream>
#include <vector>
//#include "./dcel.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_2<K>                            Triangulation;
typedef Triangulation::Point                                Point;

void show(vector<vertex> ps)
{
  // create a polygon and put some points in it
  Triangulation t;

  for (int i=0; i<ps.size(); i++)
  {
    t.insert(Point(ps[i].x,ps[i].y));
  }
  /*
  p.push_back(Point(0,0));
  p.push_back(Point(4,0));
  p.push_back(Point(4,4));
  p.push_back(Point(2,2));
  p.push_back(Point(0,4));
  */
  CGAL::draw(t);
}