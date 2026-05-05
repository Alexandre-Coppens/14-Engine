#pragma once

#include <map>
#include <SDL.h>

enum MouseButton
{
	LeftMouse = 1,
	RightMouse = 2,
	MiddleMouse = 3,
	Mouse4 = 4,
	Mouse5 = 5,
};

class Inputs
{
private:
	static std::map<int, float> mKeyTime;
	static std::map<int, bool> mKeyDown;
	static std::map<int, bool> mKeyHold;
	static std::map<int, bool> mKeyUp;

	static std::map<int, float> mMouseTime;
	static std::map<int, bool> mMouseDown;
	static std::map<int, bool> mMouseHold;
	static std::map<int, bool> mMouseUp;
	static bool mEventQuit;
	static int mMouseDeltaX, mMouseDeltaY;
	static bool getMouse;

public:
	Inputs() = default;
	Inputs(const Inputs&) = delete;
	Inputs& operator= (const Inputs&) = delete;

	static void ComputeInputs();
	static void SortInput(const SDL_Event& _event);
	static void FlushLateInputs();

	static bool GetKey(int _key);
	static bool GetKeyDown(int _key);
	static bool GetKeyHold(int _key);
	static bool GetKeyUp(int _key);

	static bool GetMouseDown(MouseButton _button);
	static bool GetMouseHold(MouseButton _button);
	static bool GetMouseUp(MouseButton _button);
	static int GetMouseDeltaX() { return mMouseDeltaX; }
	static int GetMouseDeltaY() { return mMouseDeltaY; }

	static bool GetEventQuit() { return mEventQuit; }
};