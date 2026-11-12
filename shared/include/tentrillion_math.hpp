#ifndef TENTRILLIONGAMEENGINE_TENTRILLIONMATH_HPP
#define TENTRILLIONGAMEENGINE_TENTRILLIONMATH_HPP

/**
 * @brief This is the Math library for the TenTrillion.
 * This is for basic Vector, Quaternion operations.
 * Along with a more optimized division and multiplication operation.
 *
 */

#include <cstdint>

/**
 * @brief TenTrillion Vector Operations.
 *
 */
class tentrillion_vector {
  public:
	/**
	 * @brief The X-coordinate of this Vector.
	 *
	 */
	uint32_t x_position;
	/**
	 * @brief The Y-coordinate of this Vector.
	 *
	 */
	uint32_t y_position;
	/**
	 * @brief The Z-coordinate of this Vector.
	 *
	 */
	uint32_t z_position;
};

/**
 * @brief TenTrillion Quaternion Operations.
 *
 */
class tentrillion_quaternion {};

#endif