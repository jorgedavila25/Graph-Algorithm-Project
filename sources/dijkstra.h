//
//  dijkstra.h
//  graphAlgorithm
//
//  Created by Jorge Davila

#ifndef graphAlgorithm_dijkstra_h
#define graphAlgorithm_dijkstra_h

#include "Vertex.h"
#include "LeftistHeap.h"
#include <iostream>

using namespace std;


    class graphMani{

    public:
        graphMani();
        void dijkstraAlgo(vector<Vertex> &,int);
        void printPath(float, vector<Vertex>, int,int);
        int numberOfOperationsItTook(){return this->numberOfOperations;};
    private:
        int numberOfOperations;

    };


#endif
