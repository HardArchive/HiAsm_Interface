#ifndef GLOBAL_H
#define GLOBAL_H

//STL

//Qt

//Project

#ifdef BUILDING_DLL
#define DLLEXPORT extern "C" __cdecl
#else
#define DLLEXPORT extern "C"
#endif

#endif // GLOBAL_H
