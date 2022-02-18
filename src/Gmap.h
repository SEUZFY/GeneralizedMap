#pragma once

#include "Point.h"

class Point;
class Dart;
class Vertex;
class Edge;
class Face;
class Volume;

/*
Below you find the basic elements that you need to build the generalised map.
The main thing you need to fill out are the links between the elements:
  * the involutions and cells on the Dart
  * the darts on the cells

One way to do this is by using pointers. eg. define a member on the dart struct like

  Struct Dart {
    // involutions:
    Dart* a0 = nullptr;
    // ...

    // cells:
    // ...

  };

Then you could create and link Darts like:

  Dart* dart_a = new Dart();
  Dart* dart_b = new Dart();

  dart_a->a0 = dart_b;
*/

class Dart {
public:  
    // involutions:
    // ..

    // cells:
    // ...

};

class Vertex : public Point{
    // access the coordinates of this vertex:
    // x, y, z
    // v[0], v[1], v[2]
public:
    // constructor without arguments
    Vertex() : Point(){}

    // constructor with x,y,z arguments to immediately initialise the point member on this Vertex.
    Vertex(const float& x, const float& y, const float& z) : Point(x, y, z){}

    // a dart incident to this Vertex:
    // ...

    virtual ~Vertex() = default;
   

};

class Edge {
public:
    // a dart incident to this Edge:
    // ...

    // function to compute the barycenter for this Edge (needed for triangulation output):
    // Point barycenter() {}
};

class Face {
public:
    // a dart incident to this Face:
    // ...

    // function to compute the barycenter for this Face (needed for triangulation output):
    // Point barycenter() {}

};

class Volume {
public:
    // a dart incident to this Volume:
    // ...

};
