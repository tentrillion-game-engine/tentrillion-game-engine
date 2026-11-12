/**
 * This is the Math library for the TenTrillion.
 * Allowing you to do Vector, Trigonometry and other Mathematical operations.
 */

#ifndef TENTRILLIONGAMEENGINE_TENTRILLIONMATH_HPP
#define TENTRILLIONGAMEENGINE_TENTRILLIONMATH_HPP

#include <cmath>

/**
 * @brief The TenTrillion Basic Math Class.
 *
 */
class tentrillion_basic_math {
  public:
	/**
	 * @brief Clamp value between the two values specified by the type
	 * parameter.
	 *
	 * @tparam T The typename to use when doing a clamp operation.
	 * @param value The current value of the object.
	 * @param min The minimum value of the object.
	 * @param max The maximum value of the object.
	 * @return T The object, clamped between minimum and maximum values.
	 */
	template <typename T> static T clamp(T value, T min, T max);
};

/**
 * @brief TenTrillion Vector Operations.
 * TODO: Also add typename T for the Vector itself, further making the compiler
 * optimize the code.
 */

class tentrillion_vector {
  public:
	/**
	 * @brief Construct a new tentrillion vector object
	 *
	 * @param x_position The X-Coordinate of this Vector.
	 * @param y_position The Y-Coordinate of this Vector.
	 * @param z_position The Z-Coordinate of this Vector.
	 */
	tentrillion_vector(const float &x_position, const float &y_position,
					   const float &z_position);

	/**
	 * @brief The X-coordinate of this Vector.
	 *
	 */
	float x_position;
	/**
	 * @brief The Y-coordinate of this Vector.
	 *
	 */
	float y_position;
	/**
	 * @brief The Z-coordinate of this Vector.
	 *
	 */
	float z_position;

	/**
	 * @brief This normalizes the current Vector and returns the result.
	 *
	 * @return tentrillion_vector The normalized Vector, or a Unit Vector.
	 */
	tentrillion_vector normalize();

	/**
	 * @brief Get the length of the specified Vector in use for normalization
	 * and other operations.
	 *
	 * @return float Length of this Vector.
	 */
	template <typename T> T magnitude() const;

	/**
	 * @brief Returns the dot-product of two Vectors.
	 *
	 * @param other The other Vector.
	 * @return The dot product of the two Vectors.
	 */
	template <typename T> T dot(const tentrillion_vector &other);

	/**
	 * @brief Returns the cross-product of two Vectors.
	 *
	 * @param other The other Vector.
	 * @return tentrillion_vector The cross product of the two Vectors.
	 */
	tentrillion_vector cross(const tentrillion_vector &other);

	/**
	 * @brief Calculate the angle between two Vectors.
	 *
	 * @param other The other Vector.
	 * @return float The angle between the two Vectors by the dot and cross
	 * products.
	 */
	template <typename T> T angle(const tentrillion_vector &other);

	/**
	 * @brief Addition with another Vector.
	 *
	 */
	tentrillion_vector operator+(const tentrillion_vector &other);

	/**
	 * @brief Addition with a float.
	 *
	 */
	tentrillion_vector operator+(const float &other);

	/**
	 * @brief Subtraction with another Vector.
	 *
	 */
	tentrillion_vector operator-(const tentrillion_vector &other);

	/**
	 * @brief Subtraction with a float.
	 *
	 */
	tentrillion_vector operator-(const float &other);

	/**
	 * @brief Division with another Vector.
	 *
	 */
	tentrillion_vector operator/(const tentrillion_vector &other);

	/**
	 * @brief Division with a float.
	 *
	 */
	tentrillion_vector operator/(const float &other);

	/**
	 * @brief Multiplication with another Vector.
	 *
	 */
	tentrillion_vector operator*(const tentrillion_vector &other);

	/**
	 * @brief Multiplication with a float.
	 *
	 */
	tentrillion_vector operator*(const float &other);

	/**
	 * @brief Addition with another Vector.
	 *
	 */
	tentrillion_vector &operator+=(const tentrillion_vector &other);

	/**
	 * @brief Addition with a float.
	 *
	 */
	tentrillion_vector &operator+=(const float &other);

	/**
	 * @brief Subtraction with another Vector.
	 *
	 */
	tentrillion_vector &operator-=(const tentrillion_vector &other);

	/**
	 * @brief Subtraction with a float.
	 *
	 */
	tentrillion_vector &operator-=(const float &other);

	/**
	 * @brief Division with another Vector.
	 *
	 */
	tentrillion_vector &operator/=(const tentrillion_vector &other);

	/**
	 * @brief Division with a float.
	 *
	 */
	tentrillion_vector &operator/=(const float &other);

	/**
	 * @brief Multiplication with another Vector.
	 *
	 */
	tentrillion_vector &operator*=(const tentrillion_vector &other);

	/**
	 * @brief Multiplication with a float.
	 *
	 */
	tentrillion_vector &operator*=(const float &other);
};

/**
 * @brief TenTrillion Quaternion Operations.
 *
 */
class tentrillion_quaternion {};

#endif