#pragma once
#include <DirectXMath.h>
#include "Sprite.h"

class Model;

class SpeedMeter
{
private:
	Texture* m_pTexture;
	DirectX::XMFLOAT2 m_pos;
	ID3D11Buffer* m_pNumberBuf;
	ID3D11ShaderResourceView* m_pNumberTex;
	int m_nSpeed;
	bool m_bSpeedAdded;

public:
	SpeedMeter();
	~SpeedMeter();
	void Update();
	void Draw();
	void SetSpeed(int speed);

private:
	void UpdateSpeedTexcoord();
};

