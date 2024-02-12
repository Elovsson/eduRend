/**
 * @file buffers.h
 * @brief Contains constant buffers
*/

#pragma once

#include "vec/mat.h"

/**
 * @brief Contains transformation matrices.
*/
struct TransformationBuffer
{
	linalg::mat4f ModelToWorldMatrix; //!< Matrix for converting from object space to world space.
	linalg::mat4f WorldToViewMatrix; //!< Matrix for converting from world space to view space.
	linalg::mat4f ProjectionMatrix; //!< Matrix for converting from view space to clip cpace.
};
struct LightCameraBuffer
{
	linalg::vec4f cameraPosition;
	linalg::vec4f lightPosition;
};
struct MaterialBuffer
{
	linalg::float4 specular;
	linalg::float4 diffuse;
	linalg::float4 ambient;
	float shininess;
	float x;
};