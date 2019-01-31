struct VS_INPUT
{
	float4 mPosition	: POSITION;
	float2 mUv			: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 mPosition	: POSITION;
	float2 mUv			: TEXCOORD0;
};

float4x4 gWorldMatrix;
float4x4 gViewMatrix;
float4x4 gProjMatrix;

float gWaterWave;
float gWaveSpeed = 0.01;

VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.mPosition = mul(Input.mPosition, gWorldMatrix);
	Output.mPosition = mul(Output.mPosition, gViewMatrix);
	Output.mPosition = mul(Output.mPosition, gProjMatrix);
	Output.mUv = Input.mUv;

	return Output;
}

struct PS_INPUT
{
	float2 mUv			: TEXCOORD0;
};

texture gMap;
sampler gMapSampler = sampler_state
{
	Texture = (gMap);
};

texture gBumpMap;
sampler gBumpMapSampler = sampler_state
{
	Texture = (gBumpMap);
};


float4 ps_main(PS_INPUT Input) : COLOR
{
   float2 xy = float2(Input.mUv.x + gWaterWave * gWaveSpeed, Input.mUv.y);

   float4 noize = tex2D(gBumpMapSampler, xy);

   float2 uv = Input.mUv.xy + noize.xy * 0.01;

   return tex2D(gMapSampler, uv);
}

technique Color
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
}
