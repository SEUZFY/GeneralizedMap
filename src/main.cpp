
#include "Gmap.h"

int main(int argc, char* argv[])
{

    // Example how to read vertices from an obj file :
    std::vector<Vertex> vertices;
    std::vector<std::vector<int>> face_vertex_index;
    ReadOBJ::readobj(DATA_PATH, "/cube.obj", &vertices, &face_vertex_index);


    // test the read

    // test vertices
    for (auto& v : vertices) {
        v.print();
        std::cout << '\n';
    }

    // test face-index
    for (auto& f : face_vertex_index) {
        for (auto& id : f) {
            std::cout << id;
        }
        std::cout << '\n';
    }

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
