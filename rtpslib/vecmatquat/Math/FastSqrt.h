/****************************************************************************************
* Real-Time Particle System - An OpenCL based Particle system developed to run on modern GPUs. Includes SPH fluid simulations.
* version 1.0, September 14th 2011
* 
* Copyright (C) 2011 Ian Johnson, Andrew Young, Gordon Erlebacher, Myrna Merced, Evan Bollig
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
****************************************************************************************/


// FastSqrt.h
//


#ifndef _3D_FASTSQRT_H
#define _3D_FASTSQRT_H


#include "Types.h"


#define FSqrt(x, squareroot)  { extern UInt32 FastSqrtTable[0x10000]; *((UInt *) &(squareroot)) = (FastSqrtTable[(*(Int *) &((Float) x) >> 8) & 0xFFFF] ^ ((((*(Int *) &((Float) x) - 0x3F800000) >> 1) + 0x3F800000) & 0x7F800000)); }

ForceInline Float FastSqrt(Float x)
{
	FSqrt(x, x);
	return x;
}


Void BuildSqrtTable();


#endif