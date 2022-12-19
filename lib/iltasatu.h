/*
	Iltasatu C-API
*/

#pragma once

#include <stddef.h>
#include <stdint.h>

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

typedef enum _IltasatuMask
{
	None = 0x00,
	Punctuation = (1u << 0),
	Number = (1u << 1),
	Uppercase = (1u << 2),
	Lowercase = (1u << 3)
} IltasatuMask;

typedef struct _IltasatuOptions
{
	size_t Size;
	uint32_t Mask;
} IltasatuOptions;

ILTASATU_EXPORT IltasatuHandle ILTASATU_CC IltasatuInitialize(IltasatuOptions);
ILTASATU_EXPORT char* ILTASATU_CC IltasatuGenerate(IltasatuHandle);
ILTASATU_EXPORT void ILTASATU_CC IltasatuDelete(IltasatuHandle);
