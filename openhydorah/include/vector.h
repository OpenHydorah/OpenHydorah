/**
 * \file vector.h
 */

#ifndef OPENHYDORAH_VECTOR_H
#define OPENHYDORAH_VECTOR_H

/**
 * \struct vec2
 *
 * A 2-dimensional vector
 */
struct vec2 {
	float x;
	float y;
};

/**
 * \brief Returns the Dot product of two 2D vectors
 *
 * \param[in] lhs Left-hand side vector
 * \param[in] rhs Right-hand side vector
 *
 * \return The dot product
 */
float vec2_dot_product(struct vec2 lhs, struct vec2 rhs);

/**
 * \brief Returns the normalized 2D vector
 *
 * \param[in] vec The vector to normalize
 *
 * \return The normalized version of vec
 */
struct vec2 vec2_normalize(struct vec2 vec);

float vec2_length(struct vec2 vec);

struct vec2 vec2_substract(struct vec2 lhs, struct vec2 rhs);

struct vec2 vec2_add(struct vec2 lhs, struct vec2 rhs);

#endif
