#include <main/models/obj_model_manager.hpp>
#include <main/core/settings/scene_settings.hpp>
#include <main/core/culling_wrapper.hpp>

#include <glm/ext/matrix_transform.hpp>

#include <random>

namespace
{
	constexpr size_t AIRPLANES_COUNT = 1000;
	constexpr float SCALE_AIRPLANE = 25.f;

	const char* DEFAULT_VERTEX_SHADER = "../../../shaders/SimpleObj.vertexShader";
	const char* DEFAULT_FRAGMENT_SHADER = "../../../shaders/SimpleObj.fragmentShader";
}

ObjModelManager::ObjModelManager()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution plate(-SCENE_WIDTH, SCENE_WIDTH);
	std::uniform_real_distribution vertical(-SCENE_HEIGHT, SCENE_HEIGHT);

	// load airplanes
	std::vector<glm::mat4> airplanes;
	airplanes.reserve(AIRPLANES_COUNT);

	ObjModel airplane("../../../obj_models/airplane.obj");
	airplane.loadModel();
	ObjModelInfo modelInfo({}, Shader(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER), ObjModelDrawer(airplane));
	auto& transforms = modelInfo.transforms;

	for (size_t i = 0; i < AIRPLANES_COUNT; i++)
	{
		glm::mat4 transform = glm::mat4(1.f);
		transform[3][0] = plate(gen);
		transform[3][1] = vertical(gen);
		transform[3][2] = plate(gen);

		transform = glm::scale(transform, glm::vec3(SCALE_AIRPLANE, SCALE_AIRPLANE, SCALE_AIRPLANE));
		
		transforms.push_back(transform);
	}

	m_objModels[airplane] = modelInfo;

	addToCullingManager();
}

void ObjModelManager::draw()
{
	auto& cullingManager = CullingWrapper::instance().cullingManager();

	size_t i = 0;

	for (auto&[model, info] : m_objModels)
	{
		info.drawer.activateShader(info.shader);

		for (const auto& transform : info.transforms)
		{
			if (cullingManager.isVisible(info.uids[i++]))
			{
				info.drawer.draw(transform);
			}
		}
	}
}

void ObjModelManager::addToCullingManager()
{
	auto& cullingManager = CullingWrapper::instance().cullingManager();

	for (auto&[model, modelInfo] : m_objModels)
	{
		for (const auto& transform : modelInfo.transforms)
		{
			modelInfo.uids.push_back(cullingManager.registerObject(Cooling::transformedAABB(model.getAABB(), transform)));
		}
	}
}