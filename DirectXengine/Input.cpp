#include "Input.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

Input* Input::GetInstance()
{
	static Input instance;

	return &instance;
}

//����������
void Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result = S_FALSE;

	assert(!dinput);

	//DirectInput�I�u�W�F�N�g�̐���
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);

	//�L�[�{�[�h�f�o�C�X�̐���	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);

	//�}�E�X�f�o�C�X�̐���	
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);

	//���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);//�W���`��

	//�r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	//���̓f�[�^�`���̃Z�b�g
	result = devMouse->SetDataFormat(&c_dfDIMouse2); // �W���`��

	//�r�����䃌�x���̃Z�b�g
	result = devMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

//�X�V����
void Input::Update()
{
	HRESULT result = S_FALSE;

	//�L�[�{�[�h
	//�L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();
	//�O�t���[���̃L�[���͂��R�s�[
	memcpy(OldKey, Key, sizeof(Key));
	//�S�L�[�̓��͏�Ԃ��擾����
	result = devkeyboard->GetDeviceState(sizeof(Key), Key);

	//�}�E�X
	//�}�E�X����J�n
	result = devMouse->Acquire();
	//�O��̓��͂�ۑ�
	mouseStatePre = mouseState;
	//�}�E�X�̓���
	result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);
}

//�L�[����
bool Input::IsKey(BYTE KeyNumber)
{
	//�w��L�[�������Ă����true��Ԃ�
	if (Key[KeyNumber])
	{
		return true;
	}

	//�����łȂ����false��Ԃ�
	return false;
}

//�L�[����i�������s�j
bool Input::IsKeyTrigger(BYTE KeyNumber)
{
	//�O�t���[����false�Ŏw��L�[�������Ă����true��Ԃ�
	if (!OldKey[KeyNumber] && Key[KeyNumber])
	{
		return true;
	}

	//�����łȂ����false��Ԃ�
	return false;
}

//�L�[�̍��{�^���������`�F�b�N
bool Input::PushMouseLeft()
{
	//0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[0])
	{
		return true;
	}

	//�����Ă��Ȃ�
	return false;
}

//�L�[�̒��{�^���������`�F�b�N
bool Input::PushMouseMiddle()
{
	//0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[2])
	{
		return true;
	}

	//�����Ă��Ȃ�
	return false;
}

//�L�[�̍��{�^���g���K�[���`�F�b�N
bool Input::TriggerMouseLeft()
{
	//�O��0�ŁA����0�łȂ���΃g���K�[
	if (!mouseStatePre.rgbButtons[0] && mouseState.rgbButtons[0])
	{
		return true;
	}

	//�g���K�[�łȂ�
	return false;
}

//�L�[�̒��{�^���g���K�[���`�F�b�N
bool Input::TriggerMouseMiddle()
{
	//�O��0�ŁA����0�łȂ���΃g���K�[
	if (!mouseStatePre.rgbButtons[2] && mouseState.rgbButtons[2])
	{
		return true;
	}

	//�g���K�[�łȂ�
	return false;
}

//�}�E�X�ړ��ʂ��擾
Input::MouseMove Input::GetMouseMove()
{
	MouseMove tmp;
	tmp.lX = mouseState.lX;
	tmp.lY = mouseState.lY;
	tmp.lZ = mouseState.lZ;
	return tmp;
}