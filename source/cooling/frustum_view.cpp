#include <cooling/frustum_view.hpp>

namespace Cooling
{
FrustumView::FrustumView()
{
}

void FrustumView::setViewProjection(const glm::mat4& viewProjection)
{
	m_viewProjection = viewProjection;
}

FrustumPlanes FrustumView::getFrustumPlanes() const
{
	return m_planes;
}

void FrustumView::updateFrustumView()
{
	for(int i = 0; i < 4; i++) { m_planes[0][i] = m_viewProjection[i][3] + m_viewProjection[i][0]; } // left
	for(int i = 0; i < 4; i++) { m_planes[1][i] = m_viewProjection[i][3] - m_viewProjection[i][0]; } // right
	for(int i = 0; i < 4; i++) { m_planes[2][i] = m_viewProjection[i][3] + m_viewProjection[i][1]; } // bottom
	for(int i = 0; i < 4; i++) { m_planes[3][i] = m_viewProjection[i][3] - m_viewProjection[i][1]; } // top
	for(int i = 0; i < 4; i++) { m_planes[4][i] = m_viewProjection[i][3] + m_viewProjection[i][2]; } // near
	for(int i = 0; i < 4; i++) { m_planes[5][i] = m_viewProjection[i][3] - m_viewProjection[i][2]; } // far

	for (auto& plane : m_planes.planes)
	{
		plane = glm::normalize(plane);
	}
}

} // namespace Cooling