#include <main/models/obj_model_manager.hpp>
#include <main/core/settings/scene_settings.hpp>
#include <main/core/culling_wrapper.hpp>

#include <glm/ext/matrix_transform.hpp>

#include <random>

namespace
{
	constexpr size_t AIRPLANES_COUNT = 10000;
	constexpr size_t CUBES_COUNT = 1000;
	constexpr float SCALE_AIRPLANE = 20.f;
	constexpr float SCALE_CUBES_X = 40;
	constexpr float SCALE_CUBES_Y = 100;
	constexpr float SCALE_CUBES_Z = 20;

	const glm::vec3 CUBE_COLOR = glm::vec3(0.15f, 0.15f, 0.15f);
	const glm::vec3 AIRPLANE_COLOR = glm::vec3(0.4f, 0.8f, 0.6f);

	const char* DEFAULT_VERTEX_SHADER = "../../../shaders/SimpleObj.vert";
	const char* DEFAULT_FRAGMENT_SHADER = "../../../shaders/SimpleObj.frag";

	bool ACTIVE_SHADER_TO_OCCLUSION_QUERY = false;
}

ObjModelManager::ObjModelManager()
	: m_shader(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER)
{
	loadCubes();
	loadAirplanes();
	//loadModel("../../../obj_models/cat.obj", 20000, glm::vec3(20.f, 20.f, 20.f), glm::vec4(1.f), false);
	//loadModel("../../../obj_models/gun1.obj", 10000, glm::vec3(20.f, 20.f, 20.f), glm::vec4(1.f), true);
	/*loadModel("../../../obj_models/Leopard.obj", 1000, glm::vec3(20.f, 20.f, 20.f), glm::vec4(1.f), true);
	loadModel("../../../obj_models/IS7.obj", 1000, glm::vec3(20.f, 20.f, 20.f), glm::vec4(1.f), true);*/
	//loadModel("../../../obj_models/t_34_obj.obj", 1000, glm::vec3(20.f, 20.f, 20.f), glm::vec4(1.f), false);

	addToCullingManager();
	auto& cullingManager = CullingWrapper::instance().cullingManager();
	cullingManager.setupQueriesManager([this](const Cooling::AABB& aabb)
	{
		drawBox(aabb, true);
	});

}

void ObjModelManager::draw()
{
	ACTIVE_SHADER_TO_OCCLUSION_QUERY = false;
	m_countDrawed = 0;
	auto& cullingManager = CullingWrapper::instance().cullingManager();

	m_shader.use();
	
	for (auto&[model, info] : m_objModels)
	{
		size_t i = 0;
		info.drawer.activateShader(m_shader);

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

	// should be at the end of draw
	if(m_showSceneAABB)
	{
		drawBox(SCENE_AABB, true);
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

bool ObjModelManager::showSceneAABB() const
{
	return m_showSceneAABB;
}

void ObjModelManager::showSceneAABB(bool value)
{
	m_showSceneAABB = value;
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

void ObjModelManager::loadModel(const std::string& filename, size_t count, const glm::vec3& scale, const glm::vec3& color, bool hardToDraw)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution plate(-SCENE_WIDTH, SCENE_WIDTH);
	std::uniform_real_distribution vertical(-SCENE_HEIGHT, SCENE_HEIGHT);

	// load model
	std::vector<glm::mat4> transformsOfModels;
	transformsOfModels.reserve(count);

	ObjModel model(filename);
	model.loadModel();
	ObjModelInfo modelInfo(transformsOfModels, Shader(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER), ObjModelDrawer(model), color, hardToDraw);
	auto& transforms = modelInfo.transforms;

	for (size_t i = 0; i < count; i++)
	{
		glm::mat4 transform = glm::mat4(1.f);

		transform = glm::scale(transform, glm::vec3(scale.x, scale.y, scale.z));

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
	if(!ACTIVE_SHADER_TO_OCCLUSION_QUERY)
	{
		ACTIVE_SHADER_TO_OCCLUSION_QUERY = true;
		drawer.activateShader(m_shader);
	}
	//static Shader shader(DEFAULT_FRAGMENT_SHADER, DEFAULT_VERTEX_SHADER);

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