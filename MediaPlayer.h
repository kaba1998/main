#pragma once
#include <dshow.h>
#include <string>
using namespace std;

enum PlaybackState
{
	STATE_UNINITIALIZED,
	STATE_NO_GRAPH,
	STATE_RUNNING,
	STATE_PAUSED,
	STATE_STOPPED,
};

class MediaPlayer 
{
private:
	IGraphBuilder* pGraph;
	IMediaControl* pControl;
	IMediaEvent* pEvent;
	IMediaSeeking* pSeeking;
	HRESULT hr;

	PlaybackState state;

	LONGLONG startPos, stopPos;

	MediaPlayer();
	static MediaPlayer* instance;

public:
	static MediaPlayer* GetInstance();
	static void DeleteInstance();
	~MediaPlayer();

	void Play_Pause_video();
	void Repeat();
	void Accelerate();
	void Quitter();
	void Start(LPCWSTR fileIn);
};