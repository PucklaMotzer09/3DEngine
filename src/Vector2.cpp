#include "Vector2.h"
/*#include <cmath>

namespace Johnny
{
	template<class T>
	Vector2<T>::Vector2(const T& x, const T& y)
	{
		this->x = x;
		this->y = y;
	}
	template<class T>
	Vector2<T>::Vector2(const Vector2<T>& v)
	{
		x = v.x;
		y = v.y;
	}
	template<class T>
	T Vector2<T>::length(bool squared) const
	{
		if (squared)
			return x*x + y*y;
		else
			return sqrt(x*x+y*y);
	}
	template<class T>
	Vector2<T>& Vector2<T>::normalise()
	{
		T Length = length();

		x /= Length;
		y /= Length;

		return *this;
	}
	template<class T>
	Vector2<T>& Vector2<T>::add(const Vector2<T>& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}
	template<class T>
	Vector2<T>& Vector2<T>::subtract(const Vector2<T>& v)
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}
	template<class T>
	Vector2<T>& Vector2<T>::multiply(const Vector2<T>& v)
	{
		x *= v.x;
		y *= v.y;

		return *this;
	}
	template<class T>
	Vector2<T>& Vector2<T>::multiply(const T& s)
	{
		x *= s;
		y *= s;

		return *this;
	}
	template<class T>
	Vector2<T>& Vector2<T>::divide(const Vector2<T>& v)
	{
		x /= v.x;
		y /= v.y;

		return *this;
	}
	template<class T>
	Vector2<T>& Vector2<T>::divide(const T& s)
	{
		x /= s;
		y /= s;

		return *this;
	}
	template<class T>
	T Vector2<T>::dot(const Vector2<T>& v) const
	{
		return x * v.x + y * v.y;
	}
	template<class T>
	T Vector2<T>::distance(const Vector2<T>& v,bool squared) const
	{
		Vector2<T> v1(v);

		v1.subtract(*this);

		return v1.length(squared);
	}
	template<class T>
	Vector2<T>& operator+=(Vector2<T>& v1, const Vector2<T>& v2)
	{
		return v1.add(v2);
	}
	template<class T>
	Vector2<T>& operator-=(Vector2<T>& v1, const Vector2<T>& v2)
	{
		return v1.subtract(v2);
	}
	template<class T>
	Vector2<T>& operator*=(Vector2<T>& v1, const Vector2<T>& v2)
	{
		return v1.multiply(v2);
	}
	template<class T>
	Vector2<T>& operator/=(Vector2<T>& v1, const Vector2<T>& v2)
	{
		return v1.divide(v2);
	}
	template<class T>
	const Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2)
	{
		return Vector2<T>(v1).add(v2);
	}
	template<class T>
	const Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2)
	{
		return Vector2<T>(v1).subtract(v2);
	}
	template<class T>
	const Vector2<T> operator*(const Vector2<T>& v1, const Vector2<T>& v2)
	{
		return Vector2<T>(v1).multiply(v2);
	}
	template<class T>
	const Vector2<T> operator/(const Vector2<T>& v1, const Vector2<T>& v2)
	{
		return Vector2<T>(v1).divide(v2);
	}
}*/