#include "pch.h"
#include "main.h"
#include "Image.h"

void Main::Init() {

	SetTimer(g_hWnd, 1, 10, NULL);

	mBkBuff = new Image();
	mBkBuff->CreateEmpty(WINSIZEX, WINSIZEY);

	mPG = new Image();
	mPG->LoadFromFile(L"playground.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	mGL = { 111, WINSIZEY / 2, 25, 333 };
	mGR = { WINSIZEX - 113, WINSIZEY / 2, 25,333 };
	mGL.rc = RectCenter(mGL.x, mGL.y, mGL.w, mGL.h);
	mGR.rc = RectCenter(mGR.x, mGR.y, mGR.w, mGR.h);

	mPuck = { WINSIZEX / 2, WINSIZEY / 2, 20, 0, 0 };
	mPk = new Image();
	mPk->LoadFromFile(L"puck.bmp", 40, 40, true, RGB(255, 0, 255));


	h1 = { WINSIZEX - 180, WINSIZEY / 2, 30, 0,0 };
	mH1 = new Image ();
	mH1->LoadFromFile(L"h1.bmp", 60, 60, true, RGB(255, 0, 255));

	temp.x = h1.x;
	temp.y = h1.y;

	h2 = { 160, WINSIZEY / 2, 30,0,0 };
	mH2 = new Image ();
	mH2->LoadFromFile(L"h2.bmp", 60, 60, true, RGB(255, 0, 255));

	score1 = 0;
	score2 = 0;

}

void Main::Release() {

	KillTimer(g_hWnd, 1);

	Random::ReleaseInstance();

	SafeDelete(mBkBuff);
	SafeDelete(mPG);


}

void Main::Update() {

	if (Input::GetInstance()->GetKeyD(VK_ESCAPE)) exit(0);
	
	h1.x = g_mPosit.x;
	h1.y = g_mPosit.y;

	if(mPuck.y<mGL.rc.bottom and mPuck.y>mGL.rc.top) h2.y = mPuck.y;


	Vector temp2h1 = VectorMake(temp.x, temp.y, h1.x, h1.y); // 핸들이 0.01초동안 이동한 거리가 곧 스피드가 된다
	h1.vecSize = 0.75*temp2h1.size; //이 계수는 자유. 보정 계수


	if(mPuck.vecSize>0) mPuck.vecSize -= 0.44f; //바닥 마찰 계수인 척 하는 어떤 것


	Vector h12pk = VectorMake(h1.x, h1.y, mPuck.x, mPuck.y);
	Vector h22pk = VectorMake(h2.x, h2.y, mPuck.x, mPuck.y);

	

	if (h12pk.size < h1.r + mPuck.r) { //핸들 1과 퍽의 충돌 처리 및 보정

		mPuck.angle = h12pk.angle;

		if (h1.vecSize != 0) {
			mPuck.vecSize = h1.vecSize;
		}

		mPuck.x = h1.x - (h1.r + mPuck.r) * cosf(h12pk.angle+PI);
		mPuck.y = h1.y + (h1.r + mPuck.r) * sinf(h12pk.angle+PI);
		h1.x = mPuck.x - (h1.r + mPuck.r) * cosf(h12pk.angle);
		h1.y = mPuck.y + (h1.r + mPuck.r) * sinf(h12pk.angle);
	}

	if (h22pk.size < h2.r + mPuck.r) { //핸들 2과 퍽의 충돌 처리 및 보정

		mPuck.angle = 0;

		mPuck.vecSize = 20;

		mPuck.x = h2.x - (h2.r + mPuck.r) * cosf(h22pk.angle + PI);
		mPuck.y = h2.y + (h2.r + mPuck.r) * sinf(h22pk.angle + PI);
		h2.x = mPuck.x - (h2.r + mPuck.r) * cosf(h22pk.angle);
		h2.y = mPuck.y + (h2.r + mPuck.r) * sinf(h22pk.angle);
	}


	mPuck.x += mPuck.vecSize * cosf(mPuck.angle); //퍽 움직임
	mPuck.y += mPuck.vecSize * -sinf(mPuck.angle);

	if (IntersectRectToCircle(mGL.rc, mPuck.x, mPuck.y, mPuck.r)) { //스코어링

		mPuck.x = WINSIZEX / 2;
		mPuck.y = WINSIZEY / 2;
		mPuck.vecSize = 0;
		score1++;
	}

	if (IntersectRectToCircle(mGR.rc, mPuck.x, mPuck.y, mPuck.r)) {

		mPuck.x = WINSIZEX / 2;
		mPuck.y = WINSIZEY / 2;
		mPuck.vecSize = 0;
		score2++;
	}



	if (h1.y < 22 + h1.r) h1.y = 22 + h1.r;//핸들 가두기
	if (h1.y > WINSIZEY - 20 - h1.r) h1.y = WINSIZEY - 20 - h1.r;
	if (h1.x > WINSIZEX - 120 - h1.r) h1.x = WINSIZEX - 120 - h1.r;
	if (h1.x < 120+ h1.r) h1.x = 120 + h1.r;

	if (mPuck.y < 22 + mPuck.r) { mPuck.angle = 2 * PI - mPuck.angle; mPuck.y = 22 + mPuck.r; } //퍽 튕기기 및 가두기
	if (mPuck.y > WINSIZEY - 20 - mPuck.r) { mPuck.angle = 2 * PI - mPuck.angle; mPuck.y = WINSIZEY - 20 - mPuck.r; }
	if (mPuck.x > WINSIZEX - 120 - mPuck.r) {mPuck.angle = PI - mPuck.angle; mPuck.x = WINSIZEX - 120 - mPuck.r;}
	if (mPuck.x < 120 + mPuck.r) { mPuck.angle = PI - mPuck.angle; mPuck.x = 120 + mPuck.r; }


	temp.x = h1.x;
	temp.y = h1.y;

}

void Main::Render(HDC hdc) {

	HDC backDC = mBkBuff->GetHDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); {

		HBRUSH color;
		HBRUSH white;
		HPEN newP;
		HPEN black;
		HFONT newF;
		HFONT oldF;


		color = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
		white = (HBRUSH)SelectObject(backDC, color);
		RRect(backDC, RectCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY));
		SelectObject(backDC, white);
		DeleteObject(color);

		mPG->Render(backDC, 0, 0);


		mH1->Render(backDC, h1.x - 30, h1.y - 30);
		mH2->Render(backDC, h2.x - 30, h2.y - 30);

		mPk->Render(backDC, mPuck.x - 20, mPuck.y - 20);

		SetBkMode(backDC, TRANSPARENT);

		newF = CreateFontW(100, 0, 0, 0, FW_BOLD, 0,
			FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			VARIABLE_PITCH, NULL);
		oldF = (HFONT)SelectObject(backDC, newF);
		wstring sc1 = to_wstring(score1);
		TextOut(backDC, WINSIZEX - 150, 0, sc1.c_str(), sc1.size());

		wstring sc2 = to_wstring(score2);
		TextOut(backDC, 150 , 0, sc2.c_str(), sc2.size());
		SelectObject(backDC, oldF);
		DeleteObject(newF);


	}

	mBkBuff->Render(hdc, 0, 0);


}