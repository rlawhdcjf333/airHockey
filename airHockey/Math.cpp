#include "pch.h"
#include "Math.h"

float Math::Distance(float x, float y, float xx, float yy) {

	float distance = sqrtf((xx - x) * (xx - x) + (yy - y) * (yy - y));
	return distance;
}



float Math::GetAngle(float x, float y, float xx, float yy) {

	float w = xx - x;
	float h = yy - y;
	float dist = sqrtf(w * w + h * h);

	float angle = acosf(w / dist);

	if (y < yy) {

		angle = 2 * PI - angle;
	}

	return angle;
}

float Math::Dot(float x, float y, float x1, float y1, float x2, float y2) {

	float vector1x = x1 - x;
	float vector1y = y1 - y;

	float vector2x = x2 - x;
	float vector2y = y2 - y;

	float dotscalar = vector1x * vector2x + vector1y * vector2y;

	return dotscalar;
}

float Math::GetDotAngle(float x, float y, float x1, float y1, float x2, float y2) {

	float vector1x = x1 - x;
	float vector1y = y1 - y;

	float vector2x = x2 - x;
	float vector2y = y2 - y;

	float dotscalar = vector1x * vector2x + vector1y * vector2y;

	float vecSize1 = sqrtf(vector1x * vector1x + vector1y * vector1y);
	float vecSize2 = sqrtf(vector2x * vector2x + vector2y * vector2y);

	float angle = acosf(dotscalar/vecSize1*vecSize2);

	return angle;
}