#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
#include<unordered_map>
using std::unordered_map;
using std::make_pair;
using namespace std;

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  return vertexMap.bucket_count();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  auto i = vertexMap.begin();
  int x = 0;
  for(; x<vertexMap.bucket_count();x++){
    if(*i->second == v) break;
    i++;
  }
  if(x==vertexMap.bucket_count()) return -1;
  else return vertexMap.bucket_size(x);
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  V & vx = *(new V(key));
  removeVertex(vx);
  //vertexMap.insert(make_pair(key, vx));
  edgeListIter tempedgeit;
  //adjList.insert(make_pair(key, tempedgeit));
  return vx;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  auto i =vertexMap.find(key);
  if (i==vertexMap.end()) return;
  else vertexMap.erase(key);
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));

  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2){
  V v1 = *vertexMap.find(key1)->second;
  V v2 = *vertexMap.find(key2)->second;
  E edd = E(v1, v2);
  auto i = edgeList.find(edgeList.begin(), edgeList.end(), edd);
  if (i==edgeList.end()) return;
  else edgeList.erase(i);
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it){
  edgeList.erase(it);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  V v1 = *vertexMap.find(key1)->second;
  V v2 = *vertexMap.find(key2)->second;
  E edd = E(v1, v2);
  auto i = edgeList.find(edgeList.begin(), edgeList.end(), edd);
  if (i==edgeList.end()) return false;

  return true;
}
