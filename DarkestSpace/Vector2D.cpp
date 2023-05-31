#include "Vector2D.hpp"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = +x;
	this->y = +y;
}


Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::Sub(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::Mult(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::Div(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Sub(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Mult(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Div(v2);
}


Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}
Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Sub(vec);
}
Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Mult(vec);
}
Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Div(vec);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";	//just showing the current vectors
}