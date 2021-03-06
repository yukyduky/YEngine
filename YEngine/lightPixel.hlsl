Texture2D texPosition	: register(t0);
Texture2D texNormal		: register(t1);
Texture2D texDiffuse	: register(t2);

void LoadGeoPassData(in float2 screenCoords, out float3 pos_W, out float3 normal, out float3 color);

float4 PS(float4 position_S : SV_POSITION) : SV_TARGET
{
	float3 pos_W, normal, color;
	// position_S.xy is literally screen coords
	float2 screenCoords = position_S.xy;

	// Load all the data from the geo pass
	LoadGeoPassData(screenCoords, pos_W, normal, color);

	color = color / 255.0f;
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
	return float4(color, 1.0f);
}

void LoadGeoPassData(in float2 screenCoords, out float3 pos_W, out float3 normal, out float3 color)
{
	int3 texCoords = int3(screenCoords, 0.0f);

	pos_W = texPosition.Load(texCoords).xyz;
	normal = texNormal.Load(texCoords).xyz;
	color = texDiffuse.Load(texCoords).xyz;
}