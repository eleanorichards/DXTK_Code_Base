#ifndef _GAME_H_
#define _GAME_H_
//=================================================================
//Basic Game Manager Class
//=================================================================

#include <windows.h>
#include <list>
#include <dinput.h>
#include "Effects.h"
#include "CommonStates.h"
#include "terrain.h"
#include "GameData.h"
#include <Mouse.h>
#include "TPSCamera.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "CollisionManager.h"
#include <string>

using std::list;
using std::unique_ptr;
using namespace DirectX;

// Forward declarations
class GameObject;
class Camera;
class Vehicle;
class EnemyManager;

class Game
{
public:

	Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance);
	virtual ~Game();

	bool Tick(); //tick the game state
	//virtual void tick(GameData* _GD);

	void Draw(ID3D11DeviceContext* _pd3dImmediateContext); //render the current game state
	void detectCollision();
	bool ReadKeyboard();
	bool ReadMouse();


protected:
	DWORD m_playTime; //amount of time since the game started

	//spritebatch things
	unique_ptr<SpriteBatch>		m_Sprites;
	unique_ptr<SpriteFont>		m_Font;


	Camera* m_cam; //principle camera
	TPSCamera* tp_cam;
	list<GameObject *> m_GameObjects; //data structure storing all GameObjects of this Game
	HWND m_hWnd;

	//input stuff
	IDirectInput8* m_pDirectInput;
	IDirectInputDevice8* m_pKeyboard;
	IDirectInputDevice8* m_mouse;
	unsigned char m_keyboardState[256];
	unsigned char m_prevKeyboardState[256];

	DIMOUSESTATE  m_mouseState;


	//required for the CMO model rendering system
	CommonStates* m_states;
	IEffectFactory* m_fxFactory;
	GameData* m_GD;
	Vehicle* pVehicle;
	EnemyManager* pEnemyManager;
	//string vehicleScore;
};


#endif