#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

#include "Model.h"
#include "Camera.h"

//3D�I�u�W�F�N�g
class Object3d
{
protected://�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����(���W�ϊ��s��p)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;//�r���[�v���W�F�N�V�����s��
		XMMATRIX world;//���[���h�s��
		XMFLOAT3 cameraPos;//�J�������W(���[���h���W)
	};

public://�ÓI�����o�֐�
	//setter
	static void SetDevice(ID3D12Device* dev) { Object3d::dev = dev; }
	static void SetCamera(Camera* camera) { Object3d::camera = camera; }
	//�O���t�B�b�N�X�p�C�v���C���̐���
	static void CreateGraphicsPipeline();

private://�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* dev;
	//�J����
	static Camera* camera;
	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;

public://�����o�֐�
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���f���̃Z�b�g
	void SetModel(Model* model) { this->model = model; }
	//���W�̎擾
	const XMFLOAT3& GetPosition() { return position; }
	//���W�̐ݒ�
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	//��]�̎擾
	const XMFLOAT3& GetRotation() { return rotation; }
	//��]�̐ݒ�
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }
	//�X�P�[���̎擾
	const XMFLOAT3& GetScale() { return scale; }
	//�X�P�[���̐ݒ�
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

protected://�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform;
	//���[�J���X�P�[��
	XMFLOAT3 scale = { 1, 1, 1 };
	//X, Y, Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0, 0, 0 };
	//���[�J�����W
	XMFLOAT3 position = { 0, 0, 0 };
	//���[�J�����[���h�ϊ��s��
	XMMATRIX matworld;
	//���f��
	Model* model = nullptr;
};