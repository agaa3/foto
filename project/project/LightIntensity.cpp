#include "LightIntensity.h"

LightIntensity::LightIntensity(const float& R, const float& G, const float& B) {
	this->R = (R > 1.0f) ? 1 : R;
	this->G = (G > 1.0f) ? 1 : G;
	this->B = (B > 1.0f) ? 1 : B;
}

void LightIntensity::operator+=(const LightIntensity& li) {
	this->R = (li.R >= 0) ? ((this->R + li.R > 1) ? 1 : this->R + li.R) : this->R + 0;
	this->G = (li.G >= 0) ? ((this->G + li.G > 1) ? 1 : this->G + li.G) : this->G + 0;
	this->B = (li.B >= 0) ? ((this->B + li.B > 1) ? 1 : this->B + li.B) : this->B + 0;
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
