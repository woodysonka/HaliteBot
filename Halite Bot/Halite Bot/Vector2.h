#pragma once
#include <cmath>
class Vector2
{
public:

	union
	{
		float m_data[2];

		struct
		{
			float x;
			float y;
		};

	};

	Vector2();
	Vector2(float a_x, float a_y);
	~Vector2();


	Vector2 operator*(float scalar) const;

	Vector2 operator+(const Vector2& a_rhs) const;
	Vector2 operator-(const Vector2& a_rhs) const;
	Vector2& operator=(const Vector2 &a_rhs);

	friend Vector2 operator*(float scalar, Vector2& a_rhs);

	Vector2& operator-=(const Vector2& a_rhs);
	Vector2& operator+=(const Vector2& a_rhs);
	Vector2& operator*=(float a_rhs);

	bool operator==(const Vector2& a_rhs);

	float dot(const Vector2& a_rhs) const;
	float angle(const Vector2& a_rhs) const;
	Vector2 perpendicular() const;

	void normalise();
	Vector2 normalised();

	float magnitude();

	operator float*()
	{
		return m_data;
	}

};
