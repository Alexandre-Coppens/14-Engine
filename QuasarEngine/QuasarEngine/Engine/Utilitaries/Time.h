#ifndef TIME_H
#define TIME_H

class Time
{
public:
	Time() = default;
	Time(const Time&) = delete;
	Time& operator= (const Time&) = delete;

	static unsigned int ComputeDeltaTime();
	static void DelayTime();

	static float deltaTime;
	static float currentFrameTime;

private:
	const static unsigned int FPS = 99999;
	const static unsigned int FRAME_DELAY = 1000 / FPS;
	//Max Delta Time
	const static unsigned int MAX_DT = 500;

	//Time when current frame started
	static unsigned int u16FrameStart;
	//Last frame start time
	static unsigned int u16LastFrame;
	//Time Needed to run the loop
	static unsigned int u16FrameTime;
};

#endif