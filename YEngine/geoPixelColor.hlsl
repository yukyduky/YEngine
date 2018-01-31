#pragma once
struct PS_IN {
	float4 pos_S		: SV_POSITION;
	float3 pos_W		: POSITION;
	float3 normal		: NORMAL;
	float3 color		: COLOR;
};

struct PS_OUT {
	float4 pos_W			: SV_TARGET0;
	float4 normal			: SV_TARGET1;
	float4 diffuse			: SV_TARGET2;
};

PS_OUT PS(PS_IN input) {
	PS_OUT output;

	output.pos_W = float4(input.pos_W, 1.0f);
	output.normal = float4(input.normal, 1.0f);
	output.diffuse = float4(input.color, 1.0f);

	return output;
}