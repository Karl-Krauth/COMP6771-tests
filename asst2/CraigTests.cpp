#include "CraigTests.h"

#include "EuclideanVector.h"

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
}
