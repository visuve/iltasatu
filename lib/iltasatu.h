/*
	Iltasatu C-API
*/

#pragma once
#include <stddef.h>

#ifdef __cplusplus
#define ILTASATU_EXTERN extern "C"
#else
#define ILTASATU_EXTERN
#endif

#ifdef _WIN32
#define ILTASATU_EXPORT ILTASATU_EXTERN __declspec(dllexport)
#define ILTASATU_CC __cdecl
#else
#define ILTASATU_EXPORT ILTASATU_EXTERN __attribute__((visibility("default")))
#define ILTASATU_CC
#endif

typedef struct _IltasatuHandle
{
	size_t Unused;
} *IltasatuHandle;

ILTASATU_EXPORT IltasatuHandle ILTASATU_CC IltasatuInitialize(size_t);
ILTASATU_EXPORT char* ILTASATU_CC IltasatuGenerate(IltasatuHandle);
ILTASATU_EXPORT void ILTASATU_CC IltasatuDelete(IltasatuHandle);
