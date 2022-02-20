#pragma once

// ---------------------------some standard libraries that are helpfull for reading/writing text files
#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Point.h"

#define _NULL_ 9999;

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
private:  
    std::size_t m_id; // dart id
    Dart* involution_pointers[4];  // involutions: a0, a1, a2, a3
    std::size_t cell_dimensions[4]; // cells: 0-dimensional, 1-dimensional, 2-dimensional, 3-dimensional

public:
    Dart(): m_id(0){
        for (auto& pDart : involution_pointers)pDart = nullptr;
        for (auto c : cell_dimensions)c = 0;
    }

    // settings
    // set dart id
    std::size_t& id() { return m_id; }

    // set involutions
    void set_involution_to_dart(int dimension, Dart* dptr) {
        involution_pointers[dimension] = dptr; //dptr could be nullptr
    }

    /*set incident cells :
    * cell_dimensions[0]: id of 0-cell (vertex id)
    * cell_dimensions[1]: id of 1-cell (edge id)
    * cell_dimensions[2]: id of 2-cell (face id)
    * cell_dimensions[3]: id of 3-cell (volume id) -- always null(_NULL_)*/
    void set_incident_cell(int dimension, std::size_t cell_id) {
        if (dimension >= 0 && dimension <= 3) {
            cell_dimensions[dimension] = cell_id;
        }
    }

    // helpful for debugging
    void print_id()const { std::cout << m_id << '\n'; }
    void print_cell(int dimension) { std::cout << cell_dimensions[dimension] << '\n'; }
    void print_involution(int dimension) { std::cout << involution_pointers[dimension]->id() << '\n'; }


    // cells:
    // ...

};


class Vertex : public Point{
private:
    std::size_t m_id;

    // a dart incident to this Vertex:
    // dart id? or a pointer?

public:
    // constructor without arguments
    Vertex() : Point(),m_id(0){}

    // constructor with x,y,z arguments to immediately initialise the point member on this Vertex.
    Vertex(float x, float y, float z) : Point(x, y, z),m_id(0){}

    // access id
    std::size_t& id() { return m_id; }


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


class ReadOBJ {
public:
    /*
    * function: read obj file and store vertices and face indexes.
    * @parameter:
    * param_filepath: file path
    * param_filename: file name
    * vptr: a vector pointer pointing to a std::vector<Vertec> array.
    * fptr: a vector pointer pointing to a std::vector<std::vector<int>> array.s
    */
    static void readobj(
        const std::string& param_filepath,
        const std::string& param_filename,
        std::vector<Vertex>* vptr,
        std::vector<std::vector<int>>* fptr)
    {
        std::string filename = param_filepath + param_filename; // filename
        std::string line;
        std::ifstream file(filename);
        if (!file.is_open()) { std::cerr << "file open failed! " << '\n'; }

        while (std::getline(file, line)) { // for each line in the file
            if (line.empty()) {
                continue; // skip empty lines:
            }

            std::stringstream ss(line);
            std::string field;
            std::string::size_type sz; // NOT std::size_t, size of std::string

            std::vector<float> coordinates; // store xyz coordinates in each line
            std::vector<int> face_vertex; // store face-point index in each line
            bool vertex_flag(false), face_flag(false); // to mark the current line: vertex or face, mark it as 'false' before process each line
            
            // for each element(field, type: string) in each line
            while (std::getline(ss, field, ' ')) { 
                
                 // current line is vertex
                if (field == "v") { 
                    vertex_flag = true; 
                    continue; // jump to next element in this line
                }

                // current line is face
                else if (field == "f") { 
                    face_flag = true; 
                    continue; // jump to next element in this line
                }

                if (vertex_flag) {
                    // process xyz coordinates
                    coordinates.emplace_back(std::stof(field, &sz));
                }
                else if (face_flag) {
                    // process f numbers
                    face_vertex.emplace_back(std::stoi(field, &sz));
                }
            } // end while: process each element in one line

            // process each point
            if (!coordinates.empty() && coordinates.size() == 3) vptr->emplace_back(coordinates[0], coordinates[1], coordinates[2]); 
            
            // process each face
            if (!face_vertex.empty())fptr->emplace_back(face_vertex);
        
        } // end while: each line in the file

    }

    /*
    * function: construct edge_list
    */

};
