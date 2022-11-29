#include <iostream>
#include <string>
using namespace std;

template<class T> class Graph;
template<class T>
class Edge {
    friend class Graph<T>;
private:
    T source;
    T target;
    int weight;
public:
    Edge();
    Edge(T source, T target, int weight);
};

template<class T>
Edge<T>::Edge() {
    weight = 0;
}

template<class T>
Edge<T>::Edge(T source, T target, int weight) {
    this->source = source;
    this->target = target;
    this->weight = weight;
}