#include "graph.hpp"
#include <cassert>
#include <iostream>
#include "printing.hpp"

Graph::VertexId Graph::add_vertex() {
  const VertexId new_id = get_new_vertex_id();
  vertices_.emplace(new_id, new_id);
  adjacency_list_.emplace(new_id, std::vector<EdgeId>{});
  set_vertex_depth(new_id, 1, 0);
  return new_id;
}

Graph::EdgeId Graph::add_edge(VertexId from_vertex_id, VertexId to_vertex_id) {
  assert(has_vertex(from_vertex_id));
  assert(has_vertex(to_vertex_id));
  const EdgeId new_id = get_new_edge_id();
  adjacency_list_[from_vertex_id].emplace_back(new_id);
  if (from_vertex_id != to_vertex_id) {
    adjacency_list_[to_vertex_id].emplace_back(new_id);
  }
  const Edge::Color edge_color = get_edge_color(from_vertex_id, to_vertex_id);
  if (edge_color == Edge::Color::Grey) {
    const auto from_vertex_depth = get_vertex_depth(from_vertex_id);
    set_vertex_depth(to_vertex_id, from_vertex_depth + 1, from_vertex_depth);
  }
  edges_.try_emplace(new_id, new_id, from_vertex_id, to_vertex_id, edge_color);
  return new_id;
}

void Graph::set_vertex_depth(VertexId vertex_id,
                             Depth new_depth,
                             Graph::Depth old_depth) {
  if (old_depth > 0) {
    vertices_at_depth_[get_vertex_depth(vertex_id)].erase(vertex_id);
  }
  depths_of_vertices_[vertex_id] = new_depth;
  vertices_at_depth_[new_depth].insert(vertex_id);
}

constexpr int kYellowDepthDifference = 1;
constexpr int kRedDepthDifference = 2;

Graph::Edge::Color Graph::get_edge_color(VertexId from_vertex_id,
                                         VertexId to_vertex_id) const {
  const auto from_vertex_depth = get_vertex_depth(from_vertex_id);
  const auto to_vertex_depth = get_vertex_depth(to_vertex_id);
  if (from_vertex_id == to_vertex_id) {
    return Edge::Color::Green;
  }
  if (to_vertex_depth - from_vertex_depth == kYellowDepthDifference &&
      !is_connected(from_vertex_id, to_vertex_id)) {
    return Edge::Color::Yellow;
  }
  if (to_vertex_depth - from_vertex_depth == kRedDepthDifference) {
    return Edge::Color::Red;
  }
  return Edge::Color::Grey;
}

bool Graph::is_connected(VertexId from_vertex_id, VertexId to_vertex_id) const {
  const auto children = children_of_vertex(from_vertex_id);
  for (const auto child_id : children) {
    if (child_id == to_vertex_id) {
      return true;
    }
  }
  return false;
}
