#pragma once
#define PI 3.1415926535

struct Vector {

	float xvec;
	float yvec;
	float size;
	float angle;
};

inline Vector VectorMake(float x, float y, float xx, float yy) {

	float x_vec = xx - x;
	float y_vec = yy - y;
	float _size = sqrtf(x_vec*x_vec + y_vec*y_vec);
	float _angle = acosf(x_vec/_size);

	if (y < yy) {

		_angle = 2 * PI - _angle;

	}

	return { x_vec,y_vec,_size,_angle };

}


inline RECT RectCenter(int x, int y, int w, int h) {

	return{ x - w / 2, y - h / 2, x + w / 2, y + h / 2 };
}

inline void RRect(HDC h, RECT rc) {

	Rectangle(h, rc.left, rc.top, rc.right, rc.bottom);
}

inline void REllipse(HDC h, RECT rc) {

	Ellipse(h, rc.left, rc.top, rc.right, rc.bottom);
}

inline void REllipse(HDC h, int x, int y, int r) {

	Ellipse(h, x - r, y - r, x + r, y + r);
}

inline void RLine(HDC h, int x, int y, int ex, int ey) {

	MoveToEx(h, x, y, NULL);
	LineTo(h, ex, ey);
}

inline bool IntersectRectToCircle(RECT rc, int x, int y, int radius)
{
	if ((rc.left <= x && x <= rc.right) ||
		(rc.top <= y && y <= rc.bottom))
	{
		RECT newRect = rc;
		newRect.left -= radius;
		newRect.right += radius;
		newRect.top -= radius;
		newRect.bottom += radius;

		if ((newRect.left <= x && x <= newRect.right) &&
			(newRect.top <= y && y <= newRect.bottom))
		{
			return true;
		}
	}

	POINT a = { x,y };
	POINT b = { rc.left, rc.top };
	POINT c = { rc.right, rc.top };
	POINT d = { rc.right, rc.bottom };
	POINT e = { rc.left, rc.bottom };

	Vector Q = VectorMake(a.x,a.y, b.x,b.y);
	Vector W = VectorMake(a.x,a.y, c.x,c.y);
	Vector E = VectorMake(a.x,a.y, d.x,d.y);
	Vector R = VectorMake(a.x,a.y, e.x,e.y);

	
	if (radius >= abs(Q.size))return true;
	//우상단
	if (radius >= abs(W.size))return true;
	//좌하단
	if (radius >= abs(E.size))return true;
	//우하단
	if (radius >= abs(R.size))return true;

	
	return false;
}

