#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/mm/graph.h"

#include <vector>

TEST_CASE("Test the graph class")
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6};
    std::vector<mm::edge> edges = {
        {0, 1}, {1, 5}, {5, 2}, {0, 2}, {3, 4}, {4, 6}
    };
    mm::graph<int> g(v, edges);
    g.dfs();
}
