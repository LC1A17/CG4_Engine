#include "WinInit.h"
#include "DxInit.h"
#include "Sound.h"
#include "GameScene.h"
#include "LightGroup.h"
#include "ParticleManager.h"
//#include "fbxsdk.h"
#include "FbxLoader.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//FbxManager* fbxManager = FbxManager::Create();

	WinInit* win = nullptr;
	DxInit* dxInit = nullptr;
	Input* input = nullptr;
	Sound* sound = nullptr;
	GameScene* gameScene = nullptr;

	//�Q�[���E�B���h�E�̍쐬
	win = new WinInit();
	win->CreateWIN();
	//DirectX����������
	dxInit = new DxInit();
	dxInit->Initialize(win);
	//���͏���������	
	input = Input::GetInstance();
	input->Initialize(win->GetInstance(), win->GetHwnd());
	//�T�E���h����������
	sound = new Sound();
	sound->Initialize();
	//�X�v���C�g����������
	Sprite::StaticInitialize(dxInit->GetDev(), WinInit::WIN_WIDTH, WinInit::WIN_HEIGHT);
	//���C�g�ÓI������
	LightGroup::StaticInitialize(dxInit->GetDev());
	//�p�[�e�B�N���}�l�[�W��������
	ParticleManager::GetInstance()->Initialize(dxInit->GetDev());
	//FBX
	FbxLoader::GetInstance()->Initialize(dxInit->GetDev());
	//GameScene
	gameScene = new GameScene();
	gameScene->Initialize(dxInit, input, sound);

	//�Q�[�����[�v
	while (true)
	{
		//���b�Z�[�W���[�v
		if (win->MessageLoop())
		{
			break;
		}

		//�X�V������������
		input->Update();//Input�X�V
		gameScene->Update();//GameScene�X�V
		//�X�V���������܂�

		//�`�揈����������
		dxInit->BeforeDraw();//�`��J�n
		gameScene->Draw();//GameScene�`��
		dxInit->AfterDraw();//�`��I��
		//�`�揈�������܂�

		//ESC�ŋ����I��
		if (input->IsKey(DIK_ESCAPE))
		{
			break;
		}
	}

	//�e����
	delete(gameScene);
	delete(sound);
	delete(dxInit);
	FbxLoader::GetInstance()->Finalize();

	//�E�B���h�E�̔j��
	win->DeleteWIN();
	delete(win);

	return 0;
}