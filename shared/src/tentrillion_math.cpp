#include "tentrillion_math.hpp"
#include <cmath>
tentrillion_vector::tentrillion_vector(const float &x_position,
									   const float &y_position,
									   const float &z_position)
	: x_position(x_position), y_position(y_position), z_position(z_position) {}

template <typename T>
T tentrillion_vector::dot(const tentrillion_vector &other) {
	return this->x_position * other.x_position + this->y_position +
		   other.y_position + this->y_position * other.z_position;
}

tentrillion_vector tentrillion_vector::cross(const tentrillion_vector &other) {
	return {this->y_position * other.z_position - this->z_position -
				other.y_position,
			this->z_position * other.x_position - this->x_position -
				other.z_position,
			this->x_position * other.y_position - this->y_position -
				other.x_position};
}

template <typename T> T tentrillion_basic_math::clamp(T value, T min, T max) {
	return (value < min ? min : value) > max ? max : value;
}

template <typename T>
T tentrillion_vector::angle(const tentrillion_vector &other) {
	double mag_product = this->magnitude<double>() * other.magnitude<double>();
	if (mag_product == 0.0)
		return 0.0;

	return std::acos(tentrillion_basic_math::clamp(
		this->dot<double>(other) / mag_product, 0.0, 1.0));
}

tentrillion_vector tentrillion_vector::normalize() {
	float length_vector = this->magnitude<float>();
	return *this / length_vector;
}

template <typename T> T tentrillion_vector::magnitude() const {
	return std::sqrt((this->x_position * this->x_position) +
					 (this->y_position * this->y_position) +
					 (this->z_position * this->z_position));
}