#pragma once

#define PI 3.1415926535

class Math
{

public:

	static float GetAngle(float x, float y, float xx, float yy);

	static float Distance(float x, float y, float xx, float yy);

	static float Dot(float x, float y, float x1, float y1, float x2, float y2); // x,y 내적 원점; 

	static float GetDotAngle(float x, float y, float x1, float y1, float x2, float y2);// 내적 사이각 계산;
};


