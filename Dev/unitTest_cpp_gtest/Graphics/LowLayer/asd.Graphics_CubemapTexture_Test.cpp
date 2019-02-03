﻿

#include "../asd.Graphics_Test_Utls.h"

static const char* dx_vs = R"(
struct VS_Input
{
	float3 Pos		: Pos0;
	float2 UV		: UV0;
};

struct VS_Output
{
	float4 Pos		: SV_POSITION;
	float2 UV		: TEXCOORD0;
};

VS_Output main( const VS_Input Input )
{
	VS_Output Output = (VS_Output)0;
	Output.Pos = float4( Input.Pos.x, Input.Pos.y, Input.Pos.z, 1.0 );
	Output.UV = Input.UV;
	return Output;
}

)";

static const char* dx_ps = R"(

TextureCube		g_texture		: register( t0 );
SamplerState	g_sampler		: register( s0 );


struct PS_Input
{
	float4 Pos		: SV_POSITION;
	float2 UV		: TEXCOORD0;
};


float4 main( const PS_Input Input ) : SV_Target
{
	float3 uv = float3(Input.UV.x, Input.UV.y, 1.0 - dot(Input.UV,Input.UV));
	uv = normalize(uv);

	float4 Output = g_texture.SampleLevel(g_sampler, uv, 0.5);
	if(Output.a == 0.0f) discard;
	return Output;
}

)";

static const char* gl_vs = R"(
//#version 150
in vec3 Pos;
in vec2 UV;

out vec4 vaTexCoord;

void main()
{
	gl_Position = vec4(Pos.x,Pos.y,Pos.z,1.0);
	vaTexCoord = vec4(UV.x,UV.y,0.0,0.0);	
}

)";

static const char* gl_ps = R"(
//#version 150
in vec4 vaTexCoord;
uniform samplerCube g_texture;
out vec4 fragColor;

void main() 
{
	vec2 uv_ = vaTexCoord.xy;
	//uv_.y = 1.0 - uv_.y;

	vec3 uv = vec3(uv_.x, -uv_.y, 1.0 - dot(uv_,uv_));
	uv = normalize(uv);

	fragColor = textureLod(g_texture, uv.xyz, 0.5);
}

)";


static const char* dx_writemip_vs = R"(
struct VS_Input
{
	float3 Pos		: Pos0;
	float2 UV		: UV0;
};

struct VS_Output
{
	float4 Pos		: SV_POSITION;
	float2 UV		: TEXCOORD0;
};

VS_Output main( const VS_Input Input )
{
	VS_Output Output = (VS_Output)0;
	Output.Pos = float4( Input.Pos.x, Input.Pos.y, Input.Pos.z, 1.0 );
	Output.UV = Input.UV;
	return Output;
}

)";

static const char* dx_writemip_ps = R"(

Texture2D		g_texture		: register( t0 );
SamplerState	g_sampler		: register( s0 );


struct PS_Input
{
	float4 Pos		: SV_POSITION;
	float2 UV		: TEXCOORD0;
};


float4 main( const PS_Input Input ) : SV_Target
{
	float2 uv = float2(Input.UV.x, Input.UV.y);
	float4 Output = g_texture.Sample(g_sampler, uv);
	if(Output.a == 0.0f) discard;
	return Output;
}

)";

static const char* gl_writemip_vs = R"(
//#version 150
in vec3 Pos;
in vec2 UV;

out vec4 vaTexCoord;

void main()
{
	gl_Position = vec4(Pos.x,Pos.y,Pos.z,1.0);
	vaTexCoord = vec4(UV.x,UV.y,0.0,0.0);	
}

)";

static const char* gl_writemip_ps = R"(
//#version 150
in vec4 vaTexCoord;
uniform sampler2D g_texture;
out vec4 fragColor;

void main() 
{
	vec2 uv = vaTexCoord.xy;
	uv.y = 1.0 - uv.y;

	fragColor = texture(g_texture, uv);
}

)";

struct Vertex
{
	asd::Vector3DF Pos;
	asd::Vector2DF UV;

	Vertex() {}
	Vertex(asd::Vector3DF pos, asd::Vector2DF uv)
	{
		Pos = pos;
		UV = uv;
	}
};

void Graphics_CubemapTexture(bool isOpenGLMode)
{
	StartGraphicsTest();
	SetGLEnable(isOpenGLMode);

	asd::Log* log = asd::Log_Imp::Create(u"graphics.html", u"描画");

	auto window = asd::Window_Imp::Create(640, 480, asd::ToAString(u"CubemapTexture").c_str(), log, false, asd::WindowPositionType::Default, isOpenGLMode ? asd::GraphicsDeviceType::OpenGL : asd::GraphicsDeviceType::DirectX11, asd::ColorSpaceType::LinearSpace, false);
	ASSERT_TRUE(window != nullptr);

	auto synchronizer = std::make_shared<asd::Synchronizer>();
	auto file = asd::File_Imp::Create(synchronizer);
	ASSERT_TRUE(file != nullptr);

	asd::GraphicsOption go;
	go.IsFullScreen = false;
	go.IsReloadingEnabled = false;
	go.ColorSpace = asd::ColorSpaceType::LinearSpace;
	go.GraphicsDevice = isOpenGLMode ? asd::GraphicsDeviceType::OpenGL : asd::GraphicsDeviceType::DirectX11;
	auto graphics = asd::Graphics_Imp::Create(window, isOpenGLMode ? asd::GraphicsDeviceType::OpenGL : asd::GraphicsDeviceType::DirectX11, log, file, go);
	ASSERT_TRUE(graphics != nullptr);

	auto cubemap = graphics->CreateCubemapTextureFrom6ImageFiles_(
		asd::ToAString("Data/Cubemap/Sky1/Front.png").c_str(),
		asd::ToAString("Data/Cubemap/Sky1/Left.png").c_str(),
		asd::ToAString("Data/Cubemap/Sky1/Back.png").c_str(),
		asd::ToAString("Data/Cubemap/Sky1/Right.png").c_str(),
		asd::ToAString("Data/Cubemap/Sky1/Top.png").c_str(),
		asd::ToAString("Data/Cubemap/Sky1/Bottom.png").c_str()
		);

	auto front = graphics->CreateTexture2D(asd::ToAString("Data/Cubemap/Sky1/Front.png").c_str());
	auto back = graphics->CreateTexture2D(asd::ToAString("Data/Cubemap/Sky1/Back.png").c_str());
	auto left = graphics->CreateTexture2D(asd::ToAString("Data/Cubemap/Sky1/Left.png").c_str());
	auto right = graphics->CreateTexture2D(asd::ToAString("Data/Cubemap/Sky1/Right.png").c_str());
	auto top = graphics->CreateTexture2D(asd::ToAString("Data/Cubemap/Sky1/Top.png").c_str());
	auto bottom = graphics->CreateTexture2D(asd::ToAString("Data/Cubemap/Sky1/Bottom.png").c_str());

	auto vertexBuffer = graphics->CreateVertexBuffer_Imp(sizeof(Vertex), 4, false);
	ASSERT_TRUE(vertexBuffer != nullptr);

	auto vertexBufferMip = graphics->CreateVertexBuffer_Imp(sizeof(Vertex), 4, false);
	ASSERT_TRUE(vertexBufferMip != nullptr);

	auto indexBuffer = graphics->CreateIndexBuffer_Imp(6, false, false);
	ASSERT_TRUE(indexBuffer != nullptr);

	std::vector<asd::VertexLayout> vl;
	vl.push_back(asd::VertexLayout("Pos", asd::VertexLayoutFormat::R32G32B32_FLOAT));
	vl.push_back(asd::VertexLayout("UV", asd::VertexLayoutFormat::R32G32_FLOAT));

	std::shared_ptr<asd::NativeShader_Imp> shader;
	std::shared_ptr<asd::NativeShader_Imp> shaderMip;

	bool const is32bit = false;

	std::vector<asd::Macro> macro;
	if (isOpenGLMode)
	{
		shader = graphics->CreateShader_Imp(
			gl_vs,
			"vs",
			gl_ps,
			"ps",
			vl,
			is32bit,
			macro);
		shaderMip = graphics->CreateShader_Imp(
			gl_writemip_vs,
			"vs",
			gl_writemip_ps,
			"ps",
			vl,
			is32bit,
			macro);
	}
	else
	{
		shader = graphics->CreateShader_Imp(
			dx_vs,
			"vs",
			dx_ps,
			"ps",
			vl,
			is32bit,
			macro);
		shaderMip = graphics->CreateShader_Imp(
			dx_writemip_vs,
			"vs",
			dx_writemip_ps,
			"ps",
			vl,
			is32bit,
			macro);
	}

	ASSERT_TRUE(shader != nullptr);
	ASSERT_TRUE(shaderMip != nullptr);

	{
		vertexBuffer->Lock();
		auto vb = vertexBuffer->GetBuffer<Vertex>(4);
		vb[0] = Vertex(asd::Vector3DF(-1.0f, 1.0f, 0.5f), asd::Vector2DF(0.0f, 0.0f));
		vb[1] = Vertex(asd::Vector3DF(0.5f, 1.0f, 0.5f), asd::Vector2DF(1.0f, 0.0f));
		vb[2] = Vertex(asd::Vector3DF(0.5f, -1.0f, 0.5f), asd::Vector2DF(1.0f, 1.0f));
		vb[3] = Vertex(asd::Vector3DF(-1.0f, -1.0f, 0.5f), asd::Vector2DF(0.0f, 1.0f));
		vertexBuffer->Unlock();
	}

	{
		vertexBufferMip->Lock();
		auto vb = vertexBufferMip->GetBuffer<Vertex>(4);
		vb[0] = Vertex(asd::Vector3DF(-1.0f, 1.0f, 0.5f), asd::Vector2DF(0.0f, 0.0f));
		vb[1] = Vertex(asd::Vector3DF(1.0f, 1.0f, 0.5f), asd::Vector2DF(1.0f, 0.0f));
		vb[2] = Vertex(asd::Vector3DF(1.0f, -1.0f, 0.5f), asd::Vector2DF(1.0f, 1.0f));
		vb[3] = Vertex(asd::Vector3DF(-1.0f, -1.0f, 0.5f), asd::Vector2DF(0.0f, 1.0f));
		vertexBufferMip->Unlock();
	}

	{
		indexBuffer->Lock();
		auto ib = indexBuffer->GetBuffer<uint16_t>(6);
		ib[0] = 0;
		ib[1] = 1;
		ib[2] = 2;
		ib[3] = 0;
		ib[4] = 2;
		ib[5] = 3;
		indexBuffer->Unlock();
	}

	shader->SetTexture("g_texture", cubemap, asd::TextureFilterType::Linear, asd::TextureWrapType::Clamp, 0);
	
	int32_t time = 0;
	while (window->DoEvent())
	{
		graphics->Begin();

		for (int i = 0; i < 6; i++)
		{
			if (i == 0) shaderMip->SetTexture("g_texture", right.get(), asd::TextureFilterType::Linear, asd::TextureWrapType::Clamp, 0);
			if (i == 1) shaderMip->SetTexture("g_texture", left.get(), asd::TextureFilterType::Linear, asd::TextureWrapType::Clamp, 0);
			if (i == 2) shaderMip->SetTexture("g_texture", top.get(), asd::TextureFilterType::Linear, asd::TextureWrapType::Clamp, 0);
			if (i == 3) shaderMip->SetTexture("g_texture", bottom.get(), asd::TextureFilterType::Linear, asd::TextureWrapType::Clamp, 0);
			if (i == 4) shaderMip->SetTexture("g_texture", front.get(), asd::TextureFilterType::Linear, asd::TextureWrapType::Clamp, 0);
			if (i == 5) shaderMip->SetTexture("g_texture", back.get(), asd::TextureFilterType::Linear, asd::TextureWrapType::Clamp, 0);

			graphics->SetRenderTarget((asd::CubemapTexture_Imp*)cubemap, i, 1, nullptr);
			graphics->SetVertexBuffer(vertexBufferMip.get());
			graphics->SetIndexBuffer(indexBuffer.get());
			graphics->SetShader(shaderMip.get());

			asd::RenderState state;
			state.DepthTest = false;
			state.DepthWrite = false;
			graphics->SetRenderState(state);

			graphics->DrawPolygon(2);
		}
		

		graphics->SetRenderTarget(nullptr, nullptr);
		graphics->Clear(true, false, asd::Color(64, 32, 16, 255));

		graphics->SetVertexBuffer(vertexBuffer.get());
		graphics->SetIndexBuffer(indexBuffer.get());
		graphics->SetShader(shader.get());

		asd::RenderState state;
		state.DepthTest = false;
		state.DepthWrite = false;
		graphics->SetRenderState(state);

		graphics->DrawPolygon(2);

		graphics->Present();

		graphics->End();

		if (time == 10)
		{
			SAVE_SCREEN_SHOT(graphics, 0);
		}

		if (time == 11)
		{
			window->Close();
		}
		time++;
	}

	front.reset();
	cubemap->Release();
	graphics->Release();
	file->Release();

	vertexBuffer.reset();
	indexBuffer.reset();
	shader.reset();

	window->Release();
	delete log;
}

#ifdef _WIN32
TEST(Graphics, CubemapTexture_DX)
{
	Graphics_CubemapTexture(false);
}
#endif

TEST(Graphics, CubemapTexture_GL)
{
	Graphics_CubemapTexture(true);
}

