#ifndef MESH_BUFFER_H
#define MESH_BUFFER_H

#include <vector>
#include "line.hpp"

/**
 * Contains function declarations for a MeshBuffer.
 * @author Ted Mader
 * @date 2016-11-14
 */
class MeshBuffer : public std::vector<vec2> {

public:
  /**
   * Constructs a MeshBuffer with a single Line.
   * @param v1 a vertex
   * @param v2 a vertex
   * @return the constructed Buffer
   */
  MeshBuffer(vec2 v1, vec2 v2);

  /**
   * Returns a copy of this MeshBuffer.
   * @return the copied MeshBuffer
   */
  MeshBuffer(const MeshBuffer& rhs);

  /**
   * Adds a edge to the buffer by linking an existing
   * vertex to a new vertex.
   * @param i an index for an existing vertex
   * @param v a vec2 to be added
   */
  void addVertex(int i, vec2 v);

  /**
   * Modifies the position of a vertex by an index by
   * replacing its coordinates with those of another
   * vec2.
   * @param i an index for an existing vertex
   * @param v a vec2 with the new coordinates
   */
  void modifyVertex(int i, vec2 v);

  /**
   * Returns a vector containing pairs of vertices for independent line
   * segments, to be used with GL_LINES.
   * @return the vector of Vertices
   */
  std::vector<vec2> getVerticesForGlLines();

private:
  std::vector<Line> lines;
};

#endif
