
#include "Gmap.hpp"

int main(int argc, char* argv[])
{
    /*
    * to store all the vertices
    * index starts from: 0
    * use index as the id of vertices
    * ie:
    * vertices[i]: the i-th vertex in the G-map
    */
    std::vector<Vertex> vertices; 

    /*
    * to store all face indexes, each face contains multiple vertex id
    * !!!NB!!!: OBJ uses 1-based indexes
    * Identify the vertex: 
    * face: element in vector face_list, type of face: std::vector<int>
    * id: element in vector face, type of id: integer
    * vertices[id-1]: the corresponding vertex
    * use index as the id of faces
    * ie:
    * face_list[i]: the i-th face
    * 
    * Normal vector:
    * the default order of vertex is: CCW(normal vector points to outside)
    */
    std::vector<std::vector<int>> face_list; 

    /*
    * to store all the edge indexes
    * use index as the id of edge
    * !!!NB!!!: OBJ uses 1-based indexes
    * edge: element in vector edge_list, type of edge: std::vector<int>
    * id: element in vector edge, type of id: integer
    * vertices[id-1]: the corresponding vertex
    */
    std::vector<std::vector<int>> edge_list;

    /*
    * face_list and edge_list are used to map the vertices, indicating
    * to find the vertex in the vertices according to face id or edge id
    */

    ReadOBJ::readobj(DATA_PATH, "/cube.obj", &vertices, &face_list);
    BuildGmapDependency::buildEdgeList(&face_list, &edge_list);

    /*
    * vertices: contains all vertex, index is the id of vertex
    (0, 0, 0)
    (1, 1, -1) // index: 1, vertex id: 1
    (1, -1, -1) // index: 2, vertex id: 2
    (1, 1, 1)
    (1, -1, 1)
    (-1, 1, -1)
    (-1, -1, -1)
    (-1, 1, 1)
    (-1, -1, 1) // index: 8, vertex id: 8

    * face_list: face id = index
    1573 // face id: 0
    4378 // face id: 1
    8756
    6248
    2134
    6512 // face id: 5

    * edge list: edge id = index
    1 5 // edge id: 0
    5 7 // edge id: 1
    7 3
    3 1
    4 3
    7 8
    8 4
    5 6
    6 8
    6 2
    2 4
    2 1 // edge id: 11
    * edge_list
    */
    
    // test the read

    // test vertices
    std::cout << vertices;

    // test face-index
    for (auto& f : face_list) {
        for (auto& id : f) {
            std::cout << id;
        }
        std::cout << '\n';
    }

    // test edge list
    std::cout <<"edge list size: " << edge_list.size() << '\n';
    for (auto& e : edge_list) {
        std::cout << e[0] << " " << e[1] << '\n';
    }

    // test findEdge()
    std::vector<int> result;
    BuildGmapDependency::facefindEdge(face_list, edge_list, 2, result);
    for (auto& eid : result) {
        std::cout << eid << " ";
    }
    std::cout << '\n';

    /*
    * Build Gmap
    */
    std::cout << "Building faces..." << '\n';
    std::vector<Face> Faces;
    BuildGmap::buildFaces(face_list, edge_list, Faces);
    std::cout << "Face numbers: "<<Faces.size() << '\n';
    for (auto& f : Faces) {
        for (auto& eid : f.Face_edge_list) {
            std::cout<< edge_list[eid][0] << edge_list[eid][1]<<" ";
        }
        std::cout << '\n';
    }
    /*
    * edge_list:
    * one edge id maps two vertex ids, but the order won't be assured the same as origin
    * ie, (7 8) and (8 7) is the same edge
    * 
    * Origin:
    1573 // face id: 0
    4378 // face id: 1, it contains an edge: (7 8) --> the same edge
    8756 // face id: 2, it contains an edge: (8 7) --> the same edge
    6248
    2134
    6512 // face id: 5
    * 
    * output:
    15 57 73 31 // face id: 0
    43 73 78 84
    78 57 56 68
    62 24 84 68
    21 31 43 24
    56 15 21 62 // face id: 5
    */
 
        

    // build dartlist
    /*std::vector<Dart> dart_list;
    BuildGmap::buildDartList(face_list, edge_list,dart_list);
    Dart d;
    std::cout << '\n';
    std::cout << d.e;*/


    // test Dart
    //Dart d;
    //Dart d1;

    //d1.id() = 2;
    //d.set_incident_cell(0, 25);
    //d.set_involution_to_dart(0, &d1); // a0 -> d1
    //d.print_involution(0);

    // test vertex
    // Vertex v(1,2,3);
    // v.print();
    // std::cout << v.id();
    
    


    // ## Construct generalised map using the structures from Gmap.h ##

    // ## Output generalised map to CSV ##

    // ## Create triangles from the darts ##

    // ## Write triangles to obj ##

    return 0;

}
