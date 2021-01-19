#pragma once
class Image;

struct Handle {

	float x;
	float y;
	float r;
	float angle;
	float vecSize;

};

struct Puck {

	float x;
	float y;
	float r;
	float angle;
	float vecSize;

};

struct GoalLine {
	
	float x;
	float y;
	float w;
	float h;
	RECT rc;

};


class Main
{
	Image* mBkBuff;
	Image* mPG;
	Image* mH1;
	Image* mH2;
	Image* mPk;

private:

	GoalLine mGL;
	GoalLine mGR;

	Puck mPuck;

	Handle h1;
	Handle h2;

	Handle temp;

	int score1;
	int score2;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

