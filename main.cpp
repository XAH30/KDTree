#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

#include "PointStruct.cpp"
#include "NodeStruct.cpp"

#include "KDTree.h"
#include "KDTreeFunctions.cpp"


int main() {
    std::vector<Point> points = {
        { {2, 3, 1, 1, 1, 1, 1, 1, 1, 1} },
        { {5, 7, 12, 2, 2, 2, 2, 2, 2, 2} },
        { {5, 5, 11, 5, 5, 5, 5, 5, 5, 5} },
        { {9, 6, 10, 9, 9, 9, 9, 9, 9, 9} },
        { {90, 60, 90, 6, 6, 6, 6, 6, 6} },
        { {4, 7, 3, 4, 4, 4, 4, 4, 4, 4} },
        { {8, 1, 12, 8, 8, 8, 8, 8, 8, 8} },
        { {7, 2, 6, 7, 7, 7, 7, 7, 7, 7} }
    };

    KDTree kdTree;
    for (const auto& point : points) {
        kdTree.insert(point);
    }

    Point queryPoint = { {90, 0, 0, 9, 9, 9, 9, 9, 9, 9} }; // если размерность queryPoint меньше point, то все остальные координаты считаются 0 и наоборот
    Point nearestNeighbor = kdTree.findNearestNeighbor(queryPoint);
    
    std::cout << "Nearest neighbor coordinates for { ";
    
    for (const auto& coordinate : queryPoint.coordinates) {
        std::cout << coordinate << " , ";
    }
    
    std::cout << "\b\b} : { ";
    
    for (const auto& coordinate : nearestNeighbor.coordinates) {
        std::cout << coordinate << " , ";
    }
    std::cout << "\b\b}" << std::endl;

    return 0;
}
