#pragma once

//Singleton; when you want to release its memory as you wish;
class Random
{
	static Random* g_instance;
public:
	static Random* GetInstance(){
		if (g_instance == NULL) {
			g_instance = new Random();
		}
		return g_instance;
	}

	static void ReleaseInstance() {
		if (g_instance != NULL) {
			delete g_instance;
			g_instance = NULL;
		}
	}
public:
	Random();

	inline int RandInt(int num) { return rand() % num; }

	inline int RandInt(int a, int b) { return rand() % (b - a) + a; }
};

