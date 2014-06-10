#include "vector.h"
#include <math.h>

float vec2_dot_product(struct vec2 lhs, struct vec2 rhs)
{
	float r = (lhs.x * rhs.x) + (lhs.y * rhs.y);
	return r;
}

struct vec2 vec2_normalize(struct vec2 vec)
{
	float length = vec2_length(vec);
	struct vec2 normVec = {
		.x = vec.x / length,
		.y = vec.y / length
	};
	return normVec;
}

float vec2_length(struct vec2 vec)
{
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

struct vec2 vec2_substract(struct vec2 lhs, struct vec2 rhs)
{
	struct vec2 d = {
		.x = lhs.x - rhs.x,
		.y = lhs.y - rhs.y
	};

	return d;
}

struct vec2 vec2_add(struct vec2 lhs, struct vec2 rhs)
{
	struct vec2 r = {
		.x = lhs.x + rhs.x,
		.y = lhs.y + rhs.y
	};
	
	return r;
}
