#include <device.h>
#include <stdio.h>
#include <mmsystem.h>

static const DWORD WaveFormats[] = {
	WAVE_FORMAT_1M08,
	WAVE_FORMAT_1M16,
	WAVE_FORMAT_1S08,
	WAVE_FORMAT_1S16,
	WAVE_FORMAT_2M08,
	WAVE_FORMAT_2M16,
	WAVE_FORMAT_2S08,
	WAVE_FORMAT_2S16,
	WAVE_FORMAT_4M08,
	WAVE_FORMAT_4M16,
	WAVE_FORMAT_4S08,
	WAVE_FORMAT_4S16,
	WAVE_FORMAT_48M08,
	WAVE_FORMAT_48S08,
	WAVE_FORMAT_48M16,
	WAVE_FORMAT_48S16,
	WAVE_FORMAT_96M08,
	WAVE_FORMAT_96S08,
	WAVE_FORMAT_96M16,
	WAVE_FORMAT_96S16,
};

static LPCSTR WaveFormatsString[] =
{
	"11.025 kHz, Mono, 8-bit",
	"11.025 kHz, Mono, 16-bit",
	"11.025 kHz, Stereo, 8-bit",
	"11.025 kHz, Stereo, 16-bit",
	"22.05 kHz, Mono, 8-bit",
	"22.05 kHz, Mono, 16-bit",
	"22.05 kHz, Stereo, 8-bit",
	"22.05 kHz, Stereo, 16-bit",
	"44.1 kHz, Mono, 8-bit",
	"44.1 kHz, Mono, 16-bit",
	"44.1 kHz, Stereo, 8-bit",
	"44.1 kHz, Stereo, 16-bit",
	"48 kHz, Mono, 8-bit",
	"48 kHz, Stereo, 8-bit",
	"48 kHz, Mono, 16-bit",
	"48 kHz, Stereo, 16-bit",
	"96 kHz, Mono, 8-bit",
	"96 kHz, Stereo, 8-bit",
	"96 kHz, Mono, 16-bit",
	"96 kHz, Stereo, 16-bit",
};

static const DWORD SupportFunctions[] = {
	WAVECAPS_LRVOLUME,
	WAVECAPS_PITCH,
	WAVECAPS_PLAYBACKRATE,
	WAVECAPS_VOLUME,
	WAVECAPS_SAMPLEACCURATE,
};

static LPCSTR SupportFunctionsString[] = {
	"Supports separate left and right volume control.",
	"Supports pitch control.",
	"Supports playback rate control.",
	"Supports volume control.",
	"Returns sample-accurate position information.",
};

DWORD waveOutGetDeviceInfo(DWORD woDeviceNum)
{
    for(UINT uDeviceID=0; uDeviceID<woDeviceNum; ++uDeviceID)
    {
        LPWAVEOUTCAPS pwoc = new WAVEOUTCAPS();
        
        MMRESULT mmResult = waveOutGetDevCaps(uDeviceID, pwoc, sizeof(WAVEOUTCAPS));
        if(mmResult != MMSYSERR_NOERROR)
        {
            fprintf(stderr, "Cannot load device info. (id=%u, errno=%u)\n", uDeviceID, mmResult);
            continue;
        }
        
        printf("Device name: %s\n", pwoc->szPname);
		printf("Manufacturer identifier: 0x%08X\n", pwoc->wMid);
		printf("Product identifier: 0x%08X\n", pwoc->wPid);
        printf("Channels: %s\n", ((pwoc->wChannels == 1) ? "Mono(1)" : "Streo(2)"));
		
		printf("Support formats: 0x%08X\n", pwoc->dwFormats);
		for(UINT i=0; i<20; ++i)
		{
			if(pwoc->dwFormats & WaveFormats[i])
			{
				printf("\t%s\n", WaveFormatsString[i]);
			}
		}
		
		printf("Support functions: 0x%08X\n", pwoc->dwSupport);
		for(UINT i=0; i<5; ++i)
		{
			if(pwoc->dwSupport & SupportFunctions[i])
			{
				printf("\t%s\n", SupportFunctionsString[i]);
			}
		}
		
        delete pwoc;
    }
	
	return 0;
}
