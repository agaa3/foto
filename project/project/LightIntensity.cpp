#include "LightIntensity.h"

LightIntensity LightIntensity::undefined = LightIntensity(-1.f, -1.f, -1.f);


LightIntensity::LightIntensity(float r, float g, float b) : R(r), G(g), B(b) {
	/*this->R = (r > 1.0f) ? 1 : r;
	this->G = (g > 1.0f) ? 1 : g;
	this->B = (b > 1.0f) ? 1 : b;*/
}

void LightIntensity::operator+=(const LightIntensity& li) {
	this->R = (li.R >= 0) ? ((this->R + li.R > 1) ? 1 : this->R + li.R) : this->R + 0;
	this->G = (li.G >= 0) ? ((this->G + li.G > 1) ? 1 : this->G + li.G) : this->G + 0;
	this->B = (li.B >= 0) ? ((this->B + li.B > 1) ? 1 : this->B + li.B) : this->B + 0;
}

LightIntensity LightIntensity::operator*(float num) {
	return LightIntensity(this->R * num, this->G * num, this->B * num);
}

LightIntensity LightIntensity::operator+(LightIntensity& li) {
	return LightIntensity(this->R + li.R, this->G + li.G, this->B + li.B);
}

LightIntensity LightIntensity::operator-(LightIntensity& li) {
	return LightIntensity(this->R - li.R, this->G - li.G, this->B - li.B);
}

LightIntensity LightIntensity::operator/(float li) {
	if (li == 0) {
		return LightIntensity(0, 0, 0);
	}
	return LightIntensity(this->R / li, this->G / li, this->B / li);
}

bool LightIntensity::operator!=(const LightIntensity& li) {
	if (this->R != li.R || this->G != li.G || this->B != li.B) {
		return false;
	}
	else {
		return true;
	}
}

std::ostream& operator<<(std::ostream& str, LightIntensity& li) {
	str << "[ " << li.R << ", " << li.G << ", " << li.B << "]";
	return str;
}

bool operator==(const LightIntensity& lhs, const LightIntensity& rhs)
{
	if (lhs.R == rhs.R && lhs.G == rhs.G && lhs.B == rhs.B)
	{
		return true;
	}
	return false;
}

void LightIntensity::operator/=(const float& li) {
	if (li != 0.0f)
	{
		this->R /= li;
		this->G /= li;
		this->B /= li;
	}
	else
	{
		this->R = this->G = this->B = 0.0f;
	}
}

float LightIntensity::calculateDifference(const LightIntensity& other) {
	float diff = this->R - other.R;
	float temp = this->G - other.G;
	if (temp > diff) {
		diff = temp;
	}
	temp = this->B - other.B;
	if (temp > diff) {
		diff = temp;
	}
	return diff;
}
