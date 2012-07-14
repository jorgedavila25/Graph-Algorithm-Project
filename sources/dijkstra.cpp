//
//  dijkstra.cpp
//  graphAlgorithm
//
//  Created by Jorge Davila

#include <iostream>

#include <list>
#include <stack>
#include "dijkstra.h"
#define INFINITY 1000
using namespace std;


    graphMani::graphMani()
    {
        numberOfOperations = 0;
    }
    void graphMani::dijkstraAlgo(vector<Vertex> & graph, int initialVertex ){

        LeftistHeap<float> priorityQueue;//priority queue
        int index;

        for(int i = 0; i < graph.size(); i++){
            this->numberOfOperations++;//keep track of the times it looped
            if(i != initialVertex){
                this->numberOfOperations++;
                graph[i].distance = INFINITY;// setting them all to infinity
                graph[i].known = false; // set every vertices to false that's not the starting vertex
            }
        }

        graph[initialVertex].known = false;//must set this false first
        graph[initialVertex].path = 0;
        graph[initialVertex].distance = 0; // set the starting vertex distance to zero

        priorityQueue.customInsert(graph[initialVertex],initialVertex);

        for (;;){
            bool success = false;
            this->numberOfOperations++;
            while((!priorityQueue.isEmpty()) && (!success)){
                this->numberOfOperations++;
                index = (int)priorityQueue.findMin();
                priorityQueue.deleteMin();

                if(!graph[index].known){
                    this->numberOfOperations++;
                    success = true;
                }

            }
            if(!success){
                this->numberOfOperations++;
                break;
            }

            graph[index].known = true;
            for(int i = 0; i <graph[index].adjacentVertices.size(); i++)//for all Vertex adjacent to current vertex
            {
                this->numberOfOperations++;
                if(graph[index].distance + graph[index].weight[i]< graph[graph[index].adjacentVertices[i]].distance)
                {
                    this->numberOfOperations++;
                    int tempIndex = (int)graph[graph[index].adjacentVertices[i]].index; // get the numerical index of where the vertex is stored

                    graph[graph[index].adjacentVertices[i]].distance = graph[index].distance + graph[index].weight[i];//w.dist = v.dist+cvw
                    priorityQueue.customInsert(graph[graph[index].adjacentVertices[i]],tempIndex ); //P.insert(w)
                    graph[graph[index].adjacentVertices[i]].path = index; // w.path = v
                }
            }
        }
        priorityQueue.makeEmpty();

    }
    void graphMani::printPath(float s, vector<Vertex> graph, int initialVertex, int code){
        stack<int> rightOrder;
        float finalDestination = s;


        if(graph[s].distance != INFINITY){
            rightOrder.push(s);
            while(s != initialVertex){
                rightOrder.push(graph[s].path);
                s = graph[s].path;
            }

            cout <<"Vertex ";
            cout << rightOrder.top();
            while (!rightOrder.empty())
            {
                if(rightOrder.size() != 1)
                    cout <<" to Vertex ";
                rightOrder.pop();
                if(!rightOrder.empty())
                    cout << rightOrder.top() << " ";
            }
            if(code == 0)
                cout << "\nThe Total Cost is: " << graph[finalDestination].distance << endl;
            else
                cout <<"\nThe Total Cost is: " << graph[finalDestination].distance * -1 << endl;

        }else
            cout << "Not possible, these two vertices do not connect starting from " << initialVertex << endl;

    }
