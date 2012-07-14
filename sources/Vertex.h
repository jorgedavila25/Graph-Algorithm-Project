//
//  Vertex.h
//
//  Created by Jorge Davila


#ifndef Assignment5_Vertex_h
#define Assignment5_Vertex_h

#include <iostream>
#include <list>
#include <vector>


using namespace std;

struct Vertex {
    vector<float> weight;
    vector<float> adjacentVertices;
    bool known;
    float distance;//dv - distance between s to v using known vertices
    float path;//last vertex to change dv
    int index;
};

#endif
