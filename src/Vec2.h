#pragma once
struct Vec2
{
	float x = 0;
	float y = 0;
};

Vec2 operator+(const Vec2& l, const Vec2& r)
{
	return { l.x + r.x, l.y + r.y };
}
Vec2 operator-(const Vec2& l, const Vec2& r)
{
	return { l.x - r.x, l.y - r.y };
}

bool operator!=(const Vec2& l, const Vec2& r)
{
	return l.x != r.x || l.y != r.y;
}
bool operator==(const Vec2& l, const Vec2& r)
{
	return l.x == r.x && l.y == r.y;
}

Vec2 operator*(const Vec2& l, const int& r)
{
	return { l.x * r, l.y * r };
}
Vec2 operator/(const Vec2& l, const int& r)
{
	return { l.x / r, l.y / r };
}

Vec2 operator*(const Vec2& l, const float& r)
{
	return { l.x * r, l.y * r };
}
Vec2 operator/(const Vec2& l, const float& r)
{
	return { l.x / r, l.y / r };
}

Vec2 lerp(Vec2 a, Vec2 b, float t)
{
	return a * (1.0f - t) + b * t;
}

double normalize(double number, double minVal, double maxVal) 
{
	return (number - minVal) / (maxVal - minVal);
}

float normalize(float number, float minVal, float maxVal)
{
	return (number - minVal) / (maxVal - minVal);
}

Vec2 normalize(Vec2 number, Vec2 minVal, Vec2 maxVal) {
	return { (number.x - minVal.x) / (maxVal.x - minVal.x),(number.y - minVal.y) / (maxVal.y - minVal.y) };
}

