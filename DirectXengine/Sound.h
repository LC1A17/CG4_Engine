#pragma once

#include <Windows.h>
#include <xaudio2.h>
#include <wrl.h>

//�T�E���h
class Sound
{
private://�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://�T�u�N���X
	//�`�����N�w�b�_
	struct ChunkHeader
	{
		char id[4];//�`�����N����ID
		int size;//�`�����N�T�C�Y
	};

	//RIFF�w�b�_�`�����N
	struct RiffHeader
	{
		ChunkHeader	chunk;//"RIFF"
		char type[4];//"WAVE"
	};

	//FMT�`�����N
	struct FormatChunk
	{
		ChunkHeader chunk;//"fmt "
		WAVEFORMATEX fmt;//�g�`�t�H�[�}�b�g
	};

	//�����f�[�^
	struct SoundData
	{
		WAVEFORMATEX wfex;//�g�`�t�H�[�}�b�g
		BYTE* pBuffer;//�o�b�t�@�̐擪�A�h���X
		unsigned int bufferSize;//�o�b�t�@�̃T�C�Y
	};

private://�ϐ�
	ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;
	//XAudio2VoiceCallback voiceCallback;

public://�֐�
	void Initialize();//����������
	SoundData SoundLoadWave(const char* filename);//�T�E���h�̓ǂݍ���
	void SoundUnload(SoundData* soundData);
	void SoundPlayWave(const SoundData& soundData);

};