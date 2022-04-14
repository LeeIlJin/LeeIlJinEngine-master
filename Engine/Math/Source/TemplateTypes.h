#pragma once
//	Template Types

#include <windef.h>

template <typename T> struct Point
{
public:
	Point() {}
	Point(T x, T y) :x(x), y(y) {}

	bool operator == (const Point& other) { return (x == other.x && y == other.y); }
	bool operator != (const Point& other) { return !(x == other.x && y == other.y); }

	T x;
	T y;
};

template <typename T> struct Point3
{
public:
	Point3() {}
	Point3(T x, T y, T z) :x(x), y(y), z(z) {}

	bool operator == (const Point3& other) { return (x == other.x && y == other.y && z == other.z); }
	bool operator != (const Point3& other) { return !(x == other.x && y == other.y && z == other.z); }

	T x;
	T y;
	T z;
};

template <typename T> struct Point4
{
public:
	Point4() {}
	Point4(T x, T y, T z, T w) :x(x), y(y), z(z), w(w) {}

	bool operator == (const Point4& other) { return (x == other.x && y == other.y && z == other.z && w == other.w); }
	bool operator != (const Point4& other) { return !(x == other.x && y == other.y && z == other.z && w == other.w); }

	T x;
	T y;
	T z;
	T w;
};

template <typename T> struct Rect
{
public:
	Rect() {}
	Rect(T left, T top, T right, T bottom) :left(left), top(top), right(right), bottom(bottom) {}

	bool operator == (const Rect& other) { return (left == other.left && top == other.top && right == other.right && bottom == other.bottom); }
	bool operator != (const Rect& other) { return !(left == other.left && top == other.top && right == other.right && bottom == other.bottom); }

	T left;
	T top;
	T right;
	T bottom;
};

typedef Point<int> IntPoint;
typedef Point<int> IntPoint2;
typedef Point3<int> IntPoint3;
typedef Point4<int> IntPoint4;
typedef Rect<int> IntRect;

