//
//  Weighted_Digraph.h
//  idek
//
//  Created by Font,Mario,Jr on 1/11/18.
//  Copyright © 2018 Font,Mario,Jr. All rights reserved.
// NOTE: IMPLEMENTATION ASSUMES -1 cost is a null connection

#ifndef Weighted_Digraph_h
#define Weighted_Digraph_h
#include <set>
namespace cop3530{
    using namespace cop3530;
    template<typename Type>
    class Weighted_Digraph{
    private:
        static const int MAX=20;
        int adjMatrix[MAX][MAX];//keeps track of connections
        Type labels[MAX];//what is stored in the Weighted_Digraph
        int numVertices;//number of vertices
    public:
        Weighted_Digraph();
        ~Weighted_Digraph();
        void add_vertex(const Type& value);//const reference to put in that specific memory address holding the value
        void add_edge(int source, int target, int cost);//in adj matrix
        void add_edge(int source, int target);//in adj matrix
        void remove_edge(int source, int target);//in adj matrix
        Type& operator[](int vertex);//gets reference to data in graph Mutable
        Type operator[](int vertex) const;//gets copy of data in graph Immutable
        int size();//returns sz
        int cost(int source, int target);//is there an edge between the 2 vertices
        std::set<int> neighbors(int vertex) const;//gets set of neighbors
    
    };
    template<typename Type>
    Weighted_Digraph<Type>::Weighted_Digraph()
    :numVertices(0)
    {}
    template<typename Type>
    Weighted_Digraph<Type>::~Weighted_Digraph()
    {
    }

    template<typename Type>
    void Weighted_Digraph<Type>::add_vertex(const Type& value)
    {
        assert(size()<MAX);
        int newVertexNumber=numVertices;//number of new vertex equal to current length bc indexed by 0
        numVertices++;
        for(int i=0;i<numVertices;i++)
        {
            adjMatrix[i][newVertexNumber]=-1;
            adjMatrix[newVertexNumber][i]=-1;
        }
        adjMatrix[newVertexNumber][newVertexNumber]=0;//0 cost to get to itself
        labels[newVertexNumber]=value;
    }//const reference to put in that specific memory address holding the value

    template<typename Type>
    void Weighted_Digraph<Type>::add_edge(int source, int target, int cost)
    {
        assert(source<size()&&target<size());
        adjMatrix[source][target]=cost;
    }//in adj matrix

    template<typename Type>
    void Weighted_Digraph<Type>::add_edge(int source, int target)
    {
        assert(source<size()&&target<size());
        adjMatrix[source][target]=1;
    }//in adj matrix

    template<typename Type>
    void Weighted_Digraph<Type>::remove_edge(int source, int target)
    {
        assert(source<size()&&target<size());
        adjMatrix[source][target]=0;
    }//in adj matrix

    template<typename Type>
    Type& Weighted_Digraph<Type>::operator[](int vertex)
    {
        return labels[vertex];
    }//gets reference to data in graph Mutable

    template<typename Type>
    Type Weighted_Digraph<Type>::operator[](int vertex) const
    {
        const int copy=labels[vertex];
        return copy;
    }//gets copy of data in graph Immutable

    template<typename Type>
    int Weighted_Digraph<Type>::size()
    {
        return numVertices;
    }//returns sz

    template<typename Type>
    int Weighted_Digraph<Type>::cost(int source, int target)
    {
        return adjMatrix[source][target];
    }//is there an edge between the 2 vertices

    template<typename Type>
    std::set<int> Weighted_Digraph<Type>::neighbors(int vertex) const{
        
    }//gets set of neighbors
    
}

#endif /* Weighted_Digraph_h */
