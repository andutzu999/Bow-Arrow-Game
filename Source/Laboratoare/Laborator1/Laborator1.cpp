#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1() :
	colourCase(0), objectCase(0), posX(0), posY(0), posZ(0)
{
	changeClearColour();
	changeObject();
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* boxMesh = new Mesh("box");
		boxMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[boxMesh->GetMeshID()] = boxMesh;

		Mesh* sphereMesh = new Mesh("sphere");
		sphereMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[sphereMesh->GetMeshID()] = sphereMesh;

		Mesh* teapotMesh = new Mesh("teapot");
		teapotMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[teapotMesh->GetMeshID()] = teapotMesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(clearRed, clearGreen, clearBlue, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	RenderMesh(meshes[objName], glm::vec3(posX, posY, posZ), objScale); //ex2
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) //ex5
	{
		if (window->KeyHold(GLFW_KEY_W))
		{
			posZ -= deltaTime * SPEED_FACTOR;
		}
		if (window->KeyHold(GLFW_KEY_A))
		{
			posX -= deltaTime * SPEED_FACTOR;
		}
		if (window->KeyHold(GLFW_KEY_S))
		{
			posZ += deltaTime * SPEED_FACTOR;
		}
		if (window->KeyHold(GLFW_KEY_D))
		{
			posX += deltaTime * SPEED_FACTOR;
		}
		if (window->KeyHold(GLFW_KEY_E))
		{
			posY += deltaTime * SPEED_FACTOR;
		}
		if (window->KeyHold(GLFW_KEY_Q))
		{
			posY -= deltaTime * SPEED_FACTOR;
		}
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_C) { //ex3
		colourCase = (colourCase + 1) % COLOURS_NUM;

		changeClearColour();
	}

	if (key == GLFW_KEY_O) { //ex4
		objectCase = (objectCase + 1) % OBJECTS_NUM;

		changeObject();
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}

void Laborator1::changeClearColour()
{
	switch (colourCase) //ex3
	{
	case 1:
		clearRed = 0.25f;
		clearGreen = 0.25f;
		clearBlue = 0.25f;
		break;

	case 2:
		clearRed = 0.75f;
		clearGreen = 0.75f;
		clearBlue = 0.75f;
		break;

	default:
		clearRed = 0;
		clearGreen = 0;
		clearBlue = 0;
		break;
	}
}

void Laborator1::changeObject()
{
	switch (objectCase) //ex4
	{
	case 1:
		objName = "sphere";
		objScale = glm::vec3(1);
		break;

	case 2:
		objName = "teapot";
		objScale = glm::vec3(1);
		break;

	default:
		objName = "box";
		objScale = glm::vec3(1);
		break;
	}
}