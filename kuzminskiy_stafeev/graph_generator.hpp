<<<<<<< HEAD
#include <mutex>
#include "graph.hpp"
=======
>>>>>>> 3dab9460508dd55d49a03564527fbcb682a4276d
#pragma once
#include "graph.hpp"

namespace uni_course_cpp {

class GraphGenerator {
 public:
  struct Params {
   public:
    Params(Graph::Depth depth, int new_vertices_count)
        : depth_(depth), new_vertices_count_(new_vertices_count) {}

    Graph::Depth depth() const { return depth_; }
    int new_vertices_count() const { return new_vertices_count_; }

   private:
    Graph::Depth depth_ = 0;
    int new_vertices_count_ = 0;
  };

  explicit GraphGenerator(Params&& params) : params_(std::move(params)) {}

  Graph generate() const;

 private:
  void generate_grey_edges(Graph& graph) const;
<<<<<<< HEAD
  void generate_green_edges(Graph& graph) const;
  void generate_yellow_edges(Graph& graph) const;
  void generate_red_edges(Graph& graph) const;
  void generate_grey_branch(Graph& graph,
                            std::mutex& graph_mutex,
                            std::vector<Graph::VertexId> previous_vertex_ids,
                            Graph::Depth cur_depth) const;

=======
>>>>>>> 3dab9460508dd55d49a03564527fbcb682a4276d
  Params params_ = Params(0, 0);
};

}  // namespace uni_course_cpp
