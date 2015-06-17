#include <sound.h>
#include <stdio.h>
#include <mmsystem.h>

void soundError(MMRESULT mmRet)
{
	LPSTR pszText = new char[MAXERRORLENGTH];
	waveOutGetErrorText(mmRet, pszText, MAXERRORLENGTH);
	fprintf(stderr, "\t%s\n", pszText);
	delete pszText;
}

DWORD soundInit(HWAVEOUT *hwo, WAVEFORMATEX *wfx)
{
	MMRESULT mmRet = waveOutOpen(
		hwo, WAVE_MAPPER, wfx, 
		0, 0, CALLBACK_NULL
	);
	
	if(mmRet != MMSYSERR_NOERROR)
	{
		fprintf(stderr, "waveOutOpen() error.(0x%08X)\n", mmRet);
		soundError(mmRet);
		return mmRet;
	}
	
	return 0;
}

DWORD soundDestroy(HWAVEOUT *hwo)
{
	MMRESULT mmRet = waveOutClose(*hwo);
	
	if(mmRet != MMSYSERR_NOERROR)
	{
		fprintf(stderr, "waveOutOpen() error.(0x%08X)\n", mmRet);
		soundError(mmRet);
		return 1;
	}
	
	return 0;
}

DWORD soundOutBegin(HWAVEOUT *hwo, WAVEHDR *wh)
{
	MMRESULT mmRet = waveOutPrepareHeader(*hwo, wh, sizeof(WAVEHDR));
	if(mmRet != MMSYSERR_NOERROR)
	{
		fprintf(stderr, "waveOutPrepareHeader() error.(0x%08X)\n", mmRet);
		soundError(mmRet);
		return 1;
	}
	
	mmRet = waveOutWrite(*hwo, wh, sizeof(WAVEHDR));
	if(mmRet != MMSYSERR_NOERROR)
	{
		fprintf(stderr, "waveOutWrite() error.(0x%08X)\n", mmRet);
		soundError(mmRet);
		return 1;
	}
	
	return 0;
}

DWORD soundOutEnd(HWAVEOUT *hwo, WAVEHDR *wh)
{
	MMRESULT mmRet = waveOutReset(*hwo);
	if(mmRet != MMSYSERR_NOERROR)
	{
		fprintf(stderr, "waveOutReset() error.(0x%08X)\n", mmRet);
		soundError(mmRet);
		return 1;
	}
	
	mmRet = waveOutUnprepareHeader(*hwo, wh, sizeof(WAVEHDR));
	if(mmRet != MMSYSERR_NOERROR)
	{
		fprintf(stderr, "waveOutUnprepareHeader() error.(0x%08X)\n", mmRet);
		soundError(mmRet);
		return 1;
	}
	
	return 0;
}
