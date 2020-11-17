#pragma once

#include "vec3f.hpp"

namespace geometry {

template <typename T> class Triangle_ {
private:
  enum Index : unsigned char { A = 0, B, C, COUNT };

public:
  Triangle_() = default;
  Triangle_(T a, T b, T c);

  T const &a() const;
  T const &b() const;
  T const &c() const;

  T const &operator[](int index) const;

  T &a();
  T &b();
  T &c();

  T &operator[](int index);

private:
  T m_vertices[Index::COUNT];
};

using Triangle = Triangle_<math::Vec3f>;
using IndexTriangle = Triangle_<unsigned int>;

Triangle scale(Triangle t, float s);

Triangle translate(Triangle t, math::Vec3f const &v);

template<typename T>
Triangle_<T>::Triangle_(T a, T b, T c) : m_vertices{ a, b, c } {}

template<typename T>
T const& Triangle_<T>::a() const { return m_vertices[Index::A]; }

template<typename T>
T const& Triangle_<T>::b() const { return m_vertices[Index::B]; }

template<typename T>
T const& Triangle_<T>::c() const { return m_vertices[Index::C]; }

template<typename T>
T const& Triangle_<T>::operator[](int index) const {
	return m_vertices[index];
}

template<typename T>
T& Triangle_<T>::a() { return m_vertices[Index::A]; };

template<typename T>
T& Triangle_<T>::b() { return m_vertices[Index::B]; };

template<typename T>
T& Triangle_<T>::c() { return m_vertices[Index::C]; };

template<typename T>
T& Triangle_<T>::operator[](int index) { return m_vertices[index]; }

} // namespace geometry


