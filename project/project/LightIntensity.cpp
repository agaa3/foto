#include "LightIntensity.h"
void LightIntensity::add(float R, float G, float B) {
	this->r += R;
	this->g += G;
	this->b += B;
}

LightIntensity LightIntensity::operator+(LightIntensity& li) {
	return LightIntensity(this->r + li.r, this->g + li.g, this->b + li.b);

}
LightIntensity LightIntensity::operator-(LightIntensity& li) {
	return LightIntensity(this->r - li.r, this->g - li.g, this->b - li.b);
}

LightIntensity LightIntensity::operator/(float num) {
	return LightIntensity(this->r / num, this->g / num, this->b / num);
}

LightIntensity LightIntensity::operator*(float num) {
	return LightIntensity(this->r * num, this->g * num, this->b * num);
}

std::ostream& operator<<(std::ostream& str, LightIntensity& li) {
	str << "[ " << li.r << ", " << li.g << ", " << li.b << "]";
	return str;
}