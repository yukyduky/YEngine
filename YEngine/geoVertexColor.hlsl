#pragma once
struct VS_IN {
	float3 pos_M		: POSITION;
	float3 normal		: NORMAL;
	float3 color		: COLOR;
};

struct VS_OUT {
	float4 pos_S		: SV_POSITION;
	float3 pos_W		: POSITION;
	float3 normal		: NORMAL;
	float3 color		: COLOR;
};

cbuffer cbGeoMatrices : register(b0) {
	float4x4 world;
	float4x4 mvp;
};

VS_OUT VS(VS_IN input) {
	VS_OUT output;

	// Convert the vertices pos from Model space to World space
	// Uncomment once the constant buffers work
	//output.pos_S = mul(float4(input.pos_M, 1.0f), wvp);
	//output.pos_W = mul(float4(input.pos_M, 1.0f), world);
	output.pos_S = float4(input.pos_M, 1.0f);
	output.pos_W = float4(input.pos_M, 1.0f);
	output.normal = input.normal;
	output.color = input.color;

	return output;
}