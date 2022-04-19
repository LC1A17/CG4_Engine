#include "GameScene.h"
#include "Model.h"
#include "Collision.h"
#include "FbxLoader.h"

#include <cassert>
#include <sstream>
#include <iomanip>

#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace Microsoft;
using namespace std;
using namespace DirectX;

//コンストラクタ
GameScene::GameScene()
{

}

//デストラクタ
GameScene::~GameScene()
{
	delete(back);
	delete(Obj);
	delete(Obj2);
}

//初期化処理
void GameScene::Initialize(DxInit* dxInit, Input* input, Sound* sound)
{
	//nullptrチェック
	assert(dxInit);
	assert(input);
	assert(sound);

	this->dxInit = dxInit;
	this->input = input;
	this->sound = sound;

	//デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png"))
	{
		assert(0);
		return;
	}

	//デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	//ここから追加
	srand(time(NULL));//乱数初期化

	//スプライト読み込み
	if (!Sprite::LoadTexture(1, L"Resources/image/back.png"))
	{
		assert(0);
	}

	//背景スプライト生成
	back = Sprite::Create(1, { 0.0f,0.0f });
	back->SetSize({ 1280, 720 });
	back->SetPosition({ 0.0f, 0.0f });

	//モデル読み込み、生成
	//モデル1
	model = model->CreateFromOBJ("player");
	Obj = Object3d::Create();
	Obj->SetModel(model);
	Obj->SetPosition({ 20, posY, 0 });
	Obj->SetScale({ 2, 2, 2 });

	//モデル2
	model = model->CreateFromOBJ("enemy");
	Obj2 = Object3d::Create();
	Obj2->SetModel(model);
	Obj2->SetPosition({ posX2, posY2, 0 });
	Obj2->SetScale({ 2, 2, 2 });

	//BGM.SE読み込み
	//soundData1 = sound->SoundLoadWave("Resources/sound/BGM.wav");
	//se0 = sound->SoundLoadWave("Resources/sound/SE0.wav");
	//se1 = sound->SoundLoadWave("Resources/sound/SE1.wav");
	//se2 = sound->SoundLoadWave("Resources/sound/SE2.wav");
	//se3 = sound->SoundLoadWave("Resources/sound/SE3.wav");
	//se4 = sound->SoundLoadWave("Resources/sound/SE4.wav");
	//sound->SoundPlayWave(soundData1);//サウンド再生

	//モデルを指定してファイル読み込み
	FbxLoader::GetInstance()->LoadModelFromFile("cube");

	camera->Update();//カメラ更新処理
}

//更新処理
void GameScene::Update()
{
	//ここに追加

	//1で自由落下
	if (input->IsKeyTrigger(DIK_1))
	{
		isFall = true;
	}

	//2で斜方投射
	if (input->IsKeyTrigger(DIK_2))
	{
		isFall2 = true;
	}

	//Rでリセット
	if (input->IsKeyTrigger(DIK_R))
	{
		t = 0.0f;
		t2 = 0.0f;
		isFall = false;
		isFall2 = false;
		Obj->SetPosition({ 20, posY, 0 });
		Obj2->SetPosition({ posX2, posY2, 0 });
	}

	//自由落下移動処理
	if (isFall)
	{
		t += 0.1f;
		fallY = -(4 * t + 0.5 * 9.8 * t * t);
		Obj->SetPosition({ 20, posY + fallY, 0 });

		if (t >= 20.0f)
		{
			t = 0;
			isFall = false;
			Obj->SetPosition({ 20, posY, 0 });
		}
	}

	//斜方投射移動処理
	if (isFall2)
	{
		t2 += 0.1f;
		fallX2 = 10 * t2;
		fallY2 = 20 * t2 + 0.5 * -9.8 * t2 * t2;
		Obj2->SetPosition({ posX2 + fallX2, posY2 + fallY2, 0 });

		if (t2 >= 20.0f)
		{
			t2 = 0;
			isFall2 = false;
			Obj2->SetPosition({ posX2, posY2, 0 });
		}
	}

	/*
	//WASDでプレイヤー移動
	if (input->IsKey(DIK_W))
	{
		pPos.y++;
	}
	if (input->IsKey(DIK_S))
	{
		pPos.y--;
	}
	if (input->IsKey(DIK_A))
	{
		pPos.x--;
	}
	if (input->IsKey(DIK_D))
	{
		pPos.x++;
	}

	Obj->SetPosition({ pPos });//プレイヤー座標更新

	//十字キーでカメラ移動
	if (input->IsKey(DIK_UP))
	{
		eye.y++;
	}
	if (input->IsKey(DIK_DOWN))
	{
		eye.y--;
	}
	if (input->IsKey(DIK_LEFT))
	{
		eye.x--;
	}
	if (input->IsKey(DIK_RIGHT))
	{
		eye.x++;
	}

	//SPACEキーで効果音
	if (input->IsKeyTrigger(DIK_SPACE))
	{
		int a = rand() % 5;//乱数生成

		if (a == 0)
		{
			sound->SoundPlayWave(se0);//サウンド再生
		}
		else if (a == 1)
		{
			sound->SoundPlayWave(se1);//サウンド再生
		}
		else if (a == 2)
		{
			sound->SoundPlayWave(se2);//サウンド再生
		}
		else if (a == 3)
		{
			sound->SoundPlayWave(se3);//サウンド再生
		}
		else
		{
			sound->SoundPlayWave(se4);//サウンド再生
		}
	}
	*/

	camera->SetEye(eye);//カメラ座標更新

	camera->Update();//カメラ更新処理
	
	//オブジェクト更新処理
	Obj->Update();
	Obj2->Update();
}

//描画処理
void GameScene::Draw()
{
	//コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxInit->GetCmdList();

	Sprite::PreDraw(cmdList);//スプライト描画前処理

	//ここに追加
	back->Draw();//背景

	Sprite::PostDraw();//スプライト描画後処理
	dxInit->ClearDepthBuffer();//深度バッファクリア

	Object3d::PreDraw(cmdList);//3Dオブジェクト描画前処理
	
	//ここに追加
	Obj->Draw();
	Obj2->Draw();

	Object3d::PostDraw();//3Dオブジェクト描画後処理

	Sprite::PreDraw(cmdList);//スプライト描画前処理

	//ここに追加

	debugText.DrawAll(cmdList);//デバッグテキストの描画
	Sprite::PostDraw();//スプライト描画後処理
}