// some standard libraries that are helpfull for reading/writing text files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Gmap.h"

int main(int argc, char* argv[])
{

    // Example how to read vertices from an obj file :
    std::string filename = "/cube.obj"; // could read from the main() parameters
    std::string file_in = DATA_PATH + filename;

    std::ifstream stream_in;
    stream_in.open(file_in);
    std::vector<Vertex> vertices;

    if (stream_in.is_open()) {
        std::string line;
        while (getline(stream_in, line)) {
            std::istringstream iss(line);
            std::string word;
            iss >> word;
            if (word == "v") {
                std::vector<float> coordinates;
                while (iss >> word) coordinates.emplace_back(std::stof(word));
                if (coordinates.size() == 3) vertices.emplace_back(coordinates[0], coordinates[1], coordinates[2]);
                else vertices.emplace_back(Vertex());
            }
        }
    }

    // test the read
    for (auto& v : vertices)v.print();


    // ## Construct generalised map using the structures from Gmap.h ##

    // ## Output generalised map to CSV ##

    // ## Create triangles from the darts ##

    // ## Write triangles to obj ##

    return 0;

}
