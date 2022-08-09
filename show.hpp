#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/draw_triangulation_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/draw_polygon_2.h>
#include <fstream>
#include <vector>
//#include "./dcel.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_2<K>                            Triangulation;
typedef Triangulation::Point                                T_Point;

typedef CGAL::Polygon_2 <K>                                  Polygon_2;
typedef CGAL::Point_2<K>                                    P_Point;

void show(vector<vertex> ps, std::string type = "triangulation")
{
  // create a Triangulation object and put some points in it
  if (type == "polygon")
  {
    Polygon_2 p;
    for (int i=0; i<ps.size(); i++)
    {
      p.push_back(P_Point(ps[i].x,ps[i].y));
    }
    CGAL::draw(p);
  }
  else if (type == "triangulation")
  {
    Triangulation t;
    for (int i=0; i<ps.size(); i++)
    {
      t.insert(T_Point(ps[i].x,ps[i].y));
    }
    CGAL::draw(t);
  }

}