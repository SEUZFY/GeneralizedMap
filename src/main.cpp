
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
    BuildGmap::buildEdgeList(&face_list, &edge_list);
    
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
    BuildGmap::facefindEdge(face_list, edge_list, 2, result);
    for (auto& eid : result) {
        std::cout << eid << " ";
    }

    // build dartlist
    std::vector<Dart> dart_list;
    BuildGmap::buildDartList(face_list, edge_list,dart_list);
    Dart d;
    std::cout << '\n';
    std::cout << d.e;


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
