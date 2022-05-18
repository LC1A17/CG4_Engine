#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <cstdlib>

#include "WinInit.h"

//DirectX�ėp
class DxInit
{
private://�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://�����o�֐�
	void Initialize(WinInit* WinIni);//������
	void BeforeDraw();//�`��O����
	void AfterDraw();//�`��㏈��
	void ClearRenderTarget();//�����_�[�^�[�Q�b�g�̃N���A
	void ClearDepthBuffer();//�[�x�o�b�t�@�̃N���A
	ID3D12Device* GetDev() { return dev.Get(); }//�f�o�C�X�̎擾
	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }//�R�}���h���X�g�̎擾

private://�����o�ϐ�
	//�������p
	WinInit* winini;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12Device> dev;
	ComPtr<IDXGIAdapter1> tmpAdapter;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<IDXGISwapChain4> swapchain;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	D3D12_RESOURCE_BARRIER barrierDesc{};
	
private://�����o�֐�
	void InitializeAdapter();//�A�_�v�^�̗�
	void InitializeDevice();//�f�o�C�X�̐���
	void CreateSwapChain();//�X���b�v�`�F�[��
	void InitializeCmdList();//�R�}���h���X�g
	void CreateRTV();//�����_�[�^�[�Q�b�g�r���[
	void CreateDepthBuffer();//�[�x�o�b�t�@����
	void CreateFence();//�t�F���X
};