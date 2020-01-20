#pragma once

/* ----------二次元情報クラス---------- */

template <class T>class Vector2Templete
{
public:
	Vector2Templete();
	Vector2Templete(T x, T y);
	~Vector2Templete();
	T x;
	T y;

	// 代入演算子
	Vector2Templete& operator = (const Vector2Templete<T>& vec);

	// 添え字演算子
	T& operator [] (int i);

	// 比較演算子
	bool operator == (const Vector2Templete& vec)const;
	bool operator != (const Vector2Templete& vec)const;
	bool operator < (const Vector2Templete& vec)const;
	bool operator > (const Vector2Templete& vec)const;
	bool operator <= (const Vector2Templete& vec)const;
	bool operator >= (const Vector2Templete& vec)const;

	// 単項演算子
	Vector2Templete& operator += (const Vector2Templete& vec);
	Vector2Templete& operator -= (const Vector2Templete& vec);
	Vector2Templete& operator *= (T k);
	Vector2Templete& operator /= (T k);
	Vector2Templete operator + ()const;
	Vector2Templete operator - ()const;
};

// ベクトルの演算

// Vector2 + T
template <class T>
Vector2Templete<T> operator + (const Vector2Templete<T>& vec, T k);

// Vector2 - T
template <class T>
Vector2Templete<T> operator - (const Vector2Templete<T>& vec, T k);

// Vector2 + Vector2
template <class T>
Vector2Templete<T> operator + (const Vector2Templete<T>& u, const Vector2Templete<T>& v);

// Vector2 - Vector2

template <class T>
Vector2Templete<T> operator - (const Vector2Templete<T>& u, const Vector2Templete<T>& v);

// 二点の距離の二乗を返す
template <class T>
T operator * (const Vector2Templete<T>& u, const Vector2Templete<T>& v);

// Vector2 / Vector2
template <class T>
Vector2Templete<T> operator / (const Vector2Templete<T>& u, const Vector2Templete<T>& v);

// Vector2 % Vector2
template <class T>
Vector2Templete<T> operator % (const Vector2Templete<T>& u, const Vector2Templete<T>& v);

// Vector2 * T
template <class T>
Vector2Templete<T> operator * (const Vector2Templete<T>& vec, T k);

// T * Vector2
template <class T>
Vector2Templete<T> operator * (T k, const Vector2Templete<T>& vec);

// Vector2 / T
template <class T>
Vector2Templete<T> operator / (const Vector2Templete<T>& vec, T k);

// Vector2 % int
template <class T>
Vector2Templete<T> operator % (const Vector2Templete<T>& vec, int k);

// 二点の距離の二乗を返す
template <class T>
T LengthSquare(const Vector2Templete<T>& u, const Vector2Templete<T>& v);

using Vector2Int = Vector2Templete<int>;
using Vector2Dbl = Vector2Templete<double>;
using Vector2Flt = Vector2Templete<float>;
using Vector2Sht = Vector2Templete<short>;

#include "./detail/Vector2.h"
