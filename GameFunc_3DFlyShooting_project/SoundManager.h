#pragma once
#include "singleton.h"

#include <mmsystem.h>
#include <mmreg.h>
#include <DSound.h>


#pragma comment (lib , "winmm.lib")
#pragma comment (lib , "dsound.lib")
#pragma comment (lib , "dxguid.lib")


class SoundManager :
	public singleton<SoundManager>
{
private:

	HWND									m_hWnd;						// �ڵ�
	LPDIRECTSOUND							m_lpDirectSound;			// �������
	std::map<std::string, LPDIRECTSOUNDBUFFER>	m_mapSoundBuffers;			// ������۹迭

public:
	SoundManager();
	virtual ~SoundManager();

	// ���� ����� ������ ������ ��ȯ.
	int                 GetBufferSize() { return m_mapSoundBuffers.size(); }

	// ����� �ʿ��� ���۸� ã�� ���.
	void                Play(const std::string& key, BOOL Loop = FALSE);

	// ����� �ʿ��� ���۸� ã�� �� ���� �޸� ������ �����ϴ� �� ���۸� ����� ���.
	// �� ������� �������� ����Ǵ� �Ҹ� (�ѼҸ� ��) �� ���Ӿ��� ����� �� �ִ�.
	void				DuplicatePlay(const std::string& key);
	// �̰� ī�޶���� x ���� ����ؼ� ������, ������ �����ؼ� ���.
	void				DuplicateDistancePlay(const std::string& key, Vector3 position);
	// ���۸� ã�� ����.
	void                Stop(const std::string& key);
	// ��� ���۸� ã�� ����.
	void                AllStop();

	// �� ���� ( -10000 ~ 10000 ) ���� ���ϼ��� ���ʿ� ��� ��� ���� �����ʿ� �Ҹ��� ���.
	void                SetPan(const std::string& key, long pan);
	// �� ������ ����.
	void                SetVol(const std::string& key, int volPercent); // 0 ~ 100 % ����.
	// ������ ����.
	int 				GetVol(const std::string& key);
	// ������ ����.
	void				AddVol(const std::string& key, int volPercent);

	// ���� �� ������ ����ǰ� �ִ����� ��ȯ.
	BOOL                IsPlaying(const std::string& key);


	// ���� �߰�.
	void				AddSound(const std::string& key, const std::string& wavPath, int flag = 0);
	// ���� ����.
	void                DeleteSound(const std::string& key);

private:

	// �� �ȿ� ������ ����Ǿ��ִ����� �˾ƿ�
	BOOL                IsBufIndex(const std::string& key);

	// �ʱ�ȭ.
	void                DirectSoundInit();
	// ����.
	void				DirectSoundDestroy();

	// WAV ������ �ε� DirectSound�� mp3�� �������� ����.
	LPDIRECTSOUNDBUFFER LoadWav(const std::string& path, int Flag = 0);
	// �� ���۸� �ʿ� �߰���.
	BOOL                AddSoundBuffer(const std::string& key, LPDIRECTSOUNDBUFFER buffer);
};

#define SOUND SoundManager::GetInst()