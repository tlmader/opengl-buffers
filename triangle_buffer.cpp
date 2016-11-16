#pragma GCC diagnostic ignored "-Wc++11-extensions"

#include "triangle_buffer.hpp"

/**
 * Implements functions for a TriangleBuffer.
 * @author Ted Mader
 * @date 2016-11-14
 */

TriangleBuffer::TriangleBuffer(vec4 a, vec4 b, vec4 c) {
  vector::push_back(a);
  vector::push_back(b);
  vector::push_back(c);
  triangles.push_back(*new Triangle(a, b, c));
}

TriangleBuffer::TriangleBuffer(const TriangleBuffer &rhs) {
  triangles = rhs.triangles;
}

void TriangleBuffer::addVerticesForTriangle(vec4 a, vec4 b, vec4 c) {
  if (compareVectors(a, b) ||
      compareVectors(a, c) ||
      compareVectors(b, c)) {
    return;
  }
  triangles.push_back(*new Triangle(replaceIfExists(a), replaceIfExists(b), replaceIfExists(c)));
}

void TriangleBuffer::addVertexAndLinkExisting(int i, int j, vec4 v) {
  if (compareVectors(vector::at(i), v) ||
      compareVectors(vector::at(j), v)) {
    return;
  }
  triangles.push_back(*new Triangle(vector::at(i), vector::at(j), replaceIfExists(v)));
}

void TriangleBuffer::modifyVertex(int i, vec4 v) {
  if (std::find(this->begin(), this->end(), v) != this->end()) {
    return;
  }
  vector::at(i).operator=(v);
  for (Triangle& t : triangles) {
    if (compareVectors(t.getA(), v) ||
        compareVectors(t.getB(), v) ||
        compareVectors(t.getC(), v)) {
      t.calcNormals();
    }
  }
}

GLfloat* TriangleBuffer::getVerticesForGlTriangles() {
  GLfloat *vertices[triangles.size() * 3];
  int i = 0;
  for (const Triangle& t : triangles) {
    vertices[i++] = t.getA();
    vertices[i++] = t.getB();
    vertices[i++] = t.getC();
  }
  return *vertices;
}

GLfloat* TriangleBuffer::getNormalsForGlTriangles() {
  GLfloat *vertices[triangles.size()];
  int i = 0;
  for (const Triangle& t : triangles) {
    vertices[i++] = t.getNormals();
  }
  return *vertices;
}

vec4 TriangleBuffer::replaceIfExists(vec4 v) {
  std::vector<vec4>::iterator it = std::find(this->begin(), this->end(), v);
  if (it != this->end()) {
    return *it;
  }
  return v;
}

bool TriangleBuffer::compareVectors(vec4 a, vec4 b) {
  if (a[0] == b[0] || a[1] == b[1] || a[2] == b[2] || a[3] == b[3]) {
    return true;
  }
  return false;
}
