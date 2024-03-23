#pragma once
#include <iostream>

class Color
{
public:
	float r, g, b;

	static Color undefined;

	//LightIntensity();
	Color(float R = 0.f, float G = 0.f, float B = 0.f) { r = R; g = G; b = B; };
	~Color() = default;

	void add(float R, float G, float B);
	float calculateDifference(const Color& other);

	Color operator+(Color& li);
	Color operator-(Color& li);
	Color operator/(float num);
	Color operator*(float num);
	friend bool operator==(const Color& lhs, const Color& rhs);


	/*void operator+=(LightIntensity& li);
	LightIntensity operator-=(LightIntensity& li);
	LightIntensity operator*=(float num);
	LightIntensity operator/=(float num);
	friend LightIntensity operator*(float num, LightIntensity& li);
	friend LightIntensity operator*(LightIntensity& li, float num);*/

	friend std::ostream& operator<<(std::ostream& str, Color& li);

};

