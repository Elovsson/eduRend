#include "Camera.h"

using namespace linalg;

void Camera::MoveTo(const vec3f& position) noexcept
{
	m_position = position;
}

void Camera::Move(const vec3f& direction, const float& rotation) noexcept
{
	m_movementRotation = mat4f::rotation(0, -rotation, 0);
	vec4f fwd = m_movementRotation * vec4f{ direction,0.0f };
	m_position += fwd.xyz();
}

void Camera::Rotation(float x, float y) 
{

	m_rotation = mat4f::rotation(0, -x, -y);
}

mat4f Camera::WorldToViewMatrix() const noexcept
{
	// Assuming a camera's position and rotation is defined by matrices T(p) and R,
	// the View-to-World transform is T(p)*R (for a first-person style camera).
	//
	// World-to-View then is the inverse of T(p)*R;
	//		inverse(T(p)*R) = inverse(R)*inverse(T(p)) = transpose(R)*T(-p)
	// Since now there is no rotation, this matrix is simply T(-p)

	return m_rotation.inverse() * mat4f::translation(m_position).inverse();
}

mat4f Camera::ProjectionMatrix() const noexcept
{
	return mat4f::projection(m_vertical_fov, m_aspect_ratio, m_near_plane, m_far_plane);
}