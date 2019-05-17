//
//  main.cpp
//  project5
//
//  Created by Cory Milsap on 4/24/19.
//  Copyright © 2019 Cory Milsap. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "graph.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    graph a;
    string filename = argv[1];
    int startID = atoi(argv[2]);
    int endID = atoi(argv[3]);
    int maxCost = atoi(argv[4]);
    a.createGraph(filename, maxCost);
    a.DFS(startID, endID);
    //a.printRoutes();
    a.findBestRoute();
    
    return 0;
}
