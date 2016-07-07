
// globals
cbuffer MatrixBuffer
{
	matrix wvp;
	float4 flag;
};
Texture2D shader_texture;
SamplerState sample_type;

// pixel input type
struct PixelInputType
{
    float4 position : SV_Position;
    float2 tex : TEXCOORD;
};

// main
float4 ps_main(PixelInputType input) : SV_TARGET
{
    float4 texture_color;
	if (flag.x > 0.5f) // 线框模式时，不使用贴图采样颜色
		texture_color = float4(1.0f, 0.0f, 0.0f, 1.0f);
	else
		texture_color = shader_texture.Sample(sample_type, input.tex);
    return texture_color;
}