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
public:
    int id; // vertex id : the id in the vertices vector, also in OBJ file
    int Vertex_dart; // incident dart
    
public:
    // constructor without arguments
    Vertex() : 
        Point(),
        id(_NULL_),
        Vertex_dart(_NULL_){}

    // constructor with x,y,z arguments to immediately initialise the point member on this Vertex.
    Vertex(float x, float y, float z) : 
        Point(x, y, z),
        id(_NULL_),
        Vertex_dart(_NULL_){}

    // access id
    // int& id() { return m_id; }


    virtual ~Vertex() = default;
    
};


class Edge {
public:
    int id;
    int start; // start vertex id, NB: (start, end) and (end, start) is the same edge
    int end; // end vertex id

    // a dart incident to this Edge:
    int Edge_dart_id;

public:
    Edge():
        id(_NULL_),
        start(_NULL_),
        end(_NULL_),
        Edge_dart_id(_NULL_){}

    // function to compute the barycenter for this Edge (needed for triangulation output):
    // Point barycenter() {}
};


class Face {
public:
    int id;
    std::vector<int> Face_edge_list; // contains the edgeid in Edges of a Face
    std::vector<int> Face_vertex_list; // contains the vertex id of a Face, oriented CCW
    std::vector<int> Face_dart_list; //contains the dart ids which belong to one same face
    
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
        std::vector<Vertex>& vertices,
        std::vector<std::vector<int>>& facelist)
    {
        
        vertices.emplace_back(Vertex(0.0, 0.0, 0.0)); // change 0-based index to 1-based index

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
            if (!coordinates.empty() && coordinates.size() == 3) {
                vertices.emplace_back(coordinates[0], coordinates[1], coordinates[2]);
            }
              
            // process each face
            if (!face_vertex.empty())facelist.emplace_back(face_vertex);
        
        } // end while: each line in the file

        // set vertex id for each vertex
        for (int i = 0; i != vertices.size(); ++i) {
            vertices[i].id = i;
        }

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
    * 
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


    /*function: build Edges
    * NB: the Edge_dart_id remains to be unknown -- set it in buildDarts()
    * 
    * @parameter:
    * edgelist: std::vector<std::vector<int>> array, contains vertex ids for each edge
    * Faces: built Faces array, contains all the faces(Face_dart_id remains to be set)
    */
    static void buildEdges(
        std::vector<std::vector<int>>& edgelist,
        std::vector<Edge>& Edges)
    {
        for (int eid = 0; eid != edgelist.size(); ++eid) {
            Edge e;
            e.id = eid;
            e.start = edgelist[eid][0];
            e.end = edgelist[eid][1];

            Edges.emplace_back(e);
        }
    }
    

    /*function: build Darts
    * NB: the a[2] remains to be set
    * 
    * @parameter:
    * Faces: a vector contains all faces needed
    * Edges: a vector contains all edges needed
    * Darts: result vector, store all the built darts
    */
    static void buildDarts(
        std::vector<Vertex>& vertices,
        std::vector<Face>& Faces,
        std::vector<Edge>& Edges,
        std::vector<Dart>& Darts)
    {
        int did(0); // once it's assigned to a dart id, did + 1

        for (int fid = 0; fid != Faces.size();++fid) 
        { // for each face

            // update the start and end of edges of this current face
            // make it associated with the original CCW orientation
            // ie, the vertex sequence of this face is: 1 2 3 4, CCW
            // the edge sequence is: 0 1 2 3, CCW, where edge 0: start = 1, end = 2
            // but the edge 1: start = 3, end = 2
            // the start and end of one edge may be dynamically updated until all the faces are traversed
         
            // the size of vertex list is the same as the size of edge list of a face
            // ie: n vertices, n edges
            // update 1: update the first edge until the last-1 edge(ie update edge 0 1 2)
            int updateEdgeN = (int)Faces[fid].Face_edge_list.size();
            for (int i = 0; i != updateEdgeN - 1; ++i)
            {
                int Eid = Faces[fid].Face_edge_list[i]; // current edge id in vector Edges
                int CompareVid= Faces[fid].Face_vertex_list[i]; // the vertex id compared to the start of the edge

                if (Edges[Eid].start == CompareVid)continue;
                else // if not, swap the start and end of this edge
                {
                    int temp = Edges[Eid].start;
                    Edges[Eid].start = Edges[Eid].end;
                    Edges[Eid].end = temp;
                }
            }

            // update 2: update the last edge
            // the last vertex: vertices[vsize()-1], the last edge: Edges[esize()-1]
            int updateVertexN = (int)Faces[fid].Face_vertex_list.size();
            int lastEid = Faces[fid].Face_edge_list[updateEdgeN - 1]; // the edge id of the last edge of this face(CCW)
            int lastVid = Faces[fid].Face_vertex_list[updateVertexN - 1]; // the vertex id of the last vertex of this face(CCW)

            if (Edges[lastEid].start != lastVid) // swap the start and end
            {
                int temp = Edges[lastEid].start;
                Edges[lastEid].start = Edges[lastEid].end;
                Edges[lastEid].end = temp;
            }
            // update complete


            // for each edge of one face:  Faces[fid], build 2 Darts of each face
            for (int eid = 0; eid != Faces[fid].Face_edge_list.size();++eid) 
            { 
                
                // current edge:
                int edge_id = Faces[fid].Face_edge_list[eid];

                // each edge has two vertices, for the same face, same edge, two vertices lead to
                // two darts: d1, d2
                Dart d1;
                d1.id = did;
                ++did;
                d1.f = Faces[fid].id; // fid = Faces[fid].id

                d1.e = edge_id; // edge id of this face: Faces[fid].Face_edge_list[eid]
                d1.v = Edges[edge_id].start;


                // Dart d2: same face and same edge with d1, but different vertex
                Dart d2;
                d2.id = did;
                ++did;
                d2.f = Faces[fid].id;

                d2.e = edge_id; // edge id of this face: Faces[fid].Face_edge_list[eid]
                d2.v = Edges[edge_id].end; // different from d1

                //set d1 d2: a[0] involution
                d1.a[0] = d2.id;
                d2.a[0] = d1.id;

                // add d1, d2 to Darts
                Darts.emplace_back(d1);
                Darts.emplace_back(d2);

                // set the incident dart of this edge
                // for each edge: Edges[edge_id], just set one arbitrary dart as its incident dart
                // for the same edge, the Edge_dart_id may get updated when traversing each face
                Edges[edge_id].Edge_dart_id = d1.id; 

                // set the incident dart of two vertices of this edge
                int va_index = Edges[edge_id].start; // d1.v
                int vb_index = Edges[edge_id].end; // d2.v
                vertices[va_index].Vertex_dart = d1.id;
                vertices[vb_index].Vertex_dart = d2.id;

                // add the built darts to this face's Face_dart_list;
                Faces[fid].Face_dart_list.emplace_back(d1.id);
                Faces[fid].Face_dart_list.emplace_back(d2.id);

            } // end for: each edge


            // set the incident dart of current face as the incident dart of 
            // the first edge's incident dart of this face
            int first_edge_id = Faces[fid].Face_edge_list[0];
            Faces[fid].Face_dart_id = Edges[first_edge_id].Edge_dart_id;


            // for the darts already stored in Darts, set a[1]: same face, same vertex, different edge
            // the edge ids of a face are stored CCW
            // for the newly-stored darts: newly add 2*Faces[fid].Face_edge_list.size() elements
            // current size() - newly added size --> starting index of Dart

            int current_size = (int)Darts.size();
            int newly_added_edges = (int)Faces[fid].Face_edge_list.size();
            int newly_added_darts = 2 * newly_added_edges;
            int start_id = current_size - newly_added_darts;
            

            // starting from start_id to Darts.size():
            // these darts are a[1] related: same face, same vertex, different edge
            // need to filter out a[0] related darts --> condition: same vertex

            int currentN = (int)Darts.size(); // to use currentN-1 to get the last dart
            for (start_id; start_id != currentN-1; ++start_id) {
                for (int next_id = start_id + 1; next_id != currentN; ++next_id) {
                    //std::cout << start_id << " " << next_id << '\n';
                    if (Darts[start_id].v == Darts[next_id].v) { // two darts are a[1] related

                        Darts[start_id].a[1] = Darts[next_id].id;
                        Darts[next_id].a[1] = Darts[start_id].id;
                    } // end if : vertex ids of two darts are the same
                }

            } // end for: newly added darts in this face

        }// end for: each faces
    }
	
    
    /*function: build Darts Alpha(involutions)
    * NB: the a[3] reamains as _NULL_(-9999)
    * 
    * @parameter:
    * Darts: a vector contains all darts needed
    * NB: Need to use buildDarts() function first
    */
    static void buildDartsAlpha(std::vector<Dart>& Darts) {       
        int N = (int)Darts.size();
        for (int i = 0; i != N - 1; ++i) {
            for (int j = i + 1; j != N; ++j) {
                if ((Darts[i].e == Darts[j].e) && // same edge
                    (Darts[i].v == Darts[j].v)) // same vertex
                {
                    Darts[i].a[2] = Darts[j].id; // a[2] related
                    Darts[j].a[2] = Darts[i].id;
                }
            }
        } // end for: each dart
    }
        
};


class TriangulateGmap {
public:

    
    static int repeateVertexCheck(
        float bx,
        float by,
        float bz,
        std::vector<Vertex>& vertices)
    {
        for (int id = 1; id != vertices.size(); ++id) // id starts from 0
        {
            if ((vertices[id].x == bx) && (vertices[id].y == by) && (vertices[id].z == bz))return id;
        }
        return 0; // 0 indicates no repeated vertex
    }

    
    static void triangulateGmap(
        std::vector<Vertex>& vertices,
        std::vector<Edge>& Edges,
        std::vector<Face>& Faces,
        std::vector<Dart>& Darts,
        std::vector<std::vector<int>>& outputFaces)
    {        
        // for each face in Faces:
        for (auto& face : Faces)
        {
            // for each face
            // dynamically set the edges of this face associated with its vertex order: CCW
            // dynamically --> for each face, need to set this at the first
            int updateEdgeN = (int)face.Face_edge_list.size();
            for (int i = 0; i != updateEdgeN - 1; ++i)
            {
                int Eid = face.Face_edge_list[i]; // current edge id in vector Edges
                int CompareVid = face.Face_vertex_list[i]; // the vertex id compared to the start of the edge

                if (Edges[Eid].start == CompareVid)continue;
                else // if not, swap the start and end of this edge
                {
                    int temp = Edges[Eid].start;
                    Edges[Eid].start = Edges[Eid].end;
                    Edges[Eid].end = temp;
                }
            }

            // update 2: update the last edge
            // the last vertex: vertices[vsize()-1], the last edge: Edges[esize()-1]
            int updateVertexN = (int)face.Face_vertex_list.size();
            int lastEid = face.Face_edge_list[updateEdgeN - 1]; // the edge id of the last edge of this face(CCW)
            int lastVid = face.Face_vertex_list[updateVertexN - 1]; // the vertex id of the last vertex of this face(CCW)

            if (Edges[lastEid].start != lastVid) // swap the start and end
            {
                int temp = Edges[lastEid].start;
                Edges[lastEid].start = Edges[lastEid].end;
                Edges[lastEid].end = temp;
            }
            // update complete for this face
            
            
            // ids:
            // barycenter vertex id of each edge
            std::vector<int> barycenterEachEdge;

            // barycenter vertex id of this face
            int barycenterFace(0);

            // compute the barycenter of each edge
            for (auto& eid : face.Face_edge_list) // for each edge, edge ids are stored in Face_edge_list
            {               
                int vaid = Edges[eid].start; // vertex a id
                int vbid = Edges[eid].end; // vertex b id

                float bx = (float)((vertices[vaid].x + vertices[vbid].x) * 0.5); // barycenter coordinates
                float by = (float)((vertices[vaid].y + vertices[vbid].y) * 0.5);
                float bz = (float)((vertices[vaid].z + vertices[vbid].z) * 0.5);

                // repeate check:
                // if the coordinates(bx, by, bz) is the same as an existed vertex
                // not construct a new vertex

                int repeate_id = repeateVertexCheck(bx, by, bz, vertices);
                if (repeate_id) // repeate_id != 0 --> find repeated vertex
                {
                    barycenterEachEdge.emplace_back(repeate_id);
                }
                else { // no repeated vertex found

                    Vertex v(bx, by, bz);
                    v.id = (int)vertices.size(); // set newly-added vertex's id
                    // ie current vertices: [0,1,2,3,4,5], the vertex v will be the 6-th vertex

                    barycenterEachEdge.emplace_back(v.id); // ad id to the barycenter Each Edge

                    // after setting the vertex's id, add it into the vertices
                    vertices.emplace_back(v);
                } // end else
                
            } // end for: each edge

            // compute the barycenter of this face:
            float accumulate_x(0);
            float accumulate_y(0);
            float accumulate_z(0);
            int bartcenterFace_sum = (int)face.Face_vertex_list.size();
            for (auto& vid : face.Face_vertex_list)
            {
                accumulate_x += vertices[vid].x;
                accumulate_y += vertices[vid].y;
                accumulate_z += vertices[vid].z;
            }

            // the barycenter of a face must be a new vertex
            float bx_face = accumulate_x / bartcenterFace_sum;
            float by_face = accumulate_y / bartcenterFace_sum;
            float bz_face = accumulate_z / bartcenterFace_sum;

            Vertex v_face(bx_face, by_face, bz_face);
            v_face.id = (int)vertices.size();
            vertices.emplace_back(v_face);

            barycenterFace = v_face.id;

            // add indexes 
            // ie: in an OBJ file, f 1 2 3 4 means a face consists of vertex 1, 2, 3, 4
            // for each edge, edge.start, the barycenter of this edge, the barycenter of this face
            // form a triangle(3 vertex ids)
            // n edges match with n edge barycenters, ie the k-th edge corresponds to 
            // the k-th edge barycenter
            // need to make the sequence as CCW
            for (int i = 0; i != face.Face_edge_list.size(); ++i)
            {
                // for each edge in each face
                // one edge matchs with two triangles("darts")

                // triangle 1
                std::vector<int> triangle1;
                int eid = face.Face_edge_list[i]; // edge id of the i-th edge in the Face_edge_list
                int bvid = Edges[eid].start;
                int beid = barycenterEachEdge[i]; // edge barycenter vertex id of the i-th edge

                triangle1.emplace_back(bvid);
                triangle1.emplace_back(beid);
                triangle1.emplace_back(barycenterFace);

                // make the sequence CCW if not
                // maketriangleCCW(triangle1, vertices);

                // add triangle 1 to the output faces
                outputFaces.emplace_back(triangle1);

                // triangle 2
                std::vector<int> triangle2;
                bvid = Edges[eid].end;
                triangle2.emplace_back(barycenterFace); // different sequence from triangle 1
                triangle2.emplace_back(beid);
                triangle2.emplace_back(bvid);

                // add triangle 2 to the output faces
                outputFaces.emplace_back(triangle2);

            } // end for: each edge           

        } // end for: each face

    }
};


// overload functions:

// print vertices
std::ostream& operator<<(std::ostream& os, std::vector<Vertex>& vertices) {
    for (auto& v : vertices)
        os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << '\n';
    return os;
}