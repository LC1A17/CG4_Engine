#pragma once

#include "DxInit.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "DebugText.h"
#include "Sound.h"
#include "DebugCamera.h"
#include "CollisionPrimitive.h"
#include "LightGroup.h"
#include <vector>

//�Q�[���V�[��
class GameScene
{
private://�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://�T�u�N���X
	//���[�v����p
	enum Scene
	{
		Title, Game, Clear, GameOver
	};

private://�ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;

public://�����o�֐�
	//�R���X�g���N�^
	GameScene();
	//�f�X�g���N�^
	~GameScene();
	//����������
	void Initialize(DxInit* dxInit, Input* input, Sound* sound);
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

private://�����o�ϐ�
	DxInit* dxInit = nullptr;
	Input* input = nullptr;
	Sound* sound = nullptr;
	DebugText* debugText;

	Model* model = nullptr;
	Object3d* object = nullptr;
	DebugCamera* camera = nullptr;
	ParticleManager* particleMan = nullptr;
	LightGroup* lightGroup = nullptr;

	Sprite* back = nullptr;//�w�i
};