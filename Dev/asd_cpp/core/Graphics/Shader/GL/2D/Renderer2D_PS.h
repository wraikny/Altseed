﻿static const char* renderer2d_ps_gl = R"(

in vec4 vaTexCoord;
in vec4 vaTexCoordSubA;
in vec4 vaColor;

out vec4 outColor;

uniform sampler2D g_texture;

void main() 
{
#ifdef HAS_TEXTURE
	// varying(in) は変更不可(Radeon)

	// gl only
	vec4 vaTexCoord_ = vaTexCoord;
	vaTexCoord_.y = 1.0 - vaTexCoord_.y;

	outColor = texture(g_texture, vaTexCoord_.xy) * vaColor;
#else
	outColor = vaColor;
#endif
}

)";