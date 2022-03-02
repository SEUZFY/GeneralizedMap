
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


    /*
    * Read in files
    */
    std::cout << "Reading... --------------------------------------------------" << '\n';
    ReadOBJ::readobj(DATA_PATH, "/torus.obj", vertices, face_list);
    std::cout << "End reading... --------------------------------------------------" << '\n';
    std::cout << '\n'; 


    /*
    * Build gmap denpendency
    */
    std::cout << "Building gmap denpendency... --------------------------------------------------" << '\n';
    BuildGmapDependency::buildEdgeList(&face_list, &edge_list);
    std::cout << "End building gmap denpendency... --------------------------------------------------" << '\n';
    std::cout << '\n';


    /*
    * Build gmap
    */
    std::cout << "Building gmap... --------------------------------------------------" << '\n';

    std::cout << "Building Edges..." << '\n';
    std::vector<Edge> Edges;
    BuildGmap::buildEdges(edge_list, Edges);
    std::cout << "done" << '\n';

    std::cout << "Building Faces..." << '\n';
    std::vector<Face> Faces;
    BuildGmap::buildFaces(face_list, edge_list, Faces);
    std::cout << "done" << '\n';

    std::cout << "Building Darts..." << '\n';
    std::vector<Dart> Darts;
    BuildGmap::buildDarts(vertices, Faces, Edges, Darts);
    std::cout << "done" << '\n';

    std::cout << "Building Darts Alpha..." << '\n';
    BuildGmap::buildDartsAlpha(Darts);
    std::cout << "done" << '\n';

    std::cout << "End building gmap... --------------------------------------------------" << '\n';
    std::cout << '\n';


    /*
    * Write files
    */
    std::cout << "Write gmap... --------------------------------------------------" << '\n';

    std::cout << "Write darts..." << '\n';
    WriteFiles::writeDarts(Darts);
    std::cout << "done" << '\n';

    std::cout << "Write vertices..." << '\n';
    WriteFiles::writeVertices(vertices);
    std::cout << "done" << '\n';
    

    /*
    * Triangulate gmap
    */
    std::cout << "Triangulate gmap... --------------------------------------------------" << '\n';
    std::vector<std::vector<int>> outputFaces;   
    TriangulateGmap::triangulateGmap(vertices, Edges, Faces, Darts, outputFaces);
    std::cout << "End triangulating gmap... --------------------------------------------------" << '\n';
    std::cout << '\n';

        
    


    // ## Construct generalised map using the structures from Gmap.h ##

    // ## Output generalised map to CSV ##

    // ## Create triangles from the darts ##

    // ## Write triangles to obj ##

    return 0;

}