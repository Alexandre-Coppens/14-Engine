#ifndef INPUTS_H
#define INPUTS_H

#include <map>
#include <SDL.h>

class Inputs
{
private:
	static std::map<int, uint16_t> mKeyTime;
	static std::map<int, bool> mKeyDown;
	static std::map<int, bool> mKeyHold;
	static std::map<int, bool> mKeyUp;
	static bool mEventQuit;

public:
	Inputs() = default;
	Inputs(const Inputs&) = delete;
	Inputs& operator= (const Inputs&) = delete;

	static void ComputeInputs();
	static void SortInput(SDL_Event& _event);
	static void FlushLateInputs();

	static bool GetKey(int _key);
	static bool GetKeyDown(int _key);
	static bool GetKeyHold(int _key);
	static bool GetKeyUp(int _key);

	static bool GetEventQuit() { return mEventQuit; }
};

#endif INPUTS_H