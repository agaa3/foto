#pragma once
#include <iostream>

class Color
{
public:
	float r, g, b;

	static Color undefined;

	Color(float R = 0.f, float G = 0.f, float B = 0.f) { r = R; g = G; b = B; };
	~Color() = default;

	void add(float R, float G, float B);
	float calculateDifference(const Color& other);
	void setValues(Color newColor);

	Color operator+(Color& li);
	Color operator-(Color& li);
	Color operator/(float num);
	Color operator*(float num);
	friend bool operator==(const Color& lhs, const Color& rhs);

	friend std::ostream& operator<<(std::ostream& str, Color& li);

};

