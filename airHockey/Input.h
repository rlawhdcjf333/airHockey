#pragma once
#include <bitset>

#define KEYMAX 256

//Singleton; when you want to release its memory at the end of programm;
class Input
{
public:
	static Input* GetInstance() {

		static Input instance;
		return  &instance;
	}

private:

	bool mKeyUpList[KEYMAX];
	bool mKeyDownList[KEYMAX];

public:
	Input();

	bool GetKeyD(int key);
	bool GetKeyU(int key);
	bool GetTK(int key);
	bool GetKey(int key);



};

