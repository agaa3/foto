
#pragma once
#include <iostream>
class LightIntensity { //UWAZAC NA OBCINANIE WARTOSCI PRZY OBLICZENIACH
public:
	float R=0, G=0, B=0;
    static LightIntensity undefined;


	~LightIntensity() = default;
	LightIntensity() = default;
	LightIntensity(float r, float g, float b);
	LightIntensity(float x) : R(x), G(x), B(x) {};

	LightIntensity(const LightIntensity& li) : R(li.R), G(li.G), B(li.B) {};

	float calculateDifference(const LightIntensity& other);

	bool friend operator==(const LightIntensity& lhs, const LightIntensity& rhs);
	
	LightIntensity operator+(LightIntensity& li);
	LightIntensity operator-(LightIntensity& li);

	void operator+=(const LightIntensity& li);
	LightIntensity operator*(float num);
	LightIntensity operator*(LightIntensity& li);
	LightIntensity operator/(float li);
	void operator/=(const float& li);
	bool operator!=(const LightIntensity& li);
	friend std::ostream& operator<<(std::ostream& str, LightIntensity& li) ;
};

//Color(float R = 0.f, float G = 0.f, float B = 0.f) { r = R; g = G; b = B; };
//~Color() = default;

//void add(float R, float G, float B);

//Color operator-(Color& li);
//Color operator/(float num);
//Color operator*(float num);
/*friend bool operator==(const Color& lhs, const Color& rhs);

friend std::ostream& operator<<(std::ostream& str, Color& li)*/;