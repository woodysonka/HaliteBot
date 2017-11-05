#include "Vector2.h"

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}


Vector2::~Vector2()
{
}

float Vector2::magnitude()
{
	return sqrt(x*x + y*y);
}

float Vector2::dot(const Vector2 & a_rhs) const
{
	return ((*this).x * a_rhs.x) + ((*this).y * a_rhs.y);
}

float Vector2::angle(const Vector2 & a_rhs) const
{
	float angle = acos(dot(a_rhs));
	float perpdot = perpendicular().dot(a_rhs);

	if (perpdot >= 0.0f)
		return angle;

	else
		return -angle;
}

Vector2 Vector2::perpendicular() const
{
	return Vector2(x, -y);
}

void Vector2::normalise()
{
	float mang = magnitude();

	if (mang > 0)
	{
		x = x / mang;
		y = y / mang;
	}
}

Vector2 Vector2::normalised()
{
	Vector2 vec;

	float mang = magnitude();

	if (mang > 0)
	{
		vec.x = x / mang;
		vec.y = y / mang;

		return vec;
	}
	return Vector2(0, 0);
}

Vector2 Vector2::operator+(const Vector2 & a_rhs) const
{
	return Vector2(x + a_rhs.x, y + a_rhs.y);
}

Vector2 Vector2::operator-(const Vector2 & a_rhs) const
{
	return Vector2(x - a_rhs.x, y - a_rhs.y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 & Vector2::operator=(const Vector2 & a_rhs)
{
	x = a_rhs.x;
	y = a_rhs.y;
	return (*this);
}

Vector2 & Vector2::operator-=(const Vector2 & a_rhs)
{
	(*this) = (*this) - a_rhs;
	return (*this);
}

Vector2 & Vector2::operator+=(const Vector2 & a_rhs)
{
	(*this) = (*this) + a_rhs;
	return (*this);
}

Vector2 & Vector2::operator*=(float a_rhs)
{
	(*this).x = (*this).x * a_rhs;
	(*this).y = (*this).y * a_rhs;
	return (*this);
}

bool Vector2::operator==(const Vector2 & a_rhs)
{
	if ((*this).x == a_rhs.x && (*this).y == a_rhs.y)
		return true;

	else
		return false;
}

Vector2 operator*(float scalar, Vector2 & a_rhs)
{
	return Vector2(a_rhs.x * scalar, a_rhs.y * scalar);
}
