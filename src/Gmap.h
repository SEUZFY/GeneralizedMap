#pragma once

#include "Point.h"

class Point;
class Dart;
class Vertex;
class Edge;
class Face;
class Volume;

class Dart {
    int dart_id;
    std::vector<Dart *> dart_involutions;
    Vertex * vertex;
    Edge *edge;
    Face *face;
    Dart():dart_id(0)
    {}
};

class Vertex {
    int vertex_id;
    Point point;
    Vertex() : point(Point())
    {}
    // constructor with x,y,z arguments to immediately initialise the point member on this Vertex.
    Vertex(const double &x, const double &y, const double &z, const int id) : point(Point(x,y,z)),vertex_id(id)
    {}
    void print() const {
        std::cout << "(" << point[0] << ", " << point[1] << ", " << point[2] << ")" << vertex_id<<std::endl; }
    // a dart incident to this Vertex:
    // ...
    Dart * incident_dart;
};

class Edge {
    int edge_id;

  // a dart incident to this Edge:

  // function to compute the barycenter for this Edge (needed for triangulation output):
  // Point barycenter() {}

};
class Face_vertices{
public:
    int x,y,z,t;
    Point a,b,c,d;
    // Face_vertices(const int &x, const int &y, const int &z,const int &t) : x(x), y(y), z(z),t(t)
    // {}
    Face_vertices(const Point &a, const Point &b, const Point &c,const Point &d) : a(a), b(b), c(c), d(d)
    {}

    void print() const {
        std::cout << "(" << a << ", " << b << ", " << c << ", "<< d << ")" << std::endl; }
    Face_vertices():x(0), y(0), z(0),t(0)
    {}
};


class Face {
    int face_id;
    Face_vertices face_ver;
    std::vector<Point> face_ver_list;
    Dart * incident_dart;

    Face(const Point &x, const Point &y, const Point &z, const Point &t) : face_ver(Face_vertices(x,y,z,t)),face_id(0)
    {}

    // Face(const int &x, const int &y, const int &z, const int &t) : face_ver(Face_vertices(x,y,z,t)),face_id(0)
    // {}
    Face():face_ver(Face_vertices()),face_id(0)
    {}

  // a dart incident to this Face:
  // ...

  // function to compute the barycenter for this Face (needed for triangulation output):
  // Point barycenter() {}

};

class Volume {
    int volume_id;
  // a dart incident to this Volume:
  // ...
};
