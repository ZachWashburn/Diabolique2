#ifndef _H_PREPROCESSOR
#define _H_PREPROCESSOR

#ifdef _MSC_VER
#pragma once
#endif



#ifdef _MSC_VER

// creds to valve software for the idea
#define NOVTABLE __declspec(novtable)
#define ABSTRACT_CLASS class NOVTABLE
#define FORCEINLINE __forceinline
#define NAKED __declspec(naked)

#else 

#define NOVTABLE 
#define ABSTRACT_CLASS 
#define FORCEINLINE 
#define NAKED __attribute__ ((naked))

#endif








#endif
