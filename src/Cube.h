#pragma once
#include "model.h"
class Cube : public Model
{
	unsigned m_number_of_indices = 0;

	Material m_material[5];



public:

	Cube(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context);

	~Cube() {}

	virtual void Render() const;

	void InvertCube(Vertex& v0, Vertex& v1, Vertex& v2, Vertex& v3);
};

