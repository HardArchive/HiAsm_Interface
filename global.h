#pragma once

//Project

//STL

//Qt

#ifdef BUILDING_DLL
#define DLLEXPORT extern "C" __cdecl
#else
#define DLLEXPORT extern "C"
#endif
