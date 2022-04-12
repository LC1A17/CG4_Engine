#pragma once

#include "DxInit.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugText.h"
#include "Sound.h"
#include "Camera.h"
#include "CollisionPrimitive.h"

//ゲームシーン
class GameScene
{
private://エイリアス
	//Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://構造体
	//ループ分岐用
	enum Scene
	{
		Title, Game, Clear, GameOver
	};

private://静的メンバ変数
	static const int debugTextTexNumber = 0;

public://メンバ関数
	//コンストラクタ
	GameScene();

	//デストラクタ
	~GameScene();

	//初期化処理
	void Initialize(DxInit* dxInit, Input* input, Sound* sound);

	//更新処理
	void Update();

	//描画処理
	void Draw();

private://メンバ変数
	DxInit* dxInit = nullptr;
	Input* input = nullptr;
	Sound* sound = nullptr;
	Model* model = nullptr;
	Camera* camera = nullptr;
	DebugText debugText;

	Sound::SoundData soundData1;//BGM
	Sound::SoundData se0;//SE
	Sound::SoundData se1;//SE
	Sound::SoundData se2;//SE
	Sound::SoundData se3;//SE
	Sound::SoundData se4;//SE

	Sprite* back = nullptr;//背景

	Object3d* Obj = nullptr;//オブジェクト1
	Object3d* Obj2 = nullptr;//オブジェクト2

	XMFLOAT3 eye = { 0, 10, -50 };//カメラ座標
	XMFLOAT3 pPos = { 0, 0, 0 };//プレイヤー座標
};