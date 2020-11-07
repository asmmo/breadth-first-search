#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <concepts>
#include <queue>
#include <atomic>
using namespace std::string_literals;


template <class T>
class Graph {
public:
    struct Vertex {
        explicit Vertex(T const &data_) : data{data_}, distance{SIZE_MAX} {}
        explicit Vertex(T && data_) : data{std::move(data_)}, distance{SIZE_MAX} {}

        std::list<std::reference_wrapper<Vertex>> adjacency_list{};
        T data;
        size_t distance{};
    };

private:
    std::list<std::reference_wrapper<Vertex>> graph;


public:

    void add(Vertex & vertex, Vertex & adjacent_Vertex){

        vertex.adjacency_list.push_back(std::ref(adjacent_Vertex));
        graph.push_back(std::ref(vertex));
    }

    void add(Vertex & vertex){
        graph.push_back(std::ref(vertex));
    }

    template<class ... Vertexes>
    void add(Vertex & vertex, Vertexes& ... adjacent_vertexes)requires std::is_same_v<Vertex, std::common_type_t<Vertexes...>>{
        (add(vertex, std::forward<Vertexes&>(adjacent_vertexes)),...);
    }

    void start_search() {
        std::queue<std::reference_wrapper<Vertex>> q;
        auto temp = graph.front();
        std::cout << temp.get().data << "\n";
        temp.get().distance = 0;
        q.push(temp);// Adding the root. It's arbitrary so far.

        while (!q.empty()) {
            temp = q.front();
            q.pop();

            for(auto vertex : temp.get().adjacency_list) {
                if (vertex.get().distance == SIZE_MAX) {
                    std::cout << vertex.get().data << "\n";
                    q.push(vertex);
                    vertex.get().distance = temp.get().distance + 1;
                }
            }

        }
    }
    void display_distances(){
        for(auto vertex : graph)
            std::cout << vertex.get().data << ":" << vertex.get().distance << "\n";
    }

};



/*
 *         A
 *       /|  \
 *      / |   \
 *     v  V    v
 *     D  C <---B---> G
 *     |   \   /\
 *     v    v v  \
 *     I     E    v
 *           |    H
 *           |   /
 *           V  v
 *             F
 *
 *
 *
 *
 */

int main() {
    Graph<std::string>::Vertex A{"A"s}, B{"B"s}, C{"C"s}, D{"D"s}, E{"E"s}, F{"F"s}, G{"G"s}, H{"H"s}, I{"I"s};

    Graph<std::string> g;
    g.add(A, B, C, D);
    g.add(B, C, E, G, H);
    g.add(C, E);
    g.add(D, I);
    g.add(E, F);
    g.add(F);
    g.add(G);
    g.add(H, F);
    g.add(I);


    g.start_search();
    std::cout << "\n\nThe distances\n\n";
    g.display_distances();

}
