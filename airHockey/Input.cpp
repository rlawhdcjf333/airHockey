#include "pch.h"
#include "Input.h"

Input::Input() {
	ZeroMemory(mKeyDownList, sizeof(bool) * KEYMAX);
	ZeroMemory(mKeyUpList, sizeof(bool) * KEYMAX);
}

bool Input::GetKeyD(int a) {

	if (GetAsyncKeyState(a) & 0x8000) {

		if (mKeyDownList[a] == 0) {
			mKeyDownList[a] = true;
			return true;
		}
	}

	else mKeyDownList[a] = 0;

	return false;
}

bool Input::GetKeyU(int a) {

	if (GetAsyncKeyState(a) & 0x8000) {
		mKeyUpList[a] = true;

	}
	else {
		if (mKeyUpList[a] = true) {

			mKeyUpList[a] = false;
			return true;
		}
	}
	return 0;
}

bool Input::GetKey(int a) {

	if (GetAsyncKeyState(a) & 0x8000)
		return 1;

	return 0;
}

bool Input::GetTK(int a) {

	if (GetAsyncKeyState(a) & 0x0001) {
		return true;
	}

	return 0;
}