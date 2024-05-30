
Texture2D texDiffuse : register(t0);
Texture2D texNormal : register(t1);
TextureCube texCubeMap : register(t2);

cbuffer LightCamerBuffer : register(b0)
{
    float4 cameraPosition;
    float4 lightPosition;
}

cbuffer MaterialBuffer : register(b1)
{
    float4 specular;
    float4 diffuse;
    float4 ambient;
    float shininess;
}


struct PSIn
{
    float4 Pos : SV_Position;
    float3 Normal : NORMAL;
    float2 TexCoord : TEX;
    float4 PosWorld : POSWORLD;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
};

SamplerState texSampler : register(s0);
SamplerState cubeMapSampler : register(s1);



//-----------------------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------------------

float4 PS_main(PSIn input) : SV_Target
{
	// Debug shading #1: map and return normal as a color, i.e. from [-1,1]->[0,1] per component
	// The 4:th component is opacity and should be = 1
	//return float4(input.Normal * 0.5 + 0.5, 1);

	// Debug shading #2: map and return texture coordinates as a color (blue = 0)
	//	return float4(input.TexCoord, 0, 1);
	
    float4 texColor = texDiffuse.Sample(texSampler, input.TexCoord);
	
    float3 lightDir = normalize(lightPosition.xyz - input.PosWorld.xyz);
    float3 viewDir = normalize(cameraPosition.xyz - input.PosWorld.xyz);
    float3 normal = normalize(input.Normal);
	
    int normalWidth, normalHeight;
    texNormal.GetDimensions(normalWidth, normalHeight);
    
    if (normalWidth != 0)
    {
        float3 colornormal = texNormal.Sample(texSampler, input.TexCoord).xyz * 2 - 1;
	
        float3x3 TBN = transpose(float3x3(input.Tangent, input.Binormal, input.Normal));
        normal = mul(TBN, colornormal);
    }

    //return float4(normal * 0.5 + 0.5, 1);
	
    float3 reflectDir = reflect(-lightDir, normal);
    
    float3 reflectVec = reflect(-viewDir, normal);
    float4 cubeColor = texCubeMap.Sample(cubeMapSampler, reflectVec);
	
    float diffuseIntensity = max(0.0, dot(normal, lightDir));
    float4 diffuseColor = (diffuse / 255) * diffuseIntensity * texColor;
	
    float specularIntensity = pow(max(0.0, dot(reflectDir, viewDir)), shininess);
    float4 specularColor = (specular / 255) * specularIntensity;
	
    float4 ambientColor = (ambient / 255);
    float4 finalColor = ambientColor + diffuseColor + specularColor + cubeColor;

    return finalColor;
	
}