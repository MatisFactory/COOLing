#include <cooling/frustum_view.hpp>

namespace Cooling
{
FrustumView::FrustumView(const glm::mat4& viewProjection)
	: m_viewProjection(viewProjection)
{
	updateFrustumView();
}

void FrustumView::setViewProjection(const glm::mat4& viewProjection)
{
	m_viewProjection = viewProjection;
	updateFrustumView();
}

FrustumPlanes FrustumView::getFrustumPlanes() const
{
	return m_planes;
}

void FrustumView::updateFrustumView()
{
	for(int i = 0; i < 4; i++) { m_planes.left[i] = m_viewProjection[3][i] + m_viewProjection[0][i]; }
	for(int i = 0; i < 4; i++) { m_planes.right[i] = m_viewProjection[3][i] - m_viewProjection[0][i]; }
	for(int i = 0; i < 4; i++) { m_planes.bottom[i] = m_viewProjection[3][i] + m_viewProjection[1][i]; }
	for(int i = 0; i < 4; i++) { m_planes.top[i] = m_viewProjection[3][i] - m_viewProjection[1][i]; }
	for(int i = 0; i < 4; i++) { m_planes.near[i] = m_viewProjection[3][i] + m_viewProjection[2][i]; }
	for(int i = 0; i < 4; i++) { m_planes.far[i] = m_viewProjection[3][i] - m_viewProjection[2][i]; }

	m_planes.left = glm::normalize(m_planes.left);
	m_planes.right = glm::normalize(m_planes.right);
	m_planes.bottom = glm::normalize(m_planes.bottom);
	m_planes.top = glm::normalize(m_planes.top);
	m_planes.near = glm::normalize(m_planes.near);
	m_planes.far = glm::normalize(m_planes.far);
}

} // namespace Cooling