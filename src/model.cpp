
#include "model.h"

void Model::compute_TB(Vertex& v0, Vertex& v1, Vertex& v2)
{
	const vec3f p0 = v0.Position;
	const vec3f p1 = v1.Position;
	const vec3f p2 = v2.Position;

	const vec2f t0 = v0.TexCoord;
	const vec2f t1 = v1.TexCoord;
	const vec2f t2 = v2.TexCoord;

	vec3f D = p1 - p0;
	vec2f F = t1 - t0;

	vec3f E = p2 - p0;
	vec2f G = t2 - t0;

	// D = F.x * T  +  F.y * B
	// E = G.x * T  +  G.y * B

	float det = 1.0f / (F.x * G.y - F.y * G.x);
	const mat2f A = mat2f(G.y, -F.y, -G.x, F.x) * det;

	vec3f T((A.m11 * D.x + A.m12 * E.x), (A.m11 * D.y + A.m12 * E.y), (A.m11 * D.z + A.m12 * E.z));
	vec3f B((A.m21 * D.x + A.m22 * E.x), (A.m21 * D.y + A.m22 * E.y), (A.m21 * D.z + A.m22 * E.z));

	v0.Tangent += T;
	v1.Tangent += T;
	v2.Tangent += T;

	v0.Binormal += B;
	v1.Binormal += B;
	v2.Binormal += B;
}

void Model::ComputeTangents(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices)
{
	for (int idx = 0; idx < indices.size(); idx += 3) // For all triangles
	{
		Model::compute_TB(
			vertices[ indices[ idx + 0 ] ],
			vertices[ indices[ idx + 1 ] ],
			vertices[ indices[ idx + 2 ] ]);
	}

	for (long vtxIdx = 0; vtxIdx < vertices.size(); vtxIdx++)
	{
		Vertex& vtx = vertices[ vtxIdx ];
		const vec3f n = vtx.Normal;
		const vec3f t = vtx.Tangent;

		// Gram-Schmidt orthogonalize
		vtx.Tangent = (t - n * n.dot(t)).normalize();

		// Calculate handedness
		vec3f nCrossT = (n % t);
		float w = (nCrossT.dot(vtx.Binormal) < 0.0F) ? -1.0F : 1.0F;
		vtx.Binormal = (nCrossT * w).normalize();
	}
}