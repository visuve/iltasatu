/*
	Iltasatu C-API
*/

#include "stddef.h"

#ifdef _WIN32
#define ILTASATU_EXPORT extern "C" __declspec(dllexport)
#define ILTASATU_CC __cdecl
#else
#define ILTASATU_EXPORT extern "C" __attribute__((visibility("default")))
#define ILTASATU_CC
#endif

struct IltasatuHandle
{
	size_t Unused;
};

ILTASATU_EXPORT IltasatuHandle* ILTASATU_CC IltasatuInitialize(size_t);
ILTASATU_EXPORT char* ILTASATU_CC IltasatuGenerate(IltasatuHandle*);
ILTASATU_EXPORT void ILTASATU_CC IltasatuDelete(IltasatuHandle*);