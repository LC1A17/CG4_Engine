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

//�R���X�g���N�^
GameScene::GameScene()
{

}

//�f�X�g���N�^
GameScene::~GameScene()
{
	delete(back);
	delete(lightGroup);
	delete(model);
	delete(object);
}

//����������
void GameScene::Initialize(DxInit* dxInit, Input* input, Sound* sound)
{
	//nullptr�`�F�b�N
	assert(dxInit);
	assert(input);
	assert(sound);

	this->dxInit = dxInit;
	this->input = input;
	this->sound = sound;

	//�J��������
	camera = new DebugCamera(WinInit::WIN_WIDTH, WinInit::WIN_HEIGHT, input);

	//�f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png"))
	{
		assert(0);
		return;
	}

	//�f�o�b�O�e�L�X�g������
	debugText = DebugText::GetInstance();
	debugText->Initialize(debugTextTexNumber);
	//�f�o�C�X���Z�b�g
	Object3d::SetDevice(dxInit->GetDev());
	//�J�������Z�b�g
	Object3d::SetCamera(camera);
	//�O���t�B�b�N�X�p�C�v���C������
	Object3d::CreateGraphicsPipeline();

	//��������ǉ�
	srand(time(NULL));//����������

	//�X�v���C�g�ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/image/back.png"))
	{
		assert(0);
	}

	//�w�i�X�v���C�g����
	back = Sprite::Create(1, { 0.0f,0.0f });
	back->SetSize({ 1280, 720 });
	back->SetPosition({ 0.0f, 0.0f });

	//���f�������w�肵�ăt�@�C���ǂݍ���
	model = FbxLoader::GetInstance()->LoadModelFromFile("cube");

	//3D�I�u�W�F�N�g�����ƃ��f���̃Z�b�g
	object = new Object3d;
	object->Initialize();
	object->SetModel(model);

	//�p�[�e�B�N���}�l�[�W������
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);

	//�e�N�X�`��2�Ԃɓǂݍ���
	Sprite::LoadTexture(2, L"Resources/tex1.png");

	//���C�g����
	lightGroup = LightGroup::Create();

	//�J���������_���Z�b�g
	camera->SetTarget({ 0, 20, 0 });
	camera->SetDistance(100.0f);
}

//�X�V����
void GameScene::Update()
{
	object->Update();//�I�u�W�F�N�g�X�V
	lightGroup->Update();//���C�g�X�V
	camera->Update();//�J�����X�V
	particleMan->Update();//�p�[�e�B�N���X�V
}

//�`�揈��
void GameScene::Draw()
{
	//�R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxInit->GetCmdList();

	Sprite::PreDraw(cmdList);//�X�v���C�g�`��O����
	//�����ɒǉ�
	back->Draw();//�w�i
	Sprite::PostDraw();//�X�v���C�g�`��㏈��
	dxInit->ClearDepthBuffer();//�[�x�o�b�t�@�N���A

	object->Draw(cmdList);
	//�p�[�e�B�N���̕`��
	particleMan->Draw(cmdList);

	Sprite::PreDraw(cmdList);//�X�v���C�g�`��O����
	//�����ɒǉ�
	//�f�o�b�O�e�L�X�g�̕`��
	debugText->DrawAll(cmdList);
	Sprite::PostDraw();//�X�v���C�g�`��㏈��
}