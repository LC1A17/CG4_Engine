#pragma once

#include <Windows.h>
#include <wrl.h>
#include <dinput.h>
#include <DirectXMath.h>

#define DIRECTINPUT_VERSION     0x0800//DirectInput�̃o�[�W�����w��

//���̓N���X
class Input
{
private://�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	struct MouseMove
	{
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};

public://�ÓI�����o�ϐ�
	static Input* GetInstance();

public://�����o�֐�
	//����������
	void Initialize(HINSTANCE hInstance, HWND hwnd);
	//�X�V����
	void Update();
	//�L�[����
	bool IsKey(BYTE KeyNumber);
	//�L�[����(�������s��)
	bool IsKeyTrigger(BYTE KeyNumber);
	//�L�[�̍��{�^���������`�F�b�N
	bool PushMouseLeft();
	//�L�[�̒��{�^���������`�F�b�N
	bool PushMouseMiddle();
	//�L�[�̍��{�^���g���K�[���`�F�b�N
	bool TriggerMouseLeft();
	//�L�[�̒��{�^���g���K�[���`�F�b�N
	bool TriggerMouseMiddle();
	//�}�E�X�ړ��ʂ��擾
	MouseMove GetMouseMove();

private://�����o�֐�
	Input() = default;
	Input(const Input&) = delete;
	~Input() = default;
	Input& operator=(const Input&) = delete;

private://�����o�ϐ�
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE Key[256] = {};
	BYTE OldKey[256] = {};
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 mouseStatePre = {};
};