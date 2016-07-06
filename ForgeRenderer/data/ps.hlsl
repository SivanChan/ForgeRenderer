
// globals
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
    texture_color = shader_texture.Sample(sample_type, input.tex);
    return texture_color;
}