#include "Game.h"
#include "gameobject.h"
#include "camera.h"
#include "SimpleMath.h"
#include "CMOGO.h"
#include "Vehicle.h"
#include "Gun.h"
#include "EnemyGun.h"
#include <dinput.h>
#include "EnemyManager.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

Game::Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance) 
{
	m_hWnd = _hWnd;
	m_GD = new GameData;
	m_GD->m_keyboardState = m_keyboardState;
	m_GD->m_prevKeyboardState = m_prevKeyboardState;
	m_GD->m_mouseState = &m_mouseState;
	m_pKeyboard = nullptr;
	m_pDirectInput = nullptr;
	m_mouse = nullptr;
	//set up DirectXTK Effects system
	m_fxFactory = new EffectFactory(_pd3dDevice);
	//Hide the mouse pointer
	ShowCursor(false);
	//Tell the fxFactory to look to the correct build directory to pull stuff in from
#ifdef DEBUG
	((EffectFactory*)m_fxFactory)->SetDirectory(L"../Debug");
#else
	((EffectFactory*)m_fxFactory)->SetDirectory(L"../Release");
#endif

	// Create other render resources here
	m_states = new CommonStates(_pd3dDevice);

	//find how big my window is to correctly calculate my aspect ratio
	RECT rc;
	GetClientRect(_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	float AR = (float)width / (float)height;

	//Direct Input Stuff
	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&m_pDirectInput, NULL);
	hr = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
	hr = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = m_pKeyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND |
		DISCL_NONEXCLUSIVE);

	//Direct Mouse input stuff
	hr = m_pDirectInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	hr = m_mouse->SetDataFormat(&c_dfDIMouse);
	hr = m_mouse->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND |
		DISCL_NONEXCLUSIVE);

	
	//load in the objects

	Terrain* pTerrain = new Terrain("terrain.cmo", _pd3dDevice, m_fxFactory,Vector3(0.0f, -13.0f, 0.0f), 0.0f, 0.0f, 0.0f, 5*Vector3::One);
	m_GameObjects.push_back(pTerrain);

	pVehicle = new Vehicle("goblin_fbx.cmo", _pd3dDevice, m_fxFactory, Vector3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.1*Vector3::One, 10.0f);
	m_GameObjects.push_back(pVehicle);

	Gun* pGun = new Gun("laser gun.cmo", _pd3dDevice, m_fxFactory, pVehicle, "goblin_fbx.cmo", 10.0f, 0.0f, -5.0f, 0.0f, 4*Vector3::One);
	m_GameObjects.push_back(pGun);

	pEnemyManager = new EnemyManager(10, "FSM.cmo", _pd3dDevice, m_fxFactory, pGun);
	m_GameObjects.push_back(pEnemyManager);

	for each (Enemy* enemy in pEnemyManager->GetEnemy())
	{
		EnemyGun* pEnemyGun = new EnemyGun("laser gun.cmo", _pd3dDevice, m_fxFactory, enemy, "goblin_fbx.cmo", 10.0f, 0.0f, -5.0f, 0.0f, 0.1*Vector3::One, pVehicle);
		m_GameObjects.push_back(pEnemyGun);

	}
	
	//create a base camera
	m_cam = new Camera(0.25f * XM_PI, AR, 1.0f, 10000.0f, Vector3::Zero, Vector3::Up);
	m_cam->SetPos(Vector3(0.0f, 700.0f, 10.0f));
	m_GameObjects.push_back(m_cam);
	
	//follow camera
	tp_cam = new TPSCamera(0.25f * XM_PI, AR, 1.0f, 10000.0f, pVehicle, Vector3::Up, Vector3(0.0f, 50.0f, -100.0f));
	m_GameObjects.push_back(tp_cam);

	//DirectX Spritebatch for UI
	ID3D11DeviceContext* pd3dImmediateContext;
	_pd3dDevice->GetImmediateContext(&pd3dImmediateContext);
	m_Sprites.reset(new SpriteBatch(pd3dImmediateContext));
	m_Font.reset(new SpriteFont(_pd3dDevice, L"italic.spritefont"));



};


bool Game::ReadKeyboard()
{
	//copy over old keyboard state
	memcpy(m_prevKeyboardState, m_keyboardState, sizeof(unsigned char) * 256);
	//clear out previous state
	ZeroMemory(&m_keyboardState, sizeof(m_keyboardState));
	// Read the keyboard device.
	HRESULT hr = m_pKeyboard->GetDeviceState(sizeof(m_keyboardState),
		(LPVOID)&m_keyboardState);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_pKeyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Game::ReadMouse()
{
	//clear out previous state
	ZeroMemory(&m_mouseState, sizeof(m_mouseState));
	// Read the keyboard device.
	HRESULT hr = m_mouse->GetDeviceState(sizeof(m_mouseState),
		(LPVOID)&m_mouseState);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
};


Game::~Game() 
{
	if (m_pKeyboard)
	{
		m_pKeyboard->Unacquire();
		m_pKeyboard->Release();
	}


	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
	}

	if (m_pDirectInput) m_pDirectInput->Release();
	//get rid of the game objects here
	for (list<GameObject *>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		delete (*it);
	}
	m_GameObjects.clear();

	delete m_GD;
};



bool Game::Tick() 
{ 
	//poll Keyboard
	ReadKeyboard();
	ReadMouse();
	//On pressing Escape send signal back to Application class to shutdown
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return false;
	}

	//change camera view using space
	if ((m_keyboardState[DIK_E] & 0x80) && !(m_prevKeyboardState[DIK_E] & 0x80))
	{
		if (m_GD->m_GS == GS_PLAY_MAIN_CAM)
		{
			m_GD->m_GS = GS_PLAY_TPS_CAM;
		}
		else
		{
			m_GD->m_GS = GS_PLAY_MAIN_CAM;
		}
	}

	if (m_mouseState.rgbButtons[0] & 0x80)
	{
		//return false;
	}

	RECT window;
	GetWindowRect(m_hWnd, &window);
	SetCursorPos(0.5*(window.left + window.right), 0.5*(window.bottom + window.top));

	//calculate frame time-step dt for passing down to game objects
	DWORD currentTime = GetTickCount();
	m_GD->m_dt = min((float)(currentTime - m_playTime) / 1000.0f, 0.1f);
	m_playTime = currentTime;
	
	//update all objects
	for (list<GameObject *>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Tick(m_GD);
	}
		
	return true; 
};



void Game::Draw(ID3D11DeviceContext* _pd3dImmediateContext) 
{
	Camera* useCam = tp_cam;

	if (m_GD->m_GS == GS_PLAY_MAIN_CAM)
	{
		useCam = m_cam;
	}
	
	for (list<GameObject *>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Draw(_pd3dImmediateContext, m_states, useCam);
	}	

	

	// Draw sprite batch stuff
	std::string vehicleScore = std::to_string(pVehicle->getPlayerScore());
	//draw player score
	m_Sprites->Begin();
	m_Font->DrawString(m_Sprites.get(), m_GD->charToWChar(vehicleScore.c_str()), XMFLOAT2(500, 20),
		Colors::ForestGreen);
	m_Sprites->End();

	std::string enemyScore = std::to_string(pEnemyManager->getEnemyScore());
	//draw enemy score
	m_Sprites->Begin();
	m_Font->DrawString(m_Sprites.get(), m_GD->charToWChar(enemyScore.c_str()), XMFLOAT2(20, 20),
		Colors::ForestGreen);
	m_Sprites->End();
};

void Game::detectCollision()
{

};
