//
//  graph.hpp
//  project5
//
//  Created by Cory Milsap on 4/24/19.
//  Copyright © 2019 Cory Milsap. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class path {
public:
    void addToPath(int v, int c, int d);
    bool isPathEmpty() {
        if (getCost() == 0 && getDuration() == 0) return true;
        return false;
    }
    int getCost() {
        int sum = 0;
        for (int i = 0; i < size; i++)
            sum += c[i];
        return sum;
    }
    int getDuration() {
        int sum = 0;
        for (int i = 0; i < size; i++)
            sum += d[i];
        return sum;
    }
    void removeLast() {
        size--;
        if (size == capacity / 4) {
            capacity /= 2;
            int *tV = new int[capacity];
            int *tC = new int[capacity];
            int *tD = new int[capacity];
            for (int i = 0; i < size; i++) {
                tV[i] = vID[i];
                tC[i] = c[i];
                tD[i] = d[i];
            }
            delete [] vID; delete [] c; delete [] d;
            vID = tV; c = tC; d = tD;
        }
    }
    void print() {
        cout << "Cost " << getCost() << " Duration " << getDuration() << endl << "Path ";
        for (int i = 0; i < size - 1; i++)
            cout << *(vID + i) << ", ";
        cout << vID[size - 1] << endl;
    }
    path() {
        size = 0;
        capacity = 2;
        vID = new int[capacity]; c = new int[capacity]; d = new int[capacity];
    }
    path(int vCount) {
        size = 0;
        capacity = vCount;
        vID = new int[vCount];
        c = new int[vCount]; d = new int[vCount];
        for (int i = 0; i < vCount; i++) {
            vID[i] = -1;
            c[i] = 0; d[i] = 0;
        }
    }
    ~path() {
        delete [] vID;
        delete [] c;
        delete [] d;
    }
    path& operator=(const path& src) {
        size = src.size; capacity = src.capacity;
        vID = new int[capacity];
        c = new int[capacity];
        d = new int[capacity];
        for (int i = 0; i < size; i++) {
            vID[i] = src.vID[i];
            c[i] = src.c[i];
            d[i] = src.d[i];
        }
        return *this;
    }
    path(const path& src) { *this = src; }
    
private:
    int *vID, *c, *d;
    int capacity, size;
};

class vertex;
class edge {
public:
    vertex *getDest() { return destination; }
    void printEdge();
    int getCost() { return cost; }
    int getDuration() { return duration; }
    void createEdge(vertex *s, vertex *dest, int c, int d);
    vertex *getSource() { return source; }
    edge() {
        cost = -1; duration = -1;
        source = nullptr;
        destination = nullptr;
    }
    bool operator==(const edge &src) const {
        if (cost == src.cost && duration == src.duration) return true;
        return false;
    }
    
private:
    int cost, duration;
    vertex *source, *destination;
};

class vertex {
public:
    void createVertex(int ID);
    void createLink(vertex *target, int cost, int duration);
    
    int getID() { return ID; }
    int getSize() { return eCount; }

    void print();
    void addEdge(edge e);
    
    vertex(int i) {
        capacity = 2;
        eCount = 0; aList = new edge[capacity];
        ID = i;
    }
    vertex() {
        eCount = 0; ID = -1; capacity = 2;
        aList = new edge[capacity];
    }
    vertex& operator=(const vertex& src) {
        eCount = src.eCount; ID = src.ID;
        capacity = src.capacity;
        aList = new edge[capacity];
        for (int i = 0; i < eCount; i++)
            aList[i] = src.aList[i];
        return *this;
    }
    vertex(const vertex& src) { *this = src; }
    ~vertex() {
        delete [] aList;
    }
    edge& operator[](int i) { return *(aList + i); }
private:
    int eCount, ID, capacity;
    edge* aList; // list of all adjacent edges
    
};

class graph {
public:
    void createGraph(string filename, int maxCost);
    vertex initializeV(int ID);
    int getvCount() { return vCount; }
    void print();
    void createLink(int start, int end, int cost, int duration);
    graph() {
        capacity = pCap = 2;
        eCount = vCount = pSize = size = 0;
        adjacencyList = new vertex[capacity];
        routes = new path[pCap];
        maxCost = 0;
    }
    ~graph() {
        delete [] routes;
        delete [] adjacencyList;
    }
    graph& operator=(const graph& src) {
        eCount = src.eCount; vCount = src.vCount; size = src.size; capacity = src.capacity;
        pCap = src.pCap; pSize = src.pSize;
        maxCost = src.maxCost;
        adjacencyList = new vertex[capacity];
        routes = new path[pCap];
        for (int i = 0; i < vCount; i++) {
            adjacencyList[i] = src.adjacencyList[i];
        }
        return *this;
    }
    graph(const graph& src) { *this = src; }
    vertex& operator[](int i) { return *(adjacencyList + i); }
    void DFS(int startingVertex, int searchVertex);
    void addToList(vertex v);
    void addRoute(path p);
    void findBestRoute();
    void DFSHelp(int cur, int dest, bool visitedSet[], path *p, int cost = 0, int dur = 0);
    void printRoutes();
    
private:
    int eCount, vCount, size, capacity;
    int maxCost;
    vertex* adjacencyList;
    path* routes;
    int pCap, pSize;
    void DFSHelp(int vertex, bool visitedSet[]);
};

#endif /* graph_hpp */
