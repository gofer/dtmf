#ifndef __DTMF_H__
#define __DTMF_H__ 

#include <windows.h>

#ifndef M_PI
const double M_PI = 3.14159265358979323846;
#endif

const double FH[] = {1209.0, 1336.0, 1477.0, 1633.0};
const double FL[] = { 697.0,  770.0,  853.0,  941.0};

DWORD buildDTMFBuffer(char, BYTE*, UINT, DWORD);

#endif
