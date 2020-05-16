#include <main/models/obj_model_manager.hpp>
#include <main/core/settings/scene_settings.hpp>
#include <main/core/culling_wrapper.hpp>

#include <glm/ext/matrix_transform.hpp>

#include <random>

namespace
{
	constexpr size_t AIRPLANES_COUNT = 1000;
	constexpr size_t CUBES_COUNT = 500;
	constexpr float SCALE_AIRPLANE = 20.f;
	constexpr float SCALE_CUBES_X = 40;
	constexpr float SCALE_CUBES_Y = 100;
	constexpr float SCALE_CUBES_Z = 20;

	const glm::vec3 CUBE_COLOR = glm::vec3(0.15f, 0.15f, 0.15f);
	const glm::vec3 AIRPLANE_COLOR = glm::vec3(0.4f, 0.8f, 0.6f);

	const char* DEFAULT_VERTEX_SHADER = "../../../shaders/SimpleObj.vert";
	const char* DEFAULT_FRAGMENT_SHADER = "../../../shaders/SimpleObj.frag";
}

ObjModelManager::ObjModelManager()
{
	loadCubes();
	loadAirplanes();

	addToCullingManager();
	auto& cullingManager = CullingWrapper::instance().cullingManager();
	cullingManager.setupQueriesManager([this](const Cooling::AABB& aabb)
	{
		drawBox(aabb, true);
	});

}

void ObjModelManager::draw()
{
	m_countDrawed = 0;
	auto& cullingManager = CullingWrapper::instance().cullingManager();

	for (auto&[model, info] : m_objModels)
	{
		size_t i = 0;
		info.drawer.activateShader(info.shader);

		for (const auto& transform : info.transforms)
		{
			if (cullingManager.isVisible(info.uids[i++]))
			{
			/*	if (info.hardToDraw)
				{
					drawBox(Cooling::transformedAABB(model.getAABB(), transform), true);
				}*/
				info.drawer.draw(transform, info.color);
				m_countDrawed++;
			}
		}
	}
}

bool ObjModelManager::enabledOcclusionQueries() const
{
	return m_occlusionQueryEnabled;
}

void ObjModelManager::setEnabledOcclusionQueris(bool value)
{
	m_occlusionQueryEnabled = value;
}

size_t ObjModelManager::countDrawed() const
{
	return m_countDrawed;
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
	ObjModelInfo modelInfo({}, Shader(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER), ObjModelDrawer(airplane), AIRPLANE_COLOR, true);
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
	ObjModelInfo modelInfo(transformsOfModels, Shader(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER), ObjModelDrawer(model), CUBE_COLOR);
	auto& transforms = modelInfo.transforms;

	for (size_t i = 0; i < CUBES_COUNT; i++)
	{
		glm::mat4 transform = glm::mat4(1.f);

		transform = glm::scale(transform, glm::vec3(SCALE_CUBES_X, SCALE_CUBES_Y, SCALE_CUBES_Z));

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
			modelInfo.uids.push_back(cullingManager.registerObject(Cooling::transformedAABB(model.getAABB(), transform), modelInfo.hardToDraw));
		}
	}
}

void ObjModelManager::drawBox(const Cooling::AABB& aabb, bool wireframe)
{
	// should be active shader
	// cube from -1 to 1 by each axis
	static ObjModel cube("../../../obj_models/cube.obj");
	static const glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
	if(!cube.isLoaded())
	{
		cube.loadModel();
	}
	static ObjModelDrawer drawer(cube);

	const glm::vec3 halfDiagonal = (aabb.max - aabb.min) * 0.5f;
	const glm::vec3 position = aabb.min + halfDiagonal;

	glm::mat4 transform = glm::mat4(1.f);

	transform = glm::translate(transform, position);
	transform = glm::scale(transform, halfDiagonal);

	if (wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		drawer.draw(transform, color);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		drawer.draw(transform, color);
	}
}