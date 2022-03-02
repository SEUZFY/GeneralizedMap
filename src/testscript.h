#pragma once

// in the main.cpp:

//std::ios::sync_with_stdio(false); // speed up for std::cin and std::cout

// test vertices
    /*std::cout << "Reading... --------------------------------------------------" << '\n';
    std::cout << "***************** vertices *****************: " << '\n';
    std::cout << vertices;*/

    // test face-index
    /*std::cout << "***************** face-vertex index *****************: " << '\n';
    for (auto& f : face_list) {
        for (auto& id : f) {
            std::cout << id;
        }
        std::cout << '\n';
    }
    std::cout << "End Reading... --------------------------------------------------" << '\n';
    std::cout << '\n';*/

    // test edge list
    /*std::cout << "***************** edge list *****************" << '\n';
    std::cout <<"edge list size: " << edge_list.size() << '\n';
    for (auto& e : edge_list) {
        std::cout << "edge id: " << (&e - &edge_list[0]) << " " << "Vertex id: " << " "
            << e[0] << " " << e[1] << '\n';
    }
    std::cout << '\n';*/

    /*
    * Build Gmap
    */
    //std::cout << "Building gmap... --------------------------------------------------" << '\n';

    //std::cout << '\n';

    //// test Faces
    //std::cout << "Building faces..." << '\n';
    //
    //std::vector<Face> Faces;
    //BuildGmap::buildFaces(face_list, edge_list, Faces);
    //std::cout << "Face numbers: "<<Faces.size() << '\n';
    //std::cout << '\n';

    //for (auto& f : Faces) {
    //    std::cout << "face id: " << (&f - &Faces[0]) << " " << "edge id: ";
    //    for (auto& eid : f.Face_edge_list) {
    //        std::cout << eid << " ";
    //    }
    //    std::cout << '\n';
    //}
    //std::cout << '\n';
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
    // face id: 0, stands for 4 edges, starting from vertex 1, oriented CCW
    Building Edges...
    id: 0 15
    id: 1 57
    id: 2 73
    id: 3 31
    id: 4 43
    id: 5 78
    id: 6 84
    id: 7 56
    id: 8 68
    id: 9 62
    id: 10 24
    id: 11 21

    Face numbers: 6
    0 1 2 3 // face id: 0, edges contained: Edges[0], Edges[1], Edges[2], Edges[3], CCW
    4 2 5 6
    5 1 7 8
    9 10 6 8
    11 3 4 10
    7 0 11 9
    */

    // test Edges
    /*std::cout << "Building Edges..." << '\n';
    std::vector<Edge> Edges;
    BuildGmap::buildEdges(edge_list, Edges);
    for (auto& e : Edges) {
        std::cout << "id: " << e.id << " " << "vertex id: " << e.start <<" "<< e.end << '\n';
    }
    std::cout << '\n';*/

    // test Darts
    /*std::cout << "Building Darts..." << '\n';
    std::vector<Dart> Darts;
    BuildGmap::buildDarts(vertices, Faces, Edges, Darts);
    std::cout << "Dart numbers: " << Darts.size() << '\n';

    std::cout << '\n';
    std::cout << "Building Darts Alpha..." << '\n';
    BuildGmap::buildDartsAlpha(Darts);

    for (auto& d : Darts) {
        std::cout << "id: " << d.id << " " << "a[2]: " << d.a[2] << '\n';
    }
    std::cout << '\n';

    std::cout << "Vertex - incident dart: " << '\n';
    for (auto& v : vertices) {
        std::cout << "Vertex id: " << v.id << " " << "incident dart: " << v.Vertex_dart << '\n';
    }
    std::cout << '\n';

    std::cout << "Faces - darts: " << '\n';
    for (int i = 0; i != Faces.size(); ++i)
    {
        std::cout << "face id: " << Faces[i].id << '\n';
        std::cout << "contains darts: " << '\n';
        for (auto& d : Faces[i].Face_dart_list)
        {
            std::cout << d << " ";
        }
        std::cout << '\n';
        std::cout << '\n';
    }*/


    // test triangulate gmap
    //std::cout << "triangulate gmap..." << '\n';
    //std::vector<std::vector<int>> outputFaces;
    //
    //TriangulateGmap::triangulateGmap(vertices, Edges, Faces, Darts, outputFaces);
    //
    //// output vertices
    //std::cout << "output OBJ: " << '\n';
    //for (int i=1; i < vertices.size(); ++i)
    //{
    //    std::cout << "v" << " " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << '\n';
    //}
    //for (auto& tri : outputFaces)
    //{
    //    std::cout << "f" << " " << tri[0] << " " << tri[1] << " " << tri[2] << '\n';
    //}