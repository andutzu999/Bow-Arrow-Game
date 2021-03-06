#include "Tema2.h"
#include "Platforme.h"
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <Core/Engine.h>
#include <cmath>
#include <algorithm>


using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	renderCameraTarget = false;

	camera = new Vizualizare::Camera();
	camera->Set(glm::vec3(0, 1.5, 5), glm::vec3(0, 1.5, 0), glm::vec3(0, 1.5, 0));

	cnt = 1;
	limit = -33;
	playerSpeed = 5.0f;

	albOx = -7;
	albOy = 6.5;
	albOz = -5;

	rosuOx = -7;
	rosuOy = 6.5;
	rosuOz = -5;
	scaleOx = 2.01f;

	blocked = false;
	times = 0;
	

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		nr_placi = 15;
		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		P[1].Oz = -8;
		P[2].Oz = -10; 
		P[3].Oz = -4;

		srand(time(NULL));
		culori[0] = glm::vec3(1, 0, 0);  //rosu
		culori[1] = glm::vec3(1, 1, 0); //galben
		culori[2] = glm::vec3(0.96f, 0.66f, 0.007f); //portocaliu
		culori[3] = glm::vec3(0, 1, 0);  //verde
		culori[4] = glm::vec3(0.01f, 0.13f, 0.97f); //albastru
		culori[5] = glm::vec3(0.94f, 0.01f, 0.71f); //mov
		
		// adaugam placile intr un vector de structuri
		for (int i = 1; i <= nr_placi; i++) {

			CubeColor = culori[rand() % 5];

			if (i == 2)
				CubeColor = culori[4];

			vector<VertexFormat> vertices
			{
				VertexFormat(glm::vec3(-1, -1,  1), CubeColor),
				VertexFormat(glm::vec3(1, -1,  1), CubeColor),
				VertexFormat(glm::vec3(-1,  1,  1), CubeColor),
				VertexFormat(glm::vec3(1,  1,  1), CubeColor),
				VertexFormat(glm::vec3(-1, -1, -1), CubeColor),
				VertexFormat(glm::vec3(1, -1, -1), CubeColor),
				VertexFormat(glm::vec3(-1,  1, -1), CubeColor),
				VertexFormat(glm::vec3(1,  1, -1), CubeColor),
			};

			P[i].platforma = Platforme::CreateMesh("cube", vertices, indices);
			P[i].color = CubeColor;
			P[i].Oy = 0;

			if (i % 3 == 1)
				P[i].Ox = -4.5;
			else
				P[i].Ox = P[i - 1].Ox + 4.5f;

			if (i >= 4) 
				P[i].Oz = P[i - 3].Oz - 23;

		}



		// create Dreptunghi Alb combustibil
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1,1,1)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1,1,1)),
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1,1,1)),
			VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1,1,1)),
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1,1,1)),
			VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1,1,1)),
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1,1,1)),
			VertexFormat(glm::vec3(1,  1, -1), glm::vec3(1,1,1)),
		};

		dreptunghi_alb = Platforme::CreateMesh("cube", vertices, indices);

		// create Dreptunghi Alb combustibil
		vector<VertexFormat> vertices1
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1,0,0)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1,0,0)),
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1,0,0)),
			VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1,0,0)),
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1,0,0)),
			VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1,0,0)),
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1,0,0)),
			VertexFormat(glm::vec3(1,  1, -1), glm::vec3(1,0,0)),
		};

		dreptunghi_rosu = Platforme::CreateMesh("cube", vertices1, indices);
 

	}

	jumped = false;
	up = false;

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// shader sfera
	{
		Shader *shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;


	}

	// coordonate sfera
	moveSphereOx = 0;
	moveSphereOy = 0.55f;
	moveSphereOz = 0;

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);


	ok = 0;
	speedSet = false;
	

}


void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	// randare placi
	for(int i = 1; i <=  nr_placi; i++)
	{	
		glm::mat4 m = glm::mat4(1);
		m = glm::translate(m, glm::vec3(P[i].Ox, P[i].Oy, P[i].Oz));
		m = glm::scale(m, glm::vec3(1.5, 0.1, 10));
		RenderMesh(P[i].platforma, shaders["VertexColor"], m);
	}
	
	// aterizare
	Land(deltaTimeSeconds);

	// platforme generate la infinit
	GenerateToInfinit();


	// miscare sfera
	playermove(deltaTimeSeconds);

	{

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(moveSphereOx, moveSphereOy, moveSphereOz));
		if(renderCameraTarget == false)
			RenderMesh(meshes["sphere"], shaders["ShaderTema2"], modelMatrix);

	}

	// create dreptunghi alb
	{
		glm::mat4 m = glm::mat4(1);
		m = glm::translate(m, glm::vec3(albOx, albOy, albOz));
		m = glm::scale(m, glm::vec3(2, 0.2, 0.01));
		RenderMesh(dreptunghi_alb, shaders["VertexColor"], m);
	}

	// create dreptunghi rosu
	{
		glm::mat4 m = glm::mat4(1);
		m = glm::translate(m, glm::vec3(rosuOx, rosuOy, rosuOz));
		m = glm::scale(m, glm::vec3(scaleOx, 0.201, 0.011));
		RenderMesh(dreptunghi_rosu, shaders["VertexColor"], m);
	}

	// modificare dreptunghi rosu si alb
	// consum obisnuit de combustibil
	scaleOx -= deltaTimeSeconds * 0.05;
	rosuOx -= deltaTimeSeconds * 0.05;

	// limita 
	if (rosuOx <= moveSphereOx - 9){
		exit(0);
	}

	// setare viteza mare cand mingea aterizeaza 
	// pe o placa portocalie
	if (blocked == true && speedSet == false) {
		Set();
		
	}

	// setam viteza la loc
	if (speedSet == true && aux - 20 > moveSphereOz) {
		blocked = false;
		playerSpeed = 5;
		speedSet = false;
	}

}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}



void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
	{
		return;
	}

	// Render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Get shader location for uniform mat4 "Model"
	GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");

	// Set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Get shader location for uniform mat4 "View"
	GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");

	// Set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Get shader location for uniform mat4 "Projection"
	GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");

	// Set shader uniform "Projection" to projectionMatrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Get shader location for "Time"
	GLint timeLocation = glGetUniformLocation(shader->GetProgramID(), "Time");

	// Set shader uniform "Time" to elapsed time
	glUniform1f(timeLocation, (GLfloat)Engine::GetElapsedTime());

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;
	
	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}




void Tema2::OnInputUpdate(float deltaTime, int mods)
{
		// translatam camera in fata cu aceeasi viteza
		// cu care translatam si mingea
		camera->TranslateForward(deltaTime * playerSpeed);
		albOz -= deltaTime * playerSpeed;
		rosuOz -= deltaTime * playerSpeed;

		if (window->KeyHold(GLFW_KEY_W) && blocked == false) {

			if (playerSpeed <= 15) {
				playerSpeed += deltaTime * 30;
			}
				
		}
		if (window->KeyHold(GLFW_KEY_S) && blocked == false) {
			if (playerSpeed >= 3)
				playerSpeed -= deltaTime * 30;
		}

		if (window->KeyHold(GLFW_KEY_A)) {

			if (renderCameraTarget == false) {
				if (moveSphereOx >= -5) {
					moveSphereOx -= deltaTime * 5;
					camera->TranslateRight(-deltaTime * 5);
					albOx -= deltaTime * 5;
					rosuOx -= deltaTime * 5; 
    
				}
			}

			if (renderCameraTarget == true) {
				if (camera->position[0] >= -5) {
					camera->TranslateRight(-deltaTime * 5);
					albOx -= deltaTime * 5;
					rosuOx -= deltaTime * 5;
				}

				if (moveSphereOx >= -5)
					moveSphereOx -= deltaTime * 5;
			}
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera backwards
			if (renderCameraTarget == false) {
				if (moveSphereOx <= 5) {
					moveSphereOx += deltaTime * 5;
					camera->TranslateRight(deltaTime * 5);
					albOx += deltaTime * 5;
					rosuOx += deltaTime * 5;
				}


			}

			if (renderCameraTarget == true) {
				if (camera->position[0] <= 5) {
					camera->TranslateRight(deltaTime * 5);
					albOx += deltaTime * 5;
					rosuOx += deltaTime * 5;
				}

				if (moveSphereOx <= 5)
					moveSphereOx += deltaTime * 5;
			}
		}


}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_C) {
		renderCameraTarget = !renderCameraTarget;

		if (renderCameraTarget) {
			camera->MoveForward(5);
			albOz -= 5;
			rosuOz -= 5;
		}
		else {
			camera->MoveForward(-5);
			albOz += 5;
			rosuOz += 5;
		}
		
	}

	if (key == GLFW_KEY_SPACE) {

		jumped = true;
		up = true;

	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
	
		/*float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			//renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-(sensivityOX * deltaY));
			camera->RotateFirstPerson_OY(-(sensivityOY * deltaX));
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			//renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-(sensivityOX * deltaY));
			camera->RotateThirdPerson_OY(-(sensivityOY * deltaX));
		}
		*/        

	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}

// functia de coliziune cu o placa
int Tema2::Intersect() {

	for (int i = 1; i <= nr_placi; i++) {
		// 1.5 e jumate din latimea cubului
		float x = max((P[i].Ox - 1.5f), min(moveSphereOx, (P[i].Ox + 1.5f)));
		float y = max((P[i].Oy - 0.1f), min(moveSphereOy, (P[i].Oy + 0.1f)));
		float z = max((P[i].Oz - 10.0f), min(moveSphereOz, (P[i].Oz + 10.0f)));

		float distance = sqrt((x - moveSphereOx) * (x - moveSphereOx) +
			(y - moveSphereOy) * (y - moveSphereOy) +
			(z - moveSphereOz) * (z - moveSphereOz));

		if (distance < 0.5f)
			return i;
	}

	return 0;
}

// miscare jucator
void Tema2::playermove(float deltaTimeSeconds) {
	moveSphereOz -= playerSpeed * deltaTimeSeconds;

	if (jumped == true) {

		Jump(deltaTimeSeconds);
	}
}


void Tema2::Jump(float deltaTimeSeconds) {

	// moment in care am apasat space
	if (up == true) {

		if (renderCameraTarget == false) {

			if (moveSphereOy <= 3)
				moveSphereOy += deltaTimeSeconds * 3;

			else
				up = false;
		}

		if (renderCameraTarget == true) {
			if (camera->position[1] <= 3.9) {
				camera->TranslateUpword(deltaTimeSeconds * 3);
				albOy += deltaTimeSeconds * 3;
				rosuOy += deltaTimeSeconds * 3;
			}

			else
				up = false;

		}

	}

	// moment in care mingea/camera e in cadere
	if (up == false) {

		if (renderCameraTarget == false) {

			if (moveSphereOy > 0.595)
				moveSphereOy -= deltaTimeSeconds * 3;

		}

		if (renderCameraTarget == true) {
		
			if (camera->position[1] >= 1.5) {
				camera->TranslateUpword(-deltaTimeSeconds * 3);
				albOy -= deltaTimeSeconds * 3;
				rosuOy -= deltaTimeSeconds * 3;
			}

		}

	}

}


void Tema2::Land(float deltaTimeSeconds) {

	idx_placa = Intersect();


	// cadere
	if (idx_placa == 0 && up == false) {
		moveSphereOy -= 12 * deltaTimeSeconds;
	}

	// translatam camera in jos
	if (idx_placa == 0 && up == false && renderCameraTarget == true) {
		camera->TranslateUpword(-deltaTimeSeconds * 12);
	}

	// schimbam culoarea placii
	// are loc coliziunea
	if (idx_placa && jumped == true && up == false) {

		
		CheckColour();

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), culori[5]),
			VertexFormat(glm::vec3(1, -1,  1), culori[5]),
			VertexFormat(glm::vec3(-1,  1,  1), culori[5]),
			VertexFormat(glm::vec3(1,  1,  1), culori[5]),
			VertexFormat(glm::vec3(-1, -1, -1), culori[5]),
			VertexFormat(glm::vec3(1, -1, -1), culori[5]),
			VertexFormat(glm::vec3(-1,  1, -1), culori[5]),
			VertexFormat(glm::vec3(1,  1, -1), culori[5]),
		};

		P[idx_placa].platforma = Platforme::CreateMesh("cube", vertices, indices);
		
	}
}

// generam placile la infinit
void Tema2::GenerateToInfinit() {

	if (moveSphereOz <= limit) {

		for (int t = cnt; t <= cnt + 2; t++) {

			CubeColor = culori[rand() % 5];
			vector<unsigned short> indices =
			{
				0, 1, 2,		1, 3, 2,
				2, 3, 7,		2, 7, 6,
				1, 7, 3,		1, 5, 7,
				6, 7, 4,		7, 5, 4,
				0, 4, 1,		1, 4, 5,
				2, 6, 4,		0, 2, 4,
			};

			vector<VertexFormat> vertices
			{
				VertexFormat(glm::vec3(-1, -1,  1),CubeColor),
				VertexFormat(glm::vec3(1, -1,  1), CubeColor),
				VertexFormat(glm::vec3(-1,  1,  1), CubeColor),
				VertexFormat(glm::vec3(1,  1,  1), CubeColor),
				VertexFormat(glm::vec3(-1, -1, -1), CubeColor),
				VertexFormat(glm::vec3(1, -1, -1), CubeColor),
				VertexFormat(glm::vec3(-1,  1, -1), CubeColor),
				VertexFormat(glm::vec3(1,  1, -1), CubeColor),
			};

			P[t].platforma = Platforme::CreateMesh("cube", vertices, indices);
			P[t].Oz -= 115;
			P[t].color = CubeColor;

		}

		cnt = cnt + 3;
		if (cnt == 16)
			cnt = 1;

		limit = limit - 23;
	}
}

void Tema2::CheckColour() {

	//rosu
			//jocul se termina instant
	if (P[idx_placa].color == culori[0]) {
		exit(0);
	}

	//galben
	//pierdem o parte din combustibil
	if (P[idx_placa].color == culori[1]) {

		rosuOx -= 0.2;
		scaleOx -= 0.2;
		P[idx_placa].color = culori[5];
		return;
	}

	//portocaliu
	if (P[idx_placa].color == culori[2]) {

		blocked = true;
		return;
	}

	//verde
	if (P[idx_placa].color == culori[3]) {

		scaleOx += 0.3;
		rosuOx += 0.3;
		P[idx_placa].color = culori[5];
		return;
	}

}

void Tema2::Set() {

	aux = moveSphereOz;
	playerSpeed = 20;
	speedSet = true;
	
	return;
}

