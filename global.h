#ifndef GLOBAL_H
#define GLOBAL_H

//STL

//Qt

//Project

#ifdef BUILDING_DLL
#define DLLIMPORT extern "C" __cdecl
#else
#define DLLIMPORT extern "C"
#endif

#endif // GLOBAL_H
