#ifndef __SOUND_H__ 
#define __SOUND_H__

#include <windows.h>

DWORD soundInit(HWAVEOUT*, WAVEFORMATEX*);
DWORD soundDestroy(HWAVEOUT*);
DWORD soundOutBegin(HWAVEOUT*, WAVEHDR*);
DWORD soundOutEnd(HWAVEOUT*, WAVEHDR*);

#endif
