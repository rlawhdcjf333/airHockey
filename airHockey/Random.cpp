#include "pch.h"
#include "Random.h"
#include <ctime>

Random* Random::g_instance = NULL;

Random::Random() {
	srand(time(NULL));
}