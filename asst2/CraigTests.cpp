#include "CraigTests.h"

#include "EuclideanVector.h"
#include "util.h"

#include <algorithm>
#include <cassert>
#include <vector>
#include <array>

void craig_tests() {
    // Test EuclideanVector with STL containers
    
    // Try sorting a vector of EuclideanVectors
    {
        std::vector<evec::EuclideanVector> vectors;
        vectors.emplace_back(4, 3.0);
        vectors.emplace_back(2, 5.0);
        vectors.emplace_back(3, 4.0);
        vectors.emplace_back(1, 6.0);

        std::sort(vectors.begin(), vectors.end(), 
                  [](const evec::EuclideanVector& lhs, 
                     const evec::EuclideanVector& rhs) {
                        return lhs.get(0) < rhs.get(0);
                     });

        assert((vectors[0] == evec::EuclideanVector{3.0, 3.0, 3.0, 3.0}));
        assert((vectors[1] == evec::EuclideanVector{4.0, 4.0, 4.0}));
        assert((vectors[2] == evec::EuclideanVector{5.0, 5.0}));
        assert((vectors[3] == evec::EuclideanVector{6.0}));
    }

    // Initialilse a vector with empty EuclideanVectors
    {
        std::vector<evec::EuclideanVector> matrix;
        matrix.resize(3);
        std::fill(matrix.begin(), matrix.end(), evec::EuclideanVector(3));
        
        assert((matrix[0] == evec::EuclideanVector{0.0, 0.0, 0.0}));
        assert((matrix[1] == evec::EuclideanVector{0.0, 0.0, 0.0}));
        assert((matrix[2] == evec::EuclideanVector{0.0, 0.0, 0.0}));
    }

    // Equality tests. Spec only requires that number of dimensions and values
    // are equal
    {
        evec::EuclideanVector ev1{ 1.0, 1.5, 3.0 }; 
        evec::EuclideanVector ev2{ 1.0, 1.5, 3.0 }; 
        evec::EuclideanVector ev3{ 2.0, 3.0, 6.0 }; 

        assert((ev1 == ev2));
        assert((ev2 == ev1));
        assert((ev1 != ev3));
        assert((ev1 == (ev3 / 2.0)));
    }

    // Casting tests
    {
        evec::EuclideanVector ev1{ 5.0, 2.0, 0.0 };
        auto vec1 = static_cast<std::vector<double>>(ev1);

        assert(almost_eq(vec1[0], ev1[0]));
        assert(almost_eq(vec1[1], ev1[1]));
        assert(almost_eq(vec1[2], ev1[2]));
    }
}
