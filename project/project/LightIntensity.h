#pragma once
#include <iostream>

class LightIntensity
{
public:
	float r, g, b;

	//LightIntensity();
	LightIntensity(float R = 0.f, float G = 0.f, float B = 0.f) { r = R; g = G; b = B; };
	~LightIntensity() = default;

	void add(float R, float G, float B);

	LightIntensity operator+(LightIntensity& li);
	LightIntensity operator-(LightIntensity& li);
	LightIntensity operator/(float num);
	LightIntensity operator*(float num);

	/*void operator+=(LightIntensity& li);
	LightIntensity operator-=(LightIntensity& li);
	LightIntensity operator*=(float num);
	LightIntensity operator/=(float num);
	friend LightIntensity operator*(float num, LightIntensity& li);
	friend LightIntensity operator*(LightIntensity& li, float num);*/

	friend std::ostream& operator<<(std::ostream& str, LightIntensity& li);

};

