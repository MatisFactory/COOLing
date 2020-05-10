#include <main/models/obj_model_manager.hpp>
#include <main/core/settings/scene_settings.hpp>
#include <main/core/culling_wrapper.hpp>

#include <glm/ext/matrix_transform.hpp>

#include <random>

namespace
{
	constexpr size_t AIRPLANES_COUNT = 1000;
	constexpr size_t CUBES_COUNT = 1000;
	constexpr float SCALE_AIRPLANE = 20.f;
	constexpr float SCALE_CUBES = 25.f;

	const char* DEFAULT_VERTEX_SHADER = "../../../shaders/SimpleObj.vertexShader";
	const char* DEFAULT_FRAGMENT_SHADER = "../../../shaders/SimpleObj.fragmentShader";
}

ObjModelManager::ObjModelManager()
{
	loadAirplanes();
	loadCubes();

	addToCullingManager();
}

void ObjModelManager::draw()
{
	auto& cullingManager = CullingWrapper::instance().cullingManager();


	for (auto&[model, info] : m_objModels)
	{
		size_t i = 0;
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

// translation * rotation * scale

void ObjModelManager::loadAirplanes()
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

		transform = glm::scale(transform, glm::vec3(SCALE_AIRPLANE, SCALE_AIRPLANE, SCALE_AIRPLANE));

		transform = glm::rotate(transform, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));

		transform[3][0] = plate(gen);
		transform[3][1] = vertical(gen);
		transform[3][2] = plate(gen);

		transforms.push_back(transform);
	}

	m_objModels[airplane] = modelInfo;
}

void ObjModelManager::loadCubes()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution plate(-SCENE_WIDTH, SCENE_WIDTH);
	std::uniform_real_distribution vertical(-SCENE_HEIGHT, SCENE_HEIGHT);

	// load model
	std::vector<glm::mat4> transformsOfModels;
	transformsOfModels.reserve(CUBES_COUNT);

	ObjModel model("../../../obj_models/cube.obj");
	model.loadModel();
	ObjModelInfo modelInfo(transformsOfModels, Shader(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER), ObjModelDrawer(model));
	auto& transforms = modelInfo.transforms;

	for (size_t i = 0; i < CUBES_COUNT; i++)
	{
		glm::mat4 transform = glm::mat4(1.f);

		transform = glm::scale(transform, glm::vec3(SCALE_AIRPLANE, SCALE_AIRPLANE, SCALE_AIRPLANE));

		transform[3][0] = plate(gen);
		transform[3][1] = vertical(gen);
		transform[3][2] = plate(gen);

		transforms.push_back(transform);
	}

	m_objModels[model] = modelInfo;
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