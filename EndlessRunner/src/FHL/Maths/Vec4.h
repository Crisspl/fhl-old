#ifndef FHL_VEC4_H
#define FHL_VEC4_H

#include <iostream>
#include <cmath>

#include "Vec2.h"
#include "Vec3.h"

namespace fhl {

	template<typename _T>
	struct Vec4
	{	  
		  using valueType = _T;
		  enum { Dimensions = 4 };

		  explicit constexpr Vec4(_T _scalar = 0) : x(_scalar), y(_scalar), z(_scalar), w(_scalar) { }
		  constexpr Vec4(_T _x, _T _y, _T _z, _T _w) : x(_x), y(_y), z(_z), w(_w) { }
		  constexpr Vec4(const Vec2<_T> & _v0, const Vec2<_T> & _v1) : x(_v0.x), y(_v0.y), z(_v1.x), w(_v1.y) { }
		  constexpr Vec4(const Vec3<_T> & _v, _T _n) : x(_v.x), y(_v.y), z(_v.z), w(_n) { }

		  template<typename _U>
		  constexpr Vec4(const Vec4<_U> & _other) :
				x(_T(_other.x)),
				y(_T(_other.y)),
				z(_T(_other.z)),
				w(_T(_other.w))
		  { }

		  static constexpr Vec4<_T> zero() { return{ 0, 0, 0, 0 }; }
		  static constexpr Vec4<_T> one() { return{ 1, 1, 1, 1 }; }

		  friend constexpr Vec4<_T> operator+(const Vec4<_T> & _left, const Vec4<_T> & _right) { return{ _left.x + _right.x, _left.y + _right.y, _left.z + _right.z, _left.w + _right.w }; }

		  friend constexpr Vec4<_T> operator-(const Vec4<_T> & _left, const Vec4<_T> & _right) { return{ _left.x - _right.x, _left.y - _right.y, _left.z - _right.z, _left.w - _right.w }; }

		  friend constexpr Vec4<_T> operator*(const Vec4<_T> & _left, const Vec4<_T> & _right) { return{ _left.x * _right.x, _left.y * _right.y, _left.z * _right.z, _left.w * _right.w }; }
		  friend constexpr Vec4<_T> operator*(const Vec4<_T> & _v, _T _scalar) { return{ _v.x * _scalar, _v.y * _scalar, _v.z * _scalar, _v.w / _scalar }; }
		  friend constexpr Vec4<_T> operator*(_T _scalar, const Vec4<_T> & _v) { return _v * _scalar; }

		  friend constexpr Vec4<_T> operator/(const Vec4<_T> & _left, const Vec4<_T> & _right) { return{ _left.x / _right.x, _left.y / _right.y, _left.z / _right.z, _left.w / _right.w }; }
		  friend constexpr Vec4<_T> operator/(const Vec4<_T> & _v, _T _scalar) { return{ _v.x / _scalar, _v.y / _scalar, _v.z / _scalar, _v.w / _scalar }; }

		  Vec4<_T> & operator+=(const Vec4<_T> & _other) { return *this = *this + _other; }

		  Vec4<_T> & operator-=(const Vec4<_T> & _other) { return *this = *this - _other; }

		  Vec4<_T> & operator*=(const Vec4<_T> & _other) { return *this = *this * _other; }
		  Vec4<_T> & operator*=(_T _scalar) { return *this = *this * _scalar; }

		  Vec4<_T> & operator/=(const Vec4<_T> & _other) { return *this = *this / _other; }
		  Vec4<_T> & operator/=(_T _scalar) { return *this = *this / _scalar; }

		  constexpr Vec4<_T> operator-() const { return Vec4<_T>(-x, -y, -z, -w); }

		  constexpr bool operator==(const Vec4<_T>  & _other) const { return _other.x == x && _other.y == y && _other.z == z; }
		  constexpr bool operator!=(const Vec4<_T>& _other) const { return !(*this == _other); }

		  constexpr bool operator<(const Vec4<_T> & _other) const { return x < _other.x && y < _other.y && z < _other.z && w < _other.w; }
		  constexpr bool operator<=(const Vec4<_T> & _other) const { return x <= _other.x && y <= _other.y && z <= _other.z && w <= _other.w; }
		  constexpr bool operator>(const Vec4<_T> & _other) const { return x > _other.x && y > _other.y && z > _other.z && w > _other.w; }
		  constexpr bool operator>=(const Vec4<_T> & _other) const { return x >= _other.x && y >= _other.y && z >= _other.z && w >= _other.w; }

		  constexpr const _T * data() const { return &x; }

		  _T & operator[](std::size_t _n) { return *(&x + _n); }
		  constexpr _T operator[](std::size_t _n) const { return *(&x + _n); }

		  friend std::ostream & operator<<(std::ostream & _os, const Vec4<_T> & _v)
		  {
				return _os << '{' << _v.x << ", " << _v.y << ", " << _v.z << ", " << _v.w << '}';
		  }

	public:
		  _T x, y, z, w;
	};

	using Vec4f = Vec4<float>;
	using Vec4lf = Vec4<double>;
	using Vec4i = Vec4<int>;
	using Vec4u = Vec4<unsigned>;

} //ns


#endif // FHL_VEC4_H