#pragma once

// TODO: Use custom implementation
#include <vector>

namespace mm
{
    // TODO: Eventually just have an iterator
    struct edge
    {
        size_t u;
        size_t v;
    };

    template<typename T>
    class graph
    {
        std::vector<T> _vertices;
        std::vector<std::vector<size_t>> _adj;

    public:
        graph() : graph({}, {}) {}
        graph(const std::vector<T>& vertices, const std::vector<edge>& edges) : _vertices(vertices)
        {
            _adj.resize(_vertices.size());
            for (auto e : edges)
            {
                add_edge(e);
            }
        }

        void add_edge(edge e)
        {
            _adj[e.u].push_back(e.v);
            _adj[e.v].push_back(e.u);
        }

        void add_vertex(T v)
        {
            _vertices.push_back(v);
        }

        void dfs(size_t start = 0)
        {
            create_visited();
            size_t size = _vertices.size();
            for (size_t i = 0; i < size; i++)
            {
                size_t index = (i + start) % size;
                if (!is_visited(index))
                {
                    visit(index);
                }
            }
        }

        void visit(size_t index)
        {
            set_visited(index, true);
            for (size_t nb : _adj[index])
            {
                if (!is_visited(nb))
                {
                    visit(nb);
                }
            }
        }

    private:
        std::vector<bool> _visited;
        void create_visited()
        {
            _visited = std::vector<bool>(_vertices.size());
            for (size_t i = 0; i < _vertices.size(); i++)
            {
                _visited[i] = false;
            }
        }

        void set_visited(size_t index, bool value)
        {
            _visited[index] = value;
        }

        bool is_visited(size_t index) const
        {
            return _visited[index];
        }
    };
}
