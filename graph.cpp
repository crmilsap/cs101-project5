//
//  graph.cpp
//  project5
//
//  Created by Cory Milsap on 4/24/19.
//  Copyright © 2019 Cory Milsap. All rights reserved.
//

#include "graph.hpp"

void graph::createGraph(string filename, int c) {
    ifstream inFile(filename);
    if (!inFile.is_open())
        cout << "Unable to open " << filename << " for input." << endl;
    
    int tStart, tEnd, tCost, tDuration;
    maxCost = c;
    
    inFile >> vCount;
    inFile >> eCount;
    
    for (int i = 0; i < vCount; i++)
        initializeV(i);
    
    while (inFile >> tStart) {
        inFile >> tEnd;
        inFile >> tCost;
        inFile >> tDuration;
        createLink(tStart, tEnd, tCost, tDuration);
    }
    
}

vertex graph::initializeV(int ID) {
    vertex v(ID);
    addToList(v);
    
    return v;
}

void graph::addToList(vertex v) {
    if (size == capacity) { //array is full
        capacity *= 2;
        vertex *temp = new vertex[capacity];
        for (int i = 0; i < size; i++) temp[i] = adjacencyList[i];
        delete[] adjacencyList;
        adjacencyList = temp;
    }
    adjacencyList[size] = v;
    size++;
}

void graph::print() {
    for (int i = 0; i < size; i++) {
        adjacencyList[i].print();
        
    }
}

void graph::createLink(int start, int end, int cost, int duration) {
    adjacencyList[start].createLink(&adjacencyList[end], cost, duration);
}

void vertex::createLink(vertex *target, int cost, int duration) {
    edge e;
    e.createEdge(this, target, cost, duration);
    addEdge(e);
}

void vertex::addEdge(edge e) {
    if (eCount == capacity) {
        capacity *= 2;
        edge* temp = new edge[capacity];
        for (int i = 0; i < eCount; i++) temp[i] = aList[i];
        delete[] aList;
        aList = temp;
    }
    aList[eCount] = e;
    eCount++;
}

void edge::createEdge(vertex *s, vertex *dest, int c, int d) {
    source = s;
    destination = dest;
    cost = c;
    duration = d;
}

void vertex::print() {
    cout << ID;
    for (int i = 0; i < eCount; i++) {
        cout << " -> " << (aList[i].getDest())->getID() << "(C: " << aList[i].getCost() << " D: " << aList[i].getDuration() << ")";
    }
    cout << endl;
}

void graph::DFS(int startingVertex, int searchVertex) {
    bool *visited = new bool[vCount];
    path *p = new path;
    
    for (int i = 0; i < vCount; i++) visited[i] = false;
    
    DFSHelp(startingVertex, searchVertex, visited, p);
    
    delete p;
    /*
    if (startingVertex == searchVertex) {
        addRoute(p);
        return;
    }
    else if (count >= vCount || p.getCost() > maxCost) {
        return;
    }
    else {
        for (int i = 0; i < adjacencyList[startingVertex].getSize(); i++) {
            id = adjacencyList[startingVertex][i].getDest()->getID();
            c = adjacencyList[startingVertex][i].getCost();
            d = adjacencyList[startingVertex][i].getDuration();
            count++;
            p.addToPath(id, c, d);
            DFS(id, searchVertex, p, count);
        }
    }*/
}

void graph::DFSHelp(int cur, int dest, bool visitedSet[], path *p, int cost, int dur) {
    int id, c, d;
    
    //FIXME cout << "Calling DFSHelp(" << cur << ", " << dest << ", " << cost << ", " << dur << endl;
    visitedSet[cur] = true;
    p->addToPath(cur, cost, dur);
    //FIXME cout << "Adding cur: " << cur << " cost: " << cost << " dur: " << dur << " to path." << endl << "Printing updated path.";
    //FIXME p->print();
    if (cur == dest && !p->isPathEmpty()) {
        //p->print();
        addRoute(*p);
    }
    else {
        
        for (int i = 0; i < adjacencyList[cur].getSize(); i++) {
            id = adjacencyList[cur][i].getDest()->getID();
            c = adjacencyList[cur][i].getCost();
            d = adjacencyList[cur][i].getDuration();
            //FIXEME cout << "Adjacent vertices to " << cur << " are: " << id << endl;
            if (!visitedSet[id])
                DFSHelp(id, dest, visitedSet, p, c, d);
        }
    }
    visitedSet[cur] = false;
    p->removeLast();
}

void path::addToPath(int v, int cost, int dur) {
    if (size == capacity) {
        capacity *= 2;
        int *tV = new int[capacity];
        int *tC = new int[capacity];
        int *tD = new int[capacity];
        for (int i = 0; i < size; i++) {
            tV[i] = vID[i];
            tC[i] = c[i];
            tD[i] = d[i];
        }
        delete [] vID;
        delete [] c;
        delete [] d;
        vID = tV; c = tC; d = tD;
    }
    vID[size] = v;
    c[size] = cost;
    d[size] = dur;
    size++;
}

void graph::addRoute(path p) {
    if (pSize == pCap) {
        pCap *= 2;
        path* temp = new path[pCap];
        for (int i = 0; i < pSize; i++) temp[i] = routes[i];
        delete [] routes;
        routes = temp;
    }
    routes[pSize] = p;
    pSize++;
}

void graph::findBestRoute() {
    path a;
    bool pathFound = false;
    int bestDur = 200000;
    for (int i = 0; i < pSize; i++) {
        int curCost = routes[i].getCost();
        int curDur = routes[i].getDuration();
        if (curCost <= maxCost && curDur < bestDur) {
            a = routes[i];
            bestDur = a.getDuration();
            pathFound = true;
        }
    }
    if (pathFound == true) a.print();
    else cout << "No path" << endl;
}

void graph::printRoutes() {
    cout << "Printing routes" << endl;
    for (int i = 0; i < pSize; i++) routes[i].print();
}
