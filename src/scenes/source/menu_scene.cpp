#include "../include/menu_scene.h"

using namespace GAME_NAMESPACE::GameScene;

Menu::Menu(float width, float height, System::Renderer& renderer)
	: m_width(width)
	, m_height(height)
	, m_renderer(renderer)
{
	onAttach();
}

Menu::~Menu()
{
	onDetatch();
}

void Menu::update(float dt, const glm::vec3& cameraView)
{

}

Scene* Menu::nextState()
{
	return nullptr;
}

void Menu::onAttach()
{

}

void Menu::onDetatch()
{

}

void Menu::render(const glm::vec3& cameraView)
{

}
