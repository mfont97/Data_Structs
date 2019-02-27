//
//  Weighted_Graph.h
//  idek
//
//  Created by Font,Mario,Jr on 1/11/18.
//  Copyright © 2018 Font,Mario,Jr. All rights reserved.
//

#ifndef Weighted_Graph_h
#define Weighted_Graph_h
#include <set>
namespace cop3530{
    using namespace cop3530;
    template<typename Type>
    class Weighted_Graph{
    private:
        static const int MAX=20;
        int adjMatrix[MAX][MAX];//keeps track of connections
        Type labels[MAX];//what is stored in the Weighted_Graph
        int numVertics;//number of vertices
    public:
        Weighted_Graph();
        ~Weighted_Graph();
        void add_vertex(const Type& value);//const reference to put in that specific memory address holding the value
        void add_edge(int source, int target);//in adj matrix
        void remove_edge(int source, int target);//in adj matrix
        Type& operator[](int vertex);//gets reference to data in graph Mutable
        Type operator[](int vertex) const;//gets copy of data in graph Immutable
        int size();//returns sz
        bool isEdge(int source, int target);//is there an edge between the 2 vertices
        std::set<int> neighbors(int vertex) const;//gets set of neighbors
    
    };
    template<typename Type>
    Weighted_Graph<Type>::Weighted_Graph(){}
    template<typename Type>
    Weighted_Graph<Type>::~Weighted_Graph(){}
    template<typename Type>
    void Weighted_Graph<Type>::add_vertex(const Type& value){}//const reference to put in that specific memory address holding the value
    template<typename Type>
    void Weighted_Graph<Type>::add_edge(int source, int target){}//in adj matrix
    template<typename Type>
    void Weighted_Graph<Type>::remove_edge(int source, int target){}//in adj matrix
    template<typename Type>
    Type& Weighted_Graph<Type>::operator[](int vertex){}//gets reference to data in graph Mutable
    template<typename Type>
    Type Weighted_Graph<Type>::operator[](int vertex) const{}//gets copy of data in graph Immutable
    template<typename Type>
    int Weighted_Graph<Type>::size(){}//returns sz
    template<typename Type>
    bool Weighted_Graph<Type>::isEdge(int source, int target){}//is there an edge between the 2 vertices
    template<typename Type>
    std::set<int> Weighted_Graph<Type>::neighbors(int vertex) const{}//gets set of neighbors
    
}

#endif /* Weighted_Graph_h */
