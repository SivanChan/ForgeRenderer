

// globals
cbuffer MatrixBuffer
{
    matrix wvp;
};

// vertex input type
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD;
};

// pixel input type
struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD;
};

// main
PixelInputType vs_main(VertexInputType input)
{
    PixelInputType output;

    input.position.w = 1.0f;
    output.position = mul(input.position, wvp);
    output.tex = input.tex;

    return output;
}