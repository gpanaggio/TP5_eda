#pragma once
#include <chrono>

// Esta libreria es el timer, basicamente se guarda la hora en dos momentos distintos (start y stop) y despues te devuelve el tiempo entre
// esas dos funciones

#define TIMERERROR (-1)

class Timer
{
public:
	Timer();
	~Timer();
	void start();
	void stop();
	float getTime(); // In ms
private:
	std::chrono::high_resolution_clock::time_point  startValue;
	bool getStartValue;
	std::chrono::high_resolution_clock::time_point  stopValue;
	bool getStopValue;
	std::chrono:: duration<float> timePassed;
};

