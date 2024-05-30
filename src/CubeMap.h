#pragma once
#include "texture.h"
#include <iostream>
#include "stdafx.h"

class CubeMap
{
private:

	ID3D11Device* const			cm_dxdevice;
	ID3D11DeviceContext* const	cm_dxdevice_context;
	ID3D11SamplerState* cm_sampler = nullptr;

	Texture cube_texture;

public:

	CubeMap(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context);

	~CubeMap() {}
};

