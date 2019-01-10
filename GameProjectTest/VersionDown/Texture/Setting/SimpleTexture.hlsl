//グローバル

Texture2D g_texColor: register(t0);//テクスチャーはレジスターt(n)
SamplerState g_samLinear : register(s0);//サンプラーはレジスターs(n)　レジスターはGPUの計算できる場所的なものかな？

cbuffer global
{
	matrix g_WVP; //ワールドから射影までの変換行列
	float g_vDiffuse;//ディフューズ色
};
//構造体
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;  //たぶんUV座標
};

//
//
//バーテックスシェーダー
PS_INPUT VS(float4 Pos : POSITION,float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = mul(Pos, g_WVP);
	output.Tex = Tex;
	
	return Out;
}
//
//
//ピクセルシェーダー
float4 PS(VS_OUTPUT input) : SV_Target
{
	return g_texColor.Sample(g_samLinear,input.Tex);// テクスチャーの本体とサンプラーをもとに input.texのUV座標から色を決定してそれを返している
}