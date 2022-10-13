//#pragma comment(lib, "Strmiids.lib")
#include "MediaPlayer.h"
#include <conio.h>
#include <iostream>

MediaPlayer* MediaPlayer::instance = NULL;

MediaPlayer::MediaPlayer()
{
    pGraph = NULL;
    pControl = NULL;
    pEvent = NULL;
    pSeeking = NULL;

    state = STATE_UNINITIALIZED;
    startPos = NULL;
    stopPos = NULL;


    // Initialize the COM library.
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return;
    }

    // Create the filter graph manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&pGraph);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");
        return;
    }

    hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create pControl.");
        return;
    }

    hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create pEvent.");
        return;
    }

    hr = pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeeking);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create pSeeking.");
        return;
    }
}

MediaPlayer* MediaPlayer::GetInstance()
{
    if (!instance)
        instance = new MediaPlayer();
    return instance;
}

void MediaPlayer::DeleteInstance()
{
    if (instance)
        delete instance;
    instance = NULL;
}

void MediaPlayer::Start(LPCWSTR fileIn)
{
    hr = pGraph->RenderFile(fileIn, NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not render file.");
        return;
    }

    hr = pSeeking->GetCurrentPosition(&startPos);
    if (SUCCEEDED(hr))
    {
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            state = STATE_RUNNING;
        }
    }

}

void MediaPlayer::Play_Pause_video()
{
    if (state == STATE_RUNNING)
    {
        pControl->Pause();
        state = STATE_STOPPED;
    }
    else if (state == STATE_STOPPED)
    {
        pControl->Run();
        state = STATE_RUNNING;
    }
}

void MediaPlayer::Accelerate()
{
    double rate;
    hr = pSeeking->GetRate(&rate);

    if (rate > 1.5)
        hr = pSeeking->SetRate(1.0);
    else
        hr = pSeeking->SetRate(2.0);
}

void MediaPlayer::Repeat()
{
    if (state == STATE_RUNNING)
    {
        pControl->Pause();
        state = STATE_STOPPED;
    }

    pSeeking->SetPositions(&startPos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
    pControl->Run();
    state = STATE_RUNNING;
}
void MediaPlayer::Quitter()
{
    cout << "Quitter la video..." << endl;

    pControl->Release();
    pEvent->Release();
    pGraph->Release();
    pSeeking->Release();
    CoUninitialize();

    state = STATE_NO_GRAPH;
}

MediaPlayer::~MediaPlayer()
{
    if (state != STATE_NO_GRAPH)
        Quitter();
    
    printf("Appel du destructeur \n");
}

