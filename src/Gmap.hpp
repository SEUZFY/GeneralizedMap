#pragma once

// ---------------------------some standard libraries that are helpfull for reading/writing text files
#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Point.h"

constexpr auto _NULL_ = -9999;

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


//class Dart {
//private:  
//    int m_id; // dart id
//    Dart* involution_pointers[4];  // involutions: a0, a1, a2, a3
//    std::size_t cell_dimensions[4]; // cells: 0-dimensional, 1-dimensional, 2-dimensional, 3-dimensional
//
//public:
//    Dart(): m_id(0){
//        for (auto& pDart : involution_pointers)pDart = nullptr;
//        for (auto c : cell_dimensions)c = 0;
//    }
//
//    // settings
//    // set dart id
//    int& id() { return m_id; }
//
//    // set involutions
//    void set_involution_to_dart(int dimension, Dart* dptr) {
//        involution_pointers[dimension] = dptr; //dptr could be nullptr
//    }
//
//    /*set incident cells :
//    * cell_dimensions[0]: id of 0-cell (vertex id)
//    * cell_dimensions[1]: id of 1-cell (edge id)
//    * cell_dimensions[2]: id of 2-cell (face id)
//    * cell_dimensions[3]: id of 3-cell (volume id) -- always null(_NULL_)*/
//    void set_incident_cell(int dimension, std::size_t cell_id) {
//        if (dimension >= 0 && dimension <= 3) {
//            cell_dimensions[dimension] = cell_id;
//        }
//    }
//
//    // helpful for debugging
//    void print_id()const { std::cout << m_id << '\n'; }
//    void print_cell(int dimension) { std::cout << cell_dimensions[dimension] << '\n'; }
//    void print_involution(int dimension) { std::cout << involution_pointers[dimension]->id() << '\n'; }
//
//
//    // cells:
//    // ...
//
//};

class Dart {
public:
    int id;
    int a[4]; // involution: a0, a1, a2, a3(null)
    int v; // 0-dimensional cell: vertex id, NOT 3-dimensional cell: volume
    int e; // 1-dimensional cell: edge id
    int f; // 2-dimensional cell: face id
    
public:
    Dart() :
        id(_NULL_),
        v(_NULL_),
        e(_NULL_),
        f(_NULL_)
    {
        for (int i = 0; i != 4; ++i) a[i] = _NULL_;
    }
};


class Vertex : public Point{
private:
    int id;

    // a dart incident to this Vertex:
    // dart id? or a pointer?

public:
    // constructor without arguments
    Vertex() : Point(),id(0){}

    // constructor with x,y,z arguments to immediately initialise the point member on this Vertex.
    Vertex(float x, float y, float z) : Point(x, y, z),id(0){}

    // access id
    // int& id() { return m_id; }


    virtual ~Vertex() = default;
    
};


class Edge {
public:
    int id;
    int start; // start vertex id
    int end; // end vertex id

    // a dart incident to this Edge:
    int Edge_dart_id;

    // function to compute the barycenter for this Edge (needed for triangulation output):
    // Point barycenter() {}
};


class Face {
public:
    int id;
    std::vector<int> Face_edge_list; // contains the edgeid of a Face
    std::vector<int> Face_vertex_list; // contains the vertex id of a Face, oriented CCW
    
    // a dart incident to this Face:
    int Face_dart_id;
public:
    Face() :
        id(_NULL_),
        Face_dart_id(_NULL_){}
    

    // function to compute the barycenter for this Face (needed for triangulation output):
    // Point barycenter() {}

};


class Volume {

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
    * vptr: a vector pointer pointing to a std::vector<Vertex> array, vertex list
    * fptr: a vector pointer pointing to a std::vector<std::vector<int>> array, face list
    */
    static void readobj(
        const std::string& param_filepath,
        const std::string& param_filename,
        std::vector<Vertex>* vptr,
        std::vector<std::vector<int>>* fptr)
    {
        vptr->emplace_back(Vertex(0.0, 0.0, 0.0)); // change 0-based index to 1-based index

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

};


class BuildGmapDependency {
public:

    /*
    * function: to judge whether the given elements are repeate
    * @parameter:
    * edge: current edge, type: a std::vector<int> array, contains two elements
    * eptr: edge list
    */
    static bool repeateEdgeCheck(
        std::vector<int>* edge,
        std::vector<std::vector<int>>* eptr)
    {
        for (auto& e : *eptr) {
            if (
                ((*edge)[0] == e[0] && (*edge)[1] == e[1]) ||
                ((*edge)[1] == e[0] && (*edge)[0] == e[1])
                ) {
                return true;
            }
        }
        return false;
    }


    /*
    * function: build edge_list based on face_list
    * @parameter:
    * fptr: a vector pointer pointing to a std::vector<std::vector<int>> array, face list
    * eptr: a vector pointer pointing to a std::vector<std::vector<int>> array. edge list
    */
    static void buildEdgeList(
        std::vector<std::vector<int>>* fptr,
        std::vector<std::vector<int>>* eptr)
    {
        for (auto& f : *fptr) { // each face: contains multiple vertex indexes, NB: 1-based indexes

            if (!f.empty()) {
                int N = (int)f.size(); // DO NOT use f.size() directly, for f.size()-1 may lead to index errors

                std::vector<int> edge_index; // initialize: add the first edge into the edge list
                edge_index.emplace_back(f[0]);
                edge_index.emplace_back(f[1]);
                if (repeateEdgeCheck(&edge_index, eptr)) {}
                else eptr->emplace_back(edge_index);

                for (int i = 1; i < N - 1; ++i) {
                    // repeate check
                    edge_index[0] = f[i];
                    edge_index[1] = f[i + 1];
                    if (repeateEdgeCheck(&edge_index, eptr))continue;
                    else eptr->emplace_back(edge_index);

                } // end for

                // make edge: the last id in a face-index, and the first id in a face-index
                // ie: face-index:[1,2,3,4], add [1,4](same as [4,1]) to the edge list
                // No need to execute repeate check first
                // Cuz the first element in a face-index is different from the last element in a face-index
                edge_index[0] = f[N - 1];
                edge_index[1] = f[0]; // caution: may overflow
                if (repeateEdgeCheck(&edge_index, eptr)) {}
                else eptr->emplace_back(edge_index);

            }// end if

        }// end for

    }// end of function


    /*
    * function: build face-edge maps
    * ie:
    * face-edge[0]:
    * all the edges belonging to face 0
    * it should contains multiple integers, indicating the edge id in the edge list
    * 
    * @parameter:
    * fptr: a vector pointer pointing to a std::vector<std::vector<int>> array, face list
    * eptr: a vector pointer pointing to a std::vector<std::vector<int>> array, edge list
    * faceid: the id of a certain face in the face list
    * 
    * @result:
    * std::vector<int> result, stores the edge indexes in the edge lists.
    */
    static void facefindEdge(
        std::vector<std::vector<int>>& facelist,
        std::vector<std::vector<int>>& edgelist,
        int faceid,
        std::vector<int>& result)
    {    
        if (faceid < 0 || faceid >= facelist.size())return;


        std::vector<int>* faceptr = &facelist[faceid]; // face[faceid]: std::vector<int>
        int numEdge = (int)edgelist.size();
        int numFace = (int)faceptr->size();


        // each integer(vertex id) in one face
        // traverse until the last-1 integer and the last integer
        // ie face[0]: [1,2,3,4]
        // look up: (1,2)(or(2,1)),(2,3)(or(3,2)),(3,4)(or(4,3)) in the edge list 
        // to find (4,1), need to manually find the last integer and the first integer
        for (int fid = 0; fid != numFace - 1; ++fid) {
            int vertexA = faceptr->at(fid);
            int vertexB = faceptr->at(fid + 1); // caution: may overflow

            for (int eid = 0; eid != numEdge; ++eid) {
                int vertex_a = edgelist[eid][0]; // each element in eptr array contains two integers
                int vertex_b = edgelist[eid][1];

                if ((vertexA == vertex_a && vertexB == vertex_b) ||
                    (vertexA == vertex_b && vertexB == vertex_a))
                {
                    result.emplace_back(eid); // add the current edge index into the result
                } // end if
            } // end for: each edge in the edge list

        } // end for: each integer in a face, not including the last and the first


        // find the last integer and the first integer
        int vertexA = faceptr->at(numFace - 1); // the last integer
        int vertexB = faceptr->at(0); // the first integer
        for (int eid = 0; eid != numEdge; ++eid) {
            int vertex_a = edgelist[eid][0]; // each element in eptr array contains two integers
            int vertex_b = edgelist[eid][1];

            if ((vertexA == vertex_a && vertexB == vertex_b) ||
                (vertexA == vertex_b && vertexB == vertex_a))
            {
                result.emplace_back(eid); // add the current edge index into the result
            } // end if
        } // end for: each edge in the edge list

    }

};


class BuildGmap {
public:

    /*function: build Faces
    * NB: the Face_dart_id remains to be unknown
    * @parameter:
    * facelist: std::vector<std::vector<int>> array, contains vertex ids for each face
    * edgelist: std::vector<std::vector<int>> array, contains vertex ids for each edge
    * Faces: built Faces array, contains all the faces(Face_dart_id remains to be set)
    */
    static void buildFaces(
        std::vector<std::vector<int>>& facelist,
        std::vector<std::vector<int>>& edgelist,
        std::vector<Face>& Faces)
    {
        for (int fid = 0; fid != facelist.size(); ++fid) {
            Face f;
            f.id = fid;

            for (int vid = 0; vid != facelist[fid].size(); ++vid) { // add vertex list for this face
                // facelist[fid][vid] -- vertex id of this face
                // facelist[fid] -- a std::vector<int> contains the vertex ids
                f.Face_vertex_list.emplace_back(facelist[fid][vid]);
            }

            BuildGmapDependency::facefindEdge(facelist, edgelist, fid, f.Face_edge_list); // add edge list for this face

            Faces.emplace_back(f);

        }
    }

	
    
    
    
    
 //   static void buildDartList(
	//	std::vector<std::vector<int>>& facelist,
	//	std::vector<std::vector<int>>& edgelist,
	//	std::vector<Dart>& dartlist)
	//{
	//	for (int faceid = 0; faceid != facelist.size(); ++faceid) {
	//		std::vector<int> findEdge;

	//		//for each face, find incident edges(stored in edge id)
 //           BuildGmapDependency::facefindEdge(facelist, edgelist, faceid, findEdge);

	//		for (auto& edgeid : findEdge) {
	//			//edgelist[edgeid][0] --vertexA of this edge
	//				//edgelist[edgeid][1] --vertexB of this edge

	//		}

	//	}
	//}
};





// overload functions:

// print vertices
std::ostream& operator<<(std::ostream& os, std::vector<Vertex>& vertices) {
    for (auto& v : vertices)
        os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << '\n';
    return os;
}