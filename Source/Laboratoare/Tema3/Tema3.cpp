#include "Tema3.h"
#include "Platformele.h"
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <Core/Engine.h>
#include <cmath>
#include <algorithm>


using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	renderCameraTarget = false;

	camera = new Vizualizare::Camera_1();
	camera->Set(glm::vec3(0, 1.5, 5), glm::vec3(0, 1.5, 0), glm::vec3(0, 1.5, 0));

	cnt_placi = 1;
	cnt_case = 1;
	limit_placi = -33;
	limit_case = -35;
	playerSpeed = 5.0f;

	
	scaleOx = 2.01f;

	blocked = false;
	times = 0;

	srand(time(NULL));
	culori[0] = glm::vec3(1, 0, 0);  //rosu
	culori[1] = glm::vec3(1, 1, 0); //galben
	culori[2] = glm::vec3(0.96f, 0.66f, 0.007f); //portocaliu
	culori[3] = glm::vec3(0, 1, 0);  //verde
	culori[4] = glm::vec3(0.01f, 0.13f, 0.97f); //albastru
	culori[5] = glm::vec3(0.94f, 0.01f, 0.71f); //mov

	vector<unsigned short> indices =
	{
		0, 1, 2,		1, 3, 2,
		2, 3, 7,		2, 7, 6,
		1, 7, 3,		1, 5, 7,
		6, 7, 4,		7, 5, 4,
		0, 4, 1,		1, 4, 5,
		2, 6, 4,		0, 2, 4,
	};


	// placi
	{
		nr_placi = 15;
		P[1].Oz = -8;
		P[2].Oz = -10;
		P[3].Oz = -4;


		// adaugam placile intr un vector de structuri
		for (int i = 1; i <= nr_placi; i++) {
			CubeColor = culori[rand() % 5];
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

			if (i == 2)
				CubeColor = culori[4];

			P[i].platforma = Platformele::CreateMesh("cube", vertices, indices);
			P[i].color = CubeColor;
			P[i].Oy = 0;

			if (i % 3 == 1)
				P[i].Ox = -4.5;
			else
				P[i].Ox = P[i - 1].Ox + 4.5f;

			if (i >= 4)
				P[i].Oz = P[i - 3].Oz - 23;

		}
	}
	
	//case = piramide + cuburi scalate 
	{
		nr_piramide = 30;
		vector<unsigned short> indices1 =
		{
			0, 1, 2,    0, 2, 3,
			0, 1, 4,    1, 2, 4,
			2, 3, 4,    0, 3, 4,

		};

		Piramide[1].Oz = -20;
		Piramide[2].Oz = -20;
		C[1].Oz = -20;
		C[2].Oz = -20;

		// adaugam placile intr un vector de structuri
		for (int i = 1; i <= nr_piramide; i++) {

			CubeColor = culori[rand() % 5];
			vector<VertexFormat> vertices1
			{
				VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 0, 0)),
				VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 0)),
				VertexFormat(glm::vec3(1,  -1,  -1), glm::vec3(1, 0, 0)),
				VertexFormat(glm::vec3(-1,  -1,  -1), glm::vec3(1, 0, 0)),
				VertexFormat(glm::vec3(0,  1,  0), glm::vec3(1, 0, 0)),
			};


			vector<VertexFormat> vertices
			{
				VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(1,  1, -1), glm::vec3(1, 0.7f, 0.2f)),
			};

			Piramide[i].piramida = Platformele::CreateMesh("piramide", vertices1, indices1);
			Piramide[i].color = glm::vec3(1, 0, 0);
			Piramide[i].Oy = 2.5f;

			C[i].cub = Platformele::CreateMesh("case", vertices, indices);
			C[i].color = glm::vec3(1, 0.7f, 0.2f);
			C[i].Oy = 1;

			if (i % 2 == 1) {
				Piramide[i].Ox = -9.5f;
				C[i].Ox = -9.5f;
			}
			else
			{
				Piramide[i].Ox = 9.5f;
				C[i].Ox = 9.5f;
			}

			if (i >= 3) {
				Piramide[i].Oz = Piramide[i - 2].Oz - 7;
				C[i].Oz = C[i - 2].Oz - 7;
			}
		}

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

	//numar limita obstacole
	k = 0;
	

}


void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds)
{

	// create piramida
	for(int i = 1; i <= nr_piramide; i++)
	{
		glm::mat4 m = glm::mat4(1);
		m = glm::translate(m, glm::vec3(Piramide[i].Ox, Piramide[i].Oy, Piramide[i].Oz));
		m = glm::scale(m, glm::vec3(1.5,0.75, 2));
		RenderMesh(Piramide[i].piramida, shaders["VertexColor"], m);

		glm::mat4 n = glm::mat4(1);
		n = glm::translate(n, glm::vec3(C[i].Ox, C[i].Oy, C[i].Oz));
		n = glm::scale(n, glm::vec3(1.5, 0.75, 2));
		RenderMesh(C[i].cub, shaders["VertexColor"], n);
	}

	// platforme generate la infinit
	GenerateHousesToInfinit();


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
	GeneratePlaciToInfinit();

	// miscare sfera
	playermove(deltaTimeSeconds);

	{

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(moveSphereOx, moveSphereOy, moveSphereOz));
		if(renderCameraTarget == false)
			RenderMesh(meshes["sphere"], shaders["ShaderTema2"], modelMatrix);

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

void Tema3::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}



void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4 & modelMatrix)
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


void Tema3::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
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




void Tema3::OnInputUpdate(float deltaTime, int mods)
{
		// translatam camera in fata cu aceeasi viteza
		// cu care translatam si mingea
		camera->TranslateForward(deltaTime * playerSpeed);

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
    
				}
			}

			if (renderCameraTarget == true) {
				if (camera->position[0] >= -5) {
					camera->TranslateRight(-deltaTime * 5);
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
				}


			}

			if (renderCameraTarget == true) {
				if (camera->position[0] <= 5) {
					camera->TranslateRight(deltaTime * 5);
				}

				if (moveSphereOx <= 5)
					moveSphereOx += deltaTime * 5;
			}
		}


}

void Tema3::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_C) {
		renderCameraTarget = !renderCameraTarget;

		if (renderCameraTarget) {
			camera->MoveForward(5);
		}
		else {
			camera->MoveForward(-5);
		}
		
	}

	if (key == GLFW_KEY_SPACE) {

		jumped = true;
		up = true;

	}
}

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
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

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

// functia de coliziune cu o placa
int Tema3::Intersect() {

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

// functia de coliziune cu o placa
bool Tema3::IntersectPlaci() {

	for (int i = 0; i < k; i++) {
		// 1.5 e jumate din latimea cubului
		float x = max((Obs[i].Ox - 1.2f), min(moveSphereOx, (Obs[i].Ox + 1.2f)));
		float y = max((Obs[i].Oy - Obs[i].save), min(moveSphereOy, (Obs[i].Oy + Obs[i].save)));
		float z = max((Obs[i].Oz - 0.2f), min(moveSphereOz, (Obs[i].Oz + 0.2f)));

		float distance = sqrt((x - moveSphereOx) * (x - moveSphereOx) +
			(y - moveSphereOy) * (y - moveSphereOy) +
			(z - moveSphereOz) * (z - moveSphereOz));

		if (distance < 0.5f)
			return true;
	}

	//1.2f, Obs[i].save, 0.2f

	return false;
}
// miscare jucator
void Tema3::playermove(float deltaTimeSeconds) {
	moveSphereOz -= playerSpeed * deltaTimeSeconds;

	if (jumped == true) {

		Jump(deltaTimeSeconds);
	}
}


void Tema3::Jump(float deltaTimeSeconds) {

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
			}

		}

	}

}


void Tema3::Land(float deltaTimeSeconds) {

	idx_placa = Intersect();
	obstacol_lovit = IntersectPlaci();

	if (obstacol_lovit == true)
		exit(0);


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

		P[idx_placa].platforma = Platformele::CreateMesh("cube", vertices, indices);
		
	}
}

// generam placile la infinit
void Tema3::GeneratePlaciToInfinit() {

	if (moveSphereOz <= limit_placi) {

		for (int t = cnt_placi; t <= cnt_placi + 2; t++) {

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

			vector<VertexFormat> vertices1
			{
				VertexFormat(glm::vec3(-1, -1,  1),glm::vec3(0,0,0)),
				VertexFormat(glm::vec3(1, -1,  1), glm::vec3(0,0,0)),
				VertexFormat(glm::vec3(-1,  1,  1), CubeColor),
				VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0,0,0)),
				VertexFormat(glm::vec3(-1, -1, -1), CubeColor),
				VertexFormat(glm::vec3(1, -1, -1), CubeColor),
				VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(0,0,0)),
				VertexFormat(glm::vec3(1,  1, -1), CubeColor),
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


			P[t].platforma = Platformele::CreateMesh("cube", vertices, indices);
			P[t].Oz -= 115;
			P[t].color = CubeColor;

			// cream obstacole si le generam
			if ((t % 10 == rand() % 10 || t % 10 == rand() % 10) && k <= 999999) {

				Obs[k].obstacol = Platformele::CreateMesh("obstacole", vertices1, indices);
				Obs[k].Ox = P[t].Ox;
				Obs[k].save = RandomFloat(0.3, 0.8);
				Obs[k].Oy = P[t].Oy + Obs[k].save;
				Obs[k].Oz = P[t].Oz - rand() % 9;
				Obs[k].color = CubeColor;
				k++;
			} 


		}

		cnt_placi = cnt_placi + 3;
		if (cnt_placi == 16)
			cnt_placi = 1;

		limit_placi = limit_placi - 23;
	}
	for (int i = 0; i < k; i++) {
		glm::mat4 n = glm::mat4(1);
		n = glm::translate(n, glm::vec3(Obs[i].Ox, Obs[i].Oy, Obs[i].Oz));
		n = glm::scale(n, glm::vec3(1.2f, Obs[i].save, 0.2f));
		RenderMesh(Obs[i].obstacol, shaders["VertexColor"], n);
	}


}

// generam casele la infinit
void Tema3::GenerateHousesToInfinit() {

	if (moveSphereOz <= limit_case) {

		for (int t1 = cnt_case; t1 <= cnt_case + 1; t1++) {

			vector<unsigned short> indices1 =
			{
				0, 1, 2,    0, 2, 3,
				0, 1, 4,    1, 2, 4,
				2, 3, 4,    0, 3, 4,

			};


			vector<unsigned short> indices =
			{
				0, 1, 2,		1, 3, 2,
				2, 3, 7,		2, 7, 6,
				1, 7, 3,		1, 5, 7,
				6, 7, 4,		7, 5, 4,
				0, 4, 1,		1, 4, 5,
				2, 6, 4,		0, 2, 4,
			};

			vector<VertexFormat> vertices1
			{
				VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 0, 0)),
				VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 0)),
				VertexFormat(glm::vec3(1,  -1,  -1), glm::vec3(1, 0, 0)),
				VertexFormat(glm::vec3(-1,  -1,  -1), glm::vec3(1, 0, 0)),
				VertexFormat(glm::vec3(0,  1,  0), glm::vec3(1, 0, 0)),
			};

			vector<VertexFormat> vertices
			{
				VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 0.7f, 0.2f)),
				VertexFormat(glm::vec3(1,  1, -1), glm::vec3(1, 0.7f, 0.2f)),
			};

			Piramide[t1].piramida = Platformele::CreateMesh("piramide", vertices1, indices1);
			Piramide[t1].Oz -= 105;
			Piramide[t1].color = glm::vec3(1, 0, 0);

			C[t1].cub = Platformele::CreateMesh("case", vertices, indices);
			C[t1].Oz -= 105;
			C[t1].color = glm::vec3(1, 0.7f, 0.2f);

		}

		cnt_case = cnt_case + 2;
		if (cnt_case == 31)
			cnt_case = 1;

		limit_case = limit_case - 7;


	}
}

void Tema3::CheckColour() {

	//rosu
	//jocul se termina instant
	if (P[idx_placa].color == culori[0]) {
		exit(0);
	}

	//galben
	//pierdem o parte din combustibil
	if (P[idx_placa].color == culori[1]) {
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
		P[idx_placa].color = culori[5];
		return;
	}

}

void Tema3::Set() {
	aux = moveSphereOz;
	playerSpeed = 20;
	speedSet = true;
	return;
}



