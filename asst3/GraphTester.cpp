#include <iostream>
#include "Graph.h"
#include "ProvidedTests.h"

int main(int argc, char *argv[]) {
    std::cout << "Starting test suite.\n";

    printf("Starting provided tests\n");
    providedTests();
    printf("Passed provided tests\n");

    std::cout << "All tests passed.\n";

    return 0;
}
