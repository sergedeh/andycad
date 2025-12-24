#include <iostream>
#include "core/vector/CVector.h"
#include "core/aabb/CAABB.h"
#include "core/utils/CRect.hpp"
#include "core/utils/CPoint.hpp"

int main() {
    std::cout << "Testing AndyCAD Core..." << std::endl;

    CPoint p1(10, 20);
    CPoint p2(30, 40);
    CRect rect(p1, p2);

    std::cout << "Rect Width: " << rect.Width() << std::endl;
    std::cout << "Rect Height: " << rect.Height() << std::endl;

    if (rect.PtInRect(CPoint(15, 25))) {
        std::cout << "Point (15, 25) is inside rect." << std::endl;
    } else {
        std::cout << "Point (15, 25) is NOT inside rect." << std::endl;
    }

    CVector v1(1, 2, 3);
    CVector v2(4, 5, 6);
    CVector v3 = v1 + v2;

    std::cout << "Vector addition: " << v3.x << ", " << v3.y << ", " << v3.z << std::endl;

    CAABB aabb;
    aabb.min = v1;
    aabb.max = v2;
    std::cout << "AABB Volume: " << aabb.volume() << std::endl;

    return 0;
}
