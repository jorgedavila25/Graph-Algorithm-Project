//
//  main.cpp
//  Assignment5
//
//  Created by Jorge Davila


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <queue>
#include "dijkstra.h"
#include "Vertex.h"

using namespace std;

bool openFile(char*, ifstream&);

void parseFile(ifstream&, vector<Vertex>&, Vertex[],float&);

int main(int argc,char * argv[])
{
    ifstream graphFile;//create an object to hold the file
    vector<Vertex> graph; //represent the graph in a vector of Vertex's
    vector<Vertex> maxGraph;//will be used to do the longest path
    Vertex vertices[10];//arbitrary large number
    string decisionForDijkstra;
    int initialVertex;
    float numberOfVerticesInGraph;
    graphMani max;
    graphMani dij;

    if (argc != 2){
        cout << "You did not enter a file:./exe Graph.txt \n";
        cout << "The program will terminate, please try again. \n";
        return 0;
    }

    if(!openFile(argv[1], graphFile)){
        cout << "There was an error opening the file \n";
        cout << "The program will terminate. \n";
        return 0;
    }

    if(graphFile.is_open())
        parseFile(graphFile, graph, vertices,numberOfVerticesInGraph);
    else
        cout << "can't parse" << endl;

    maxGraph = graph;//copy the graph so it can be manipulated again for other parts of the program


    cout << endl;
    cout << "* " << endl;
    cout << "***    THIS IS YOUR GRAPH ***" << endl;
    cout << "* " << endl;
    cout << "These are the # of Vertices in the graph: " << graph.size()<< endl;

    for (int i = 0; i < graph.size() ; i++){
        cout << "Vertex " <<i<<" contains these adjacent vertices:";
        for (int j = 0; j < graph[i].adjacentVertices.size(); j++){
            cout << graph[i].adjacentVertices[j] << " ";
        }
        cout << endl;

        cout << "Vertex "<< i <<" contains these weights:";
        for (int j = 0; j < graph[i].weight.size(); j++){
            cout << graph[i].weight[j] << " ";
        }
        cout << endl;
    }

    string userWantsToDoAgain;
    bool userWantsToDoAgainBool;
    userWantsToDoAgainBool = true;
    bool cantGetItSraight;
    cantGetItSraight = false;
    cout << "Would you like to run the Dijkstra Algo on the Graph we just created? (Y/N) ";
    cin >> decisionForDijkstra;
    if((decisionForDijkstra == "y")||(decisionForDijkstra == "Y")){
        cout <<"Please enter the vertex you wish to start on: ";
        cout <<"(Please choose a number from 0 to " << graph.size()-1 << " ) ";
        cin >> initialVertex;
        do{
            if((initialVertex > graph.size()-1)||(initialVertex < 0)){
                cout << "Please try to enter a valid number: ";
                cin >>initialVertex;
                cantGetItSraight = true;
            }else{
                dij.dijkstraAlgo(graph,initialVertex);
                cout <<"This is the amount of operations it took for the algorithm to work: ";
                cout << dij.numberOfOperationsItTook() << endl;
                cantGetItSraight = false;
            }
        }while(cantGetItSraight == true);



        while(userWantsToDoAgainBool == true){
            float shortestPath;
            cout <<"Please enter the Vertex in which you want to find the shortest path to: "<<endl;
            cout <<"(Please choose a number from 0 to " << graph.size()-1 << " )";
            cin >> shortestPath;
            do{
                if((shortestPath > graph.size()-1)||(shortestPath < 0)){
                    cout <<"Please try to enter a valid number: ";
                    cin >> shortestPath;
                    cantGetItSraight = true;
                }else {
                    cantGetItSraight = false;
                }
            }while (cantGetItSraight == true);
            cout <<"The Shortest Path is: " << endl;
            dij.printPath(shortestPath, graph, initialVertex, 0);
            cout << "Would you like to find the shortest path of another vertice?(Y/N) ";
            cin>> userWantsToDoAgain;
            if((userWantsToDoAgain == "y")||(userWantsToDoAgain == "Y"))
                userWantsToDoAgainBool = true;
            else
                userWantsToDoAgainBool = false;

        }


    }else {
        cout << "You decided to skip the Dijkstra Algo" << endl;
        cout << "Compile the program again if you skipped it by mistake" << endl;
    }

    cout << endl;
    cout <<"Part C, Longest Path" << endl;

    /*
     * Set all of the weights to a negative number
     */

    for (int i = 0; i < maxGraph.size() ; i++)
        for (int j = 0; j < maxGraph[i].weight.size(); j++)
            maxGraph[i].weight[j]*= -1;

    int vertexA,vertexB;
    cout <<"Please enter Vertex A and Vertex B, in which you wish to find the longest path from A to B " << endl;
    cout <<"Vertex A: ";
    cin >> vertexA;
    cout <<"Vetex B: ";
    cin>> vertexB;
    max.dijkstraAlgo(maxGraph, vertexA);
    cout <<"Took this many operations to run the algorithm: ";
    cout << max.numberOfOperationsItTook() << endl;
    cout <<"The Longest Path is:"<<endl;
    max.printPath(vertexB,maxGraph, vertexA, 1);
    return 0;
}
bool openFile(char* document, ifstream &fileObject){

    fileObject.open(document);
    if (fileObject.is_open())
        return true;
    else
        return false;
}

void parseFile(ifstream& fileObject, vector<Vertex> &graph, Vertex vertices[],float &numberOfVertex){
    string number;
    int lineCounter = 1;
    int initialLineCounter = 1;
    int miniCounter = 1;
    int currentIndex = 0;
    int adjacentOrWeightCounter = 0;
    int i = 0;
    while(fileObject){//while the document has data to read

        if (initialLineCounter == 1){
            getline(fileObject, number);
            numberOfVertex = ::atof(number.c_str());
        }else{
            getline(fileObject, number, ' ');
            float intNumber = ::atof(number.c_str());

            if (intNumber == -1){
                vertices[currentIndex].index = i;
                graph.push_back(vertices[currentIndex]);//push each Node back to the vector
                i++;
                lineCounter++;
                miniCounter = 1;
            }else{
                if(miniCounter == 1){
                    currentIndex = intNumber;
                    miniCounter++;

                }else{
                    if( adjacentOrWeightCounter % 2 != 0){
                        vertices[currentIndex].weight.push_back(intNumber);// storing the weight
                        adjacentOrWeightCounter++;
                    }else {
                        vertices[currentIndex].adjacentVertices.push_back(intNumber);// storing the adjacent vertices
                        adjacentOrWeightCounter++;
                    }
                }

            }
        }
        initialLineCounter = 0;
    }
}
