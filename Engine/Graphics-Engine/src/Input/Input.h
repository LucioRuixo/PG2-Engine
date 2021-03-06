#ifndef INPUT_H
#define INPUT_H

#include "Tools/Includes.h"
#include "Window/Window.h"

enum PrintableKey
{
	SPACE = 32,
	APOSTROPHE = 39,
	COMMA = 44,
	MINUS,
	PERIOD,
	SLASH,
	ZERO = 48,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	SEMICOLON = 59,
	EQUAL = 61,
	A = 65,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	LEFT_BRACKET,
	BACKSLASH,
	RIGHT_BRACKET,
	GRAVE_ACCENT = 96,
	WORLD_1 = 161,
	WORLD_2
};

enum FunctionKey
{
	ESCAPE = 256,
	ENTER,
	TAB,
	BACKSPACE,
	INSERT,
	DELETE,
	RIGHT,
	LEFT,
	DOWN,
	UP,
	PAGE_UP,
	PAGE_DOWN,
	HOME,
	END,
	CAPS_LOCK = 280,
	SCROLL_LOCK,
	NUM_LOCK,
	PRINT_SCREEN,
	PAUSE,
	F1 = 290,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	F16,
	F17,
	F18,
	F19,
	F20,
	F21,
	F22,
	F23,
	F24,
	F25,
	KP_0 = 320,
	KP_1,
	KP_2,
	KP_3,
	KP_4,
	KP_5,
	KP_6,
	KP_7,
	KP_8,
	KP_9,
	KP_DECIMAL,
	KP_DIVIDE,
	KP_MULTIPLY,
	KP_SUBTRACT,
	KP_ADD,
	KP_ENTER,
	KP_EQUAL,
	LEFT_SHIFT = 340,
	LEFT_CONTROL,
	LEFT_ALT,
	LEFT_SUPER,
	RIGHT_SHIFT,
	RIGHT_CONTROL,
	RIGHT_ALT,
	RIGHT_SUPER,
	MENU
};

class GENGINE_API Input
{
	Window* window;
public:
	Input(Window* _window);
	~Input();
	bool getKeyPress(PrintableKey key);
	bool getKeyPress(FunctionKey key);
	bool getKeyRelease(PrintableKey key);
	bool getKeyRelease(FunctionKey key);
};

#endif // !INPUT_H