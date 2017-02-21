#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_
#include <dinput.h>
#include "GameState.h"
#include "CollisionManager.h"

class Game;

class GameData
{
public:
	float m_dt;
	unsigned char* m_prevKeyboardState;
	unsigned char* m_keyboardState;
	DIMOUSESTATE* m_mouseState;//current mouse state
	GameState m_GS; //current game state
	CollisionManager m_CM;
	//Game* m_mouse_state;

	wchar_t* charToWChar(const char* _text)
	{
		size_t size = strlen(_text) + 1;
		static wchar_t* wa = NULL;
		if (wa)
		{
			delete[] wa;
			wa = NULL;
		}
		wa = new wchar_t[size];

		mbstowcs_s(nullptr, wa, size, _text, size);
		return wa;
	}
};

#endif