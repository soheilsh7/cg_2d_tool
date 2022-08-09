#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/draw_triangulation_2.h>
#include <fstream>
#include <vector>
//#include "./dcel.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_2<K>                            Triangulation;
typedef Triangulation::Point                                Point;

typedef Triangulation::Vertex_handle 	Vertex_handle;
typedef Triangulation::Face_handle 	Face_handle;

typedef Triangulation::Finite_faces_iterator 	Face_iterator;
typedef Triangulation::Finite_vertices_iterator 	Vertex_iterator;

/*
Point midpoint(const Point& p, const Point& q)
{
  return Point((p.x()+q.x())/2, (p.y()+q.y())/2);
}

Point triangle_center(const Point& p, const Point& q, const Point& r)
{
  return midpoint(midpoint(p, q), r);
}
*/



Point triangle_center(const Point& p, const Point& q, const Point& r)
{
  return Point((p.x()+q.x()+r.x())/3, (p.y()+q.y()+r.y())/3);
}


float AREA_TREASHOLD = 20;


//void show(vector<vertex> ps)
int main()
{
    Triangulation t;

    /*
    for (int i=0; i<ps.size(); i++)
    {
        t.insert(Point(ps[i].x,ps[i].y));
    }
    */
    t.push_back(Point(0,0));
    t.push_back(Point(10,0));
    t.push_back(Point(10,10));
    t.push_back(Point(5,5));
    t.push_back(Point(0,10));
    CGAL::draw(t);
    Face_handle f = Face_handle();
    //Vertex_handle v = Vertex_handle();
    
    //t.insert(Point(7,5), f);

    //CGAL::draw(t);


    Face_iterator fit;
    Vertex_iterator vit;

    float area;
    Point center;

    Triangulation cp;
    cp = t;

    for (fit = t.finite_faces_begin(); fit != t.finite_faces_end(); fit++)
    {   
        area =  CGAL::area(fit->vertex(0)->point(),fit->vertex(1)->point(),fit->vertex(2)->point());
        
        if (area > AREA_TREASHOLD)
        {
            center = triangle_center(fit->vertex(0)->point(),fit->vertex(1)->point(),fit->vertex(2)->point());
            std::cout << "center: " << center.x() << "\t" << center.y() << std::endl;
            //t.push_back(center);
            cp.insert(Point(center.x(), center.y()), f);
        }
        
        std::cout << area << std::endl;
       
        //std::cout << CGAL::area(fit->vertex(0)->point(),fit->vertex(1)->point(),fit->vertex(2)->point()) << std::endl;
    }

    CGAL::draw(cp);

} 