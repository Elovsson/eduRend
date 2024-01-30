#include "Camera.h"

using namespace linalg;

void Camera::MoveTo(const vec4f& position) noexcept
{
	m_position = position;
}

void Camera::Move(const vec4f& direction, const float& rotation_x) noexcept
{
	mat4f temp = { 0.0f, - rotation_x, 0.0f, 0.0f };
	m_position += temp * direction;
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

	return m_rotation.inverse() * mat4f::translation(m_position.x, m_position.y, m_position.z).inverse();
}

mat4f Camera::ProjectionMatrix() const noexcept
{
	return mat4f::projection(m_vertical_fov, m_aspect_ratio, m_near_plane, m_far_plane);
}