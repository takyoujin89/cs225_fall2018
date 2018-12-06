/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#pragma once

#include <vector>
#include <algorithm>

#include "graph.h"
#include "edge.h"

/**
 * Represents a algorithm to determine the maximum network flow of a graph.
 */
class NetworkFlow {
public:
  /**
   * Constructor to create a flow analyzer.
   *
   * @param startingGraph  The initial graph.
   * @param source  The source vertex.
   * @param sink    The sink vertex.
   */

  NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink);

  /**
   * Create an initial residual graph.
   *
   */

  void createResidualGraph();

  /**
   * Find an augmenting path from the source to the sink.
   *
   * @returns A vector of the vertices.
   */

  std::vector<Vertex> findAugmentingPath(Graph & residual, Vertex source, Vertex sink);

  /**
   * Returns a constant reference to the state space graph.
   *
   * @returns A constant reference to the state space graph.
   */
  const Graph & getGraph() const;
  const Graph & getFlowGraph() const;
  const Graph & getResidualGraph() const;

private:
  Graph g_;
  Graph residual_;
  Graph flow_;

  Vertex source_;
  Vertex sink_;

  Vertex startingVertex_;
};
