#include <glfw3.h>

#include "../../system/include/resource_manager.h"

#include "../include/level1.h"
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

void Menu::onAttach()
{
	glm::vec3 panelScale = glm::vec3(400.0f, 300.0f, 0.0f);
	glm::vec3 panelPos = glm::vec3(m_width / 2.0f - panelScale.x / 2.0f, m_height / 2.0f - panelScale.y / 2.0, 0.0f);

	glm::vec3 buttonScale = glm::vec3(panelScale.x / 2.0f, 50.0f, 0.0f);
	glm::vec3 startPos = glm::vec3(panelPos.x + panelScale.x / 4.0f, panelPos.y + buttonScale.y, 0.0f);
	glm::vec3 exitPos = glm::vec3(panelPos.x + panelScale.x / 4.0f, panelPos.y + panelScale.y - 2.0f * buttonScale.y, 0.0f);

	m_panel = GameModule::GameObj(panelPos, panelScale, glm::vec3(1.0f));
	m_start = Button(startPos, buttonScale, glm::vec3(0.0f));
	m_exit = Button(exitPos, buttonScale, glm::vec3(0.0f));
}

void Menu::update(float dt, const glm::vec3& cameraView)
{
	render(cameraView);
}

void Menu::processInput(float dt, glm::vec3& cameraView, const glm::vec3& cursorPos, bool* const keys)
{
	bool startCollide = 
		cursorPos.x <= m_start.getPos().x + m_start.getScale().x && cursorPos.x >= m_start.getPos().x &&
		cursorPos.y <= m_start.getPos().y + m_start.getScale().y && cursorPos.y >= m_start.getPos().y;

	bool exitCollide =
		cursorPos.x <= m_exit.getPos().x + m_exit.getScale().x && cursorPos.x >= m_exit.getPos().x &&
		cursorPos.y <= m_exit.getPos().y + m_exit.getScale().y && cursorPos.y >= m_exit.getPos().y;
	
	if (keys[GLFW_MOUSE_BUTTON_LEFT])
	{
		if (startCollide)
		{
			m_nextScene = Scenes::Level1Scene;
		}
		else if (exitCollide)
		{
			m_nextScene = Scenes::ShutDown;
		}
		keys[GLFW_MOUSE_BUTTON_LEFT] = false;
	}
}

void Menu::onDetatch()
{

}

void Menu::render(const glm::vec3& cameraView)
{
	m_panel.draw(System::ResourceManager::getInstance().getShader("base_proj"), m_renderer, cameraView);
	m_start.draw(System::ResourceManager::getInstance().getShader("base_proj"), m_renderer, cameraView);
	m_exit.draw(System::ResourceManager::getInstance().getShader("base_proj"), m_renderer, cameraView);
}
