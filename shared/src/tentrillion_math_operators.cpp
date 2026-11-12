#include "tentrillion_math.hpp"
#include <cmath>

/**
 * These are the generator preprocessors for the TenTrillion Math Library
 * Operators for Vector3. To make the code less long, these have been put in and
 * simplify the functions.
 *
 * F type operators are ones that use 'float' as the obj.
 * R type operators are ones that affect the current instance of the object and
 * return the reference.
 */

/**
 * @brief Create an operator overload template with the operator being the
 * 'operator' and the Vector object being 'obj'.
 *
 */
#define TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE(operator, obj)           \
	tentrillion_vector {                                                       \
		this->x_position operator obj.x_position,                              \
			this->y_position operator obj.y_position,                          \
			this->z_position operator obj.z_position                           \
	}

/**
 * @brief Create an operator overload template with the operator being the
 * 'operator' and the Float object being 'obj'. The 'obj' keyword will affect
 * all axes or coordinates of the vector.
 *
 */
#define TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_F(operator, obj)         \
	tentrillion_vector {                                                       \
		this->x_position operator obj, this->y_position operator obj,          \
			this->z_position operator obj                                      \
	}

/**
 * @brief Create an operator overload template that affects the current instance
 * with the operator being the 'operator' and the Vector object being 'obj'.
 *
 */
#define TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_R(operator, obj)         \
	this->x_position operator obj.x_position;                                  \
	this->y_position operator obj.y_position;                                  \
	this->z_position operator obj.z_position;                                  \
	return *this;

/**
 * @brief Create an operator overload template that affects the current instance
 * with the operator being the 'operator' and the Float object being 'obj'. The
 * 'obj' keyword will affect all axes or coordinates of the Vector.
 *
 */
#define TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_R_F(operator, obj)       \
	this->x_position operator obj;                                             \
	this->y_position operator obj;                                             \
	this->z_position operator obj;                                             \
	return *this;

tentrillion_vector &
tentrillion_vector::operator*=(const tentrillion_vector &other){
	TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_R(*=, other)}

tentrillion_vector &tentrillion_vector::operator+=(
	const tentrillion_vector &other){
	TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_R(+=, other)}

tentrillion_vector &tentrillion_vector::operator-=(
	const tentrillion_vector &other){
	TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_R(-=, other)}

tentrillion_vector &tentrillion_vector::operator/=(
	const tentrillion_vector &other){
	TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_R(/=, other)}

tentrillion_vector &tentrillion_vector::operator*=(const float &other){
	TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_R_F(*=, other)}

tentrillion_vector &tentrillion_vector::operator+=(const float &other){
	TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_R_F(+=, other)}

tentrillion_vector &tentrillion_vector::operator-=(const float &other){
	TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_R_F(-=, other)}

tentrillion_vector &tentrillion_vector::operator/=(const float &other){
	TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_R_F(/=, other)}

tentrillion_vector tentrillion_vector::operator*(const float &other) {
	return TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_F(*, other);
}

tentrillion_vector tentrillion_vector::operator/(const float &other) {
	return TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_F(/, other);
}

tentrillion_vector tentrillion_vector::operator+(const float &other) {
	return TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_F(+, other);
}

tentrillion_vector tentrillion_vector::operator-(const float &other) {
	return TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE_F(-, other);
}

tentrillion_vector
tentrillion_vector::operator*(const tentrillion_vector &other) {
	return TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE(*, other);
}
tentrillion_vector
tentrillion_vector::operator-(const tentrillion_vector &other) {
	return TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE(-, other);
}

tentrillion_vector
tentrillion_vector::operator+(const tentrillion_vector &other) {
	return TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE(-, other);
}

tentrillion_vector
tentrillion_vector::operator/(const tentrillion_vector &other) {
	return TENTRILLION_CREATE_OPERATOR_OVERLOAD_TEMPLATE(/, other);
}