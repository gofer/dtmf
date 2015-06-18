#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>

#include <device.h>
#include <sound.h>
#include <dtmf.h>

DWORD wait(double);

/* unit of T is sec; for millisec. */
DWORD wait(double T)
{
	DWORD S = (DWORD)floor(T * 1000);
	
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);
	DWORD P = (tv1.tv_sec * 1000) + (tv1.tv_usec / 1000);
	
	while(true)
	{
		gettimeofday(&tv2, NULL);
		DWORD Q = (tv2.tv_sec * 1000) + (tv2.tv_usec / 1000);
		if(Q - P >= S) break;
		
		// ToDo: polling, もっと良い処理がある
		for(UINT i=0; i<0xFFFF; ++i)
		{
			__asm volatile ("nop");
		}
	}
	
	return 0;
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, 
    int nCmdShow
)
{
    UINT woDeviceNum = waveOutGetNumDevs();
#ifdef __DEBUG__
    printf("woDeviceNum = %u\n", woDeviceNum);
#endif
   
	/* device not found */
	if(woDeviceNum == 0)
	{
		fputs("No wave output device found.", stderr);
		return 1;
	}
	
#ifdef __DEBUG__
	waveOutGetDeviceInfo(woDeviceNum);
#endif
	
	WAVEFORMATEX wfx;
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 2;
	wfx.nSamplesPerSec = 48000; //44100;
	wfx.wBitsPerSample = 8;
	wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) >> 3; /* / 8 */
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	wfx.cbSize = 0;
	
	/* 1 sec. data */
	double beepTime = 0.5, waitTime = 0.2;
	DWORD bufSize = (DWORD)floor(wfx.nAvgBytesPerSec * beepTime);
	
    printf("Input [0-9A-D#\\*]+ > ");
	while(true)
	{
		HWAVEOUT hwo = NULL;
		LPBYTE lpWave = new BYTE[bufSize];
		
		WAVEHDR wh;
		wh.lpData = (LPSTR)lpWave;
		wh.dwBufferLength = bufSize;
		wh.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
		wh.dwLoops = 1;
		
		soundInit(&hwo, &wfx);
		
REINPUT:
		char c;
		scanf("%c", &c);
		if(c == 'x' || c == '\n') 
		{
			soundDestroy(&hwo);
			break;
		}
		
		if(
			buildDTMFBuffer(c, lpWave, wh.dwBufferLength, wfx.nSamplesPerSec)
			!= 0
		) goto REINPUT;
		
		soundOutBegin(&hwo, &wh);
		
		wait(beepTime);
		
		soundOutEnd(&hwo, &wh);
		
		delete lpWave;
		
		soundDestroy(&hwo);
		
		wait(waitTime);
	}
	
    return 0;
}

