// Copyright (C) 2003 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef GCOGL_VERTEXSHADER_H
#define GCOGL_VERTEXSHADER_H

#include <stdarg.h>
#include "XFMemory.h"
#include "VideoCommon.h"
#include "ShaderGenCommon.h"

// TODO should be reordered
#define SHADER_POSITION_ATTRIB  0
#define SHADER_POSMTX_ATTRIB    1
#define SHADER_NORM0_ATTRIB     2
#define SHADER_NORM1_ATTRIB     3
#define SHADER_NORM2_ATTRIB     4
#define SHADER_COLOR0_ATTRIB    5
#define SHADER_COLOR1_ATTRIB    6

#define SHADER_TEXTURE0_ATTRIB  8
#define SHADER_TEXTURE1_ATTRIB  9
#define SHADER_TEXTURE2_ATTRIB  10
#define SHADER_TEXTURE3_ATTRIB  11
#define SHADER_TEXTURE4_ATTRIB  12
#define SHADER_TEXTURE5_ATTRIB  13
#define SHADER_TEXTURE6_ATTRIB  14
#define SHADER_TEXTURE7_ATTRIB  15



// shader variables
#define I_POSNORMALMATRIX       "cpnmtx"
#define I_PROJECTION            "cproj"
#define I_MATERIALS             "cmtrl"
#define I_LIGHTS                "clights"
#define I_TEXMATRICES           "ctexmtx"
#define I_TRANSFORMMATRICES     "ctrmtx"
#define I_NORMALMATRICES        "cnmtx"
#define I_POSTTRANSFORMMATRICES "cpostmtx"
#define I_DEPTHPARAMS           "cDepth" // farZ, zRange, scaled viewport width, scaled viewport height

#define C_POSNORMALMATRIX        0
#define C_PROJECTION            (C_POSNORMALMATRIX + 6)
#define C_MATERIALS             (C_PROJECTION + 4)
#define C_LIGHTS                (C_MATERIALS + 4)
#define C_TEXMATRICES           (C_LIGHTS + 40)
#define C_TRANSFORMMATRICES     (C_TEXMATRICES + 24)
#define C_NORMALMATRICES        (C_TRANSFORMMATRICES + 64)
#define C_POSTTRANSFORMMATRICES (C_NORMALMATRICES + 32)
#define C_DEPTHPARAMS           (C_POSTTRANSFORMMATRICES + 64)
#define C_VENVCONST_END			(C_DEPTHPARAMS + 1)

const s_svar VSVar_Loc[] = {  {I_POSNORMALMATRIX, C_POSNORMALMATRIX, 6 },
						{I_PROJECTION , C_PROJECTION, 4  },
						{I_MATERIALS, C_MATERIALS, 4 },
						{I_LIGHTS, C_LIGHTS, 40 },
						{I_TEXMATRICES, C_TEXMATRICES, 24 },
						{I_TRANSFORMMATRICES , C_TRANSFORMMATRICES, 64  },
						{I_NORMALMATRICES , C_NORMALMATRICES, 32  },
						{I_POSTTRANSFORMMATRICES, C_POSTTRANSFORMMATRICES, 64 },
						{I_DEPTHPARAMS, C_DEPTHPARAMS, 1 },
						};                                            

// TODO: Need packing?
struct vertex_shader_uid_data

{
	u32 components;
	u32 numColorChans : 2;
	u32 numTexGens : 4;

	struct {
		u32 projection : 1; // XF_TEXPROJ_X
		u32 inputform : 2; // XF_TEXINPUT_X
		u32 texgentype : 3; // XF_TEXGEN_X
		u32 sourcerow : 5; // XF_SRCGEOM_X
		u32 embosssourceshift : 3; // what generated texcoord to use
		u32 embosslightshift : 3; // light index that is used
	} texMtxInfo[8];
	struct {
		u32 index : 6; // base row of dual transform matrix
		u32 normalize : 1; // normalize before send operation
	} postMtxInfo[8];
	struct {
		u32 enabled : 1;
	} dualTexTrans;
	struct {
		u32 matsource : 1;
		u32 enablelighting : 1;
		u32 ambsource : 1;
        u32 diffusefunc : 2;
        u32 attnfunc : 2;
		u32 light_mask : 8;
	} lit_chans[4];
};

typedef ShaderUid<vertex_shader_uid_data> VertexShaderUid;
typedef ShaderCode<vertex_shader_uid_data> VertexShaderCode;

void GetVertexShaderUid(VertexShaderUid& object, u32 components, API_TYPE api_type);
void GenerateVertexShaderCode(VertexShaderCode& object, u32 components, API_TYPE api_type);
void GenerateVSOutputStructForGS(ShaderCode<u32>& object, u32 components, API_TYPE api_type);

#endif // GCOGL_VERTEXSHADER_H
