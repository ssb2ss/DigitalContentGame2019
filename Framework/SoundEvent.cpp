#include "stdafx.h"
#include "SoundEvent.h"


SoundEvent::SoundEvent() :sourceVoice(nullptr)
{
	engine = Audio::GetInstance();
}

SoundEvent::SoundEvent(const wchar_t* path)
{
	SoundEvent();
	LoadFile(path);
}


SoundEvent::~SoundEvent()
{
}

void SoundEvent::LoadFile(const wchar_t* path)
{
	HRESULT hr = S_OK;

	// load file into wave
	WAVEFORMATEX* waveFormatEx;
	engine->LoadFile(path, audioData, &waveFormatEx, waveLength);

	waveFormat = waveFormatEx;

	// create source voice
	//hr = engine->xaudio2->CreateSourceVoice(&soundEvent->sourceVoice, &soundEvent->waveFormat);
	if (FAILED(hr = engine->xaudio2->CreateSourceVoice(&sourceVoice, waveFormatEx)))
	{
		wprintf(L"Error %#X creating source voice\n", hr);
		return;
	}

	ZeroMemory(&audioBuffer, sizeof(XAUDIO2_BUFFER));
	audioBuffer.AudioBytes = (UINT32)audioData.size();
	audioBuffer.pAudioData = (BYTE * const)&audioData[0];
	audioBuffer.pContext = nullptr;

	audioPath = path;
}

void SoundEvent::Play()
{
	if (!sourceVoice)
	{
		printf("����� ������ �ε���� �ʾҽ��ϴ�.\n");
		return;
	}
	// handle errors
	HRESULT hr = S_OK;

	// submit the audio buffer to the source voice
	hr = sourceVoice->SubmitSourceBuffer(&audioBuffer);
	if (FAILED(hr))
		puts("�ҽ� ���ۿ� ������ �Ұ����մϴ�.");

	// start the source voice
	sourceVoice->Start();
}

void SoundEvent::Stop()
{
	if (!sourceVoice)
	{
		printf("����� ������ �ε���� �ʾҽ��ϴ�.\n");
		return;
	}
	sourceVoice->Stop();
	sourceVoice->FlushSourceBuffers();
}

void SoundEvent::Pause()
{
	if (!sourceVoice)
	{
		printf("����� ������ �ε���� �ʾҽ��ϴ�.\n");
		return;
	}
	sourceVoice->Stop();
}
