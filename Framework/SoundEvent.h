#pragma once
#include "stdafx.h"
#include "Audio.h"
class SoundEvent
{
private:
	IXAudio2SourceVoice* sourceVoice;	// the XAudio2 source voice
	WAVEFORMATEX *waveFormat;			// the format of the audio file
	unsigned int waveLength;			// the length of the wave
	std::vector<BYTE> audioData;		// the audio data
	XAUDIO2_BUFFER audioBuffer;			// the actual buffer with the audio data

	float fallof;						// falloff distance
	unsigned int priority;				// music priority

	unsigned int index;					// the index of the actual sound to play

	Audio* engine;
public:
	const wchar_t* audioPath;			//�ε��� ���������� ��� ���ڿ��� �����մϴ�.
public:
	SoundEvent();						//SoundEvent��ü ����
	SoundEvent(const wchar_t* path);	//��ü ������ ���ÿ� ���带 �ε��մϴ�.
	~SoundEvent();

public:
	//���������� �ε��մϴ�. ���� ���� �ؼ��� �ö���� ������ Debug ���¿����� �ε� �ӵ��� �ſ� ���� �� �ֽ��ϴ�.
	//Release�� ������ ��� �ӵ��� �����˴ϴ�.
	void LoadFile(const wchar_t* path);	
	
	//���� ���, ����, �Ͻ�����
	void Play();
	void Stop();
	void Pause();
};

