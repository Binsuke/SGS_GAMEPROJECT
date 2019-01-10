//�O���[�o��

Texture2D g_texColor: register(t0);//�e�N�X�`���[�̓��W�X�^�[t(n)
SamplerState g_samLinear : register(s0);//�T���v���[�̓��W�X�^�[s(n)�@���W�X�^�[��GPU�̌v�Z�ł���ꏊ�I�Ȃ��̂��ȁH

cbuffer global
{
	matrix g_WVP; //���[���h����ˉe�܂ł̕ϊ��s��
	float g_vDiffuse;//�f�B�t���[�Y�F
};
//�\����
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;  //���Ԃ�UV���W
};

//
//
//�o�[�e�b�N�X�V�F�[�_�[
PS_INPUT VS(float4 Pos : POSITION,float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = mul(Pos, g_WVP);
	output.Tex = Tex;
	
	return Out;
}
//
//
//�s�N�Z���V�F�[�_�[
float4 PS(VS_OUTPUT input) : SV_Target
{
	return g_texColor.Sample(g_samLinear,input.Tex);// �e�N�X�`���[�̖{�̂ƃT���v���[�����Ƃ� input.tex��UV���W����F�����肵�Ă����Ԃ��Ă���
}