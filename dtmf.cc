#include <dtmf.h>
#include <math.h>

DWORD buildDTMFBuffer(char c, BYTE* lpWave, UINT uBufSize, DWORD dwSampleRate)
{
	double fh = FH[0], fl = FL[0];
	switch(c)
	{
	case '1':	fh = FH[0]; fl = FL[0]; break;
	case '2':	fh = FH[1]; fl = FL[0]; break;
	case '3':	fh = FH[2]; fl = FL[0]; break;
	case 'A':	fh = FH[3]; fl = FL[0]; break;
	case '4':	fh = FH[0]; fl = FL[1]; break;
	case '5':	fh = FH[1]; fl = FL[1]; break;
	case '6':	fh = FH[2]; fl = FL[1]; break;
	case 'B':	fh = FH[3]; fl = FL[1]; break;
	case '7':	fh = FH[0]; fl = FL[2]; break;
	case '8':	fh = FH[1]; fl = FL[2]; break;
	case '9':	fh = FH[2]; fl = FL[2]; break;
	case 'C':	fh = FH[3]; fl = FL[2]; break;
	case '*':	fh = FH[0]; fl = FL[3]; break;
	case '0':	fh = FH[1]; fl = FL[3]; break;
	case '#':	fh = FH[2]; fl = FL[3]; break;
	case 'D':	fh = FH[3]; fl = FL[3]; break;
	default:	return 1;
	}
	
	for(UINT i=0; i<uBufSize; i += 2)
	{
		double t = ((double)(i/2)) / dwSampleRate;
		double x = 0.8 * sin(2 * M_PI * t * fh) + 0.65 * sin(2 * M_PI * t * fl);
		lpWave[i+0] = (BYTE)floor(32.0 * x + 128.0);
		lpWave[i+1] = (BYTE)floor(32.0 * x + 128.0);
	}
	
	return 0;
}
