#include "Tema1.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <string>

#include <Core/Engine.h>
#include "Transform.h"
#include "Object.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);


	// Sides
	float shurikenSide = 30;
	float balloonSide = 25;
	float sageataSide = 5;
	arcSide = 50;
	float powerBarSide = 15;

	// Miscare arc

	tXsg = 50;
	tYsg = 360;
	tXarc = 50;
	tYarc = 360;
	value = 200;



	// rotire arc si sageata
	angularStepMouse = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	//scale Power Bar
	scX = 1;
	scY = 1;
	int ok = 0;
	int speed;

	//numar vieti
	numar_vieti = 3;

	//scale Score Bar;
	pX = 1;
	pY = 1;


	//----------------------------------------------------baloane------------------------------------------------------

	stop = 0;
	int x = 250;
	int y = -100;
	int i = 0;
	Mesh* balloon1 = Object::CreateBalloon("balloon1", corner, balloonSide, glm::vec3(0.87,0.07,0.01), true);  // red
	AddMeshToList(balloon1);

	Mesh* balloon2 = Object::CreateBalloon("balloon2", corner, balloonSide, glm::vec3(0.89,0.94,0.01), true);  //yellow
	AddMeshToList(balloon2);

	Mesh* balloon3 = Object::CreateBalloon("balloon3", corner, balloonSide, glm::vec3(0.87, 0.07, 0.01), true);  //red
	AddMeshToList(balloon3);

	Mesh* balloon4 = Object::CreateBalloon("balloon4", corner, balloonSide, glm::vec3(0.89, 0.94, 0.01), true);  //yellow
	AddMeshToList(balloon4);

	Mesh* balloon5 = Object::CreateBalloon("balloon5", corner, balloonSide, glm::vec3(0.87, 0.07, 0.01), true);  //red
	AddMeshToList(balloon5);

	// add balloons to struct
	for (int i = 1; i <= 5; i++) {
		int n = sprintf(B[i].name, "balloon%d", i);

		if(i % 2 == 1)
			B[i].color = glm::vec3(0.87, 0.07, 0.01);  // red
		else {
			B[i].color = glm::vec3(0.89, 0.94, 0.01); //yellow
		}

		B[i].balloonSide = balloonSide;
		B[i].corner = corner;
		B[i].Ox = x;
		B[i].Oy  = y;
		B[i].scaleX = 1;
		B[i].scaleY = 1.5;
		x = x + 170;
		y = y - 100;

	}

	//-----------------------------------------------shuriken--------------------------------------------------------

	int x1 = 1400;
	int y1 = 600;
		// shuriken-uri
	Mesh* shuriken1 = Object::CreateShuriken("shuriken1", corner, shurikenSide, glm::vec3(0.81, 0.68, 0.1), true);
	AddMeshToList(shuriken1);

	Mesh* shuriken2 = Object::CreateShuriken("shuriken2", corner, shurikenSide, glm::vec3(0.81, 0.68, 0.1), true);
	AddMeshToList(shuriken2);

	Mesh* shuriken3 = Object::CreateShuriken("shuriken3", corner, shurikenSide, glm::vec3(0.81, 0.68, 0.1), true);
	AddMeshToList(shuriken3);

	//add shuriken to struct
	for (int i = 1; i <= 3;i++) {
		int n = sprintf(S[i].name, "shuriken%d", i);
		S[i].corner = corner;
		S[i].shurikenSide = shurikenSide;
		S[i].Ox = x1;
		S[i].Oy = y1;
		x1 = x1 + 200;
		y1= y1 - 100;
		S[i].scaleX = 1;
		S[i].scaleY = 1;
		S[i].ok1 = 0;

	}


	//-------------------------------------------- arc si sageata----------------------------------------------------
	Mesh* sageata = Object::CreateSageata("sageata", corner, sageataSide, glm::vec3(0.01, 0.92, 0.94), true);
	AddMeshToList(sageata);

	Mesh* arc = Object::CreateArc("arc", corner, arcSide, glm::vec3(0.01, 0.92, 0.94));
	AddMeshToList(arc);

	Mesh* powerbar = Object::CreateDreptunghi("powerbar", corner, powerBarSide, glm::vec3(0.01, 0.92, 0.94));
	AddMeshToList(powerbar);

	Mesh* scorebar = Object::CreateDreptunghi("scorebar", corner, powerBarSide, glm::vec3(0.01, 0.92, 0.94));
	AddMeshToList(scorebar);

	//----------------------------------------------numar vieti------------------------------------------------------
	Mesh* viata1 = Object::CreateViata("viata1", corner, balloonSide*0.6, glm::vec3(0.87, 0.07, 0.01), true);  // red
	AddMeshToList(viata1);

	Mesh* viata2 = Object::CreateViata("viata2", corner, balloonSide*0.6, glm::vec3(0.87, 0.07, 0.01), true);  // red
	AddMeshToList(viata2);

	Mesh* viata3 = Object::CreateViata("viata3", corner, balloonSide*0.6, glm::vec3(0.87, 0.07, 0.01), true);  //red
	AddMeshToList(viata3);
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	
	// TODO: update steps for translation, rotation, scale, in order to create animations

	// baloane
	int y = -200;
	for (int i = 1; i <= 5; i++) {

		modelMatrix = glm::mat3(1);
		if (Intersect(Xvf, Yvf, B[i].Ox, B[i].Oy, (B[i].balloonSide * 1.5)) == 1 && stop == 0) {

			B[i].scaleX -= 1.0f * deltaTimeSeconds * 0.1;
			B[i].scaleY -= 1.0f * deltaTimeSeconds * 0.1;
			B[i].Oy = y;
			B[i].scaleX += 1.0f * deltaTimeSeconds * 0.1;
			B[i].scaleY += 1.0f * deltaTimeSeconds * 0.1;

			if (B[i].color == glm::vec3(0.87, 0.07, 0.01)) {
				score = score + 100;
				cout << "Am nimerit un balon rosu, score-ul este: " << " " << score << endl;
			}
			else {
				score = score - 50;
				cout << "Am nimerit un balon galben, score-ul este: " << " " << score << endl;
			}
		}

		B[i].Oy += deltaTimeSeconds * 50;
		modelMatrix *= Transform::Translate(B[i].Ox, B[i].Oy);
		modelMatrix *= Transform::Scale(B[i].scaleX, B[i].scaleY);
		RenderMesh2D(meshes[B[i].name], shaders["VertexColor"], modelMatrix);
		if (B[i].Oy > 740)
			B[i].Oy = y - 200;

		y = y - 200;

	}

	// shuriken
	int x = 1200;
	for (int i = 1; i <= 3; i++) {

		modelMatrix = glm::mat3(1);
		if (Intersect(Xvf, Yvf, S[i].Ox, S[i].Oy, S[i].shurikenSide) == 1 && stop == 0 && tXsg != tXarc) {

			S[i].scaleX -= 1.0f * deltaTimeSeconds * 0.1;
			S[i].scaleY -= 1.0f * deltaTimeSeconds * 0.1;
			S[i].Ox = x;
			S[i].scaleX += 1.0f * deltaTimeSeconds * 0.1;
			S[i].scaleY += 1.0f * deltaTimeSeconds * 0.1;
			stop = 1;

			score = score + 100;
			cout << "Am nimerit un shuriken, score-ul este: " << " " << score << endl;
		}

		if (Intersect1(tXarc, tYarc, S[i].Ox, S[i].Oy, S[i].shurikenSide, arcSide, S[i].ok1) == 1) {
			numar_vieti--;
			S[i].ok1 = 1;
		}


		S[i].Ox -= deltaTimeSeconds * 200;
		modelMatrix *= Transform::Translate(S[i].Ox, S[i].Oy);
		S[i].angularStep += 8 * deltaTimeSeconds;
		modelMatrix *= Transform::Rotate(S[i].angularStep);
		modelMatrix *= Transform::Scale(S[i].scaleX, S[i].scaleY);
		RenderMesh2D(meshes[S[i].name], shaders["VertexColor"], modelMatrix);
		if (S[i].Ox < 0) {
			S[i].Ox = x;
			S[i].ok1 = 0;
		}

		x = x + 200;
	}



	// coordonatele varfului sagetii
	VarfSageata(tXsg, tYsg,  Xvf, Yvf, angularStepMouse);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform::Translate(tXsg, tYsg);
	modelMatrix *= Transform::Rotate(angularStepMouse);
	RenderMesh2D(meshes["sageata"], shaders["VertexColor"], modelMatrix);


	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform::Translate(tXarc, tYarc);
	modelMatrix *= Transform::Rotate(angularStepMouse);
	RenderMesh2D(meshes["arc"], shaders["VertexColor"], modelMatrix);


	//powerbar
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform::Translate(10, 10);
	modelMatrix *= Transform::Scale(scX, scY);
	RenderMesh2D(meshes["powerbar"], shaders["VertexColor"], modelMatrix);


	//viata3
	modelMatrix1 = glm::mat3(1);
	modelMatrix1 *= Transform::Translate(1080, 680);
	if(numar_vieti >= 3)
	RenderMesh2D(meshes["viata3"], shaders["VertexColor"], modelMatrix1);

	//viata2
	modelMatrix2 = glm::mat3(1);
	modelMatrix2 *= Transform::Translate(1120, 680);
	if (numar_vieti >= 2)
	RenderMesh2D(meshes["viata2"], shaders["VertexColor"], modelMatrix2);

	modelMatrix3 = glm::mat3(1);
	modelMatrix3 *= Transform::Translate(1160, 680);
	if (numar_vieti >= 1)
	RenderMesh2D(meshes["viata1"], shaders["VertexColor"], modelMatrix3);

	if (numar_vieti == 0)
		exit(0);



}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

	if (window->KeyHold(GLFW_KEY_W)) {
		tYarc += value * deltaTime;
		if(ok != 1)
			tYsg += value * deltaTime;

		if (tYarc >= 600 && tYsg >= 600) {
			tYarc = 600;
			tYsg = 600;
		}

		VarfSageata(tXsg, tYsg, Xvf, Yvf, angularStepMouse);
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		tYarc -= value * deltaTime;
		if (ok != 1)
			tYsg -= value * deltaTime;

		if (tYarc <= 100 && tYsg <= 100) {
			tYarc = 100;
			tYsg = 100;
		}

		VarfSageata(tXsg, tYsg, Xvf, Yvf, angularStepMouse);
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && scX < 700) {
			scX += 1000 * deltaTime;
			ok = 1;
			speed = scX / 5;
			stop = 0;
			l = 0;
	}

	else if (ok == 1 && !window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)){

		tYsg += 20 *deltaTime * speed * tan(angularStepMouse);
		tXsg += 20 * deltaTime * speed;
		scX = 1;

		if (tXsg > 1500) {
			tXsg = tXarc;
			tYsg = tYarc;
			ok = 0;
		}
	}


}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	angularStepMouse = -atan((mouseY - tYarc) / (mouseX - tXarc));

	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

void Tema1::VarfSageata(float tXsg, float tYsg, float& Xvf, float& Yvf, float angularStepMouse) {

	float e = tXsg + 2.5 * sin(angularStepMouse);
	float f = tYsg + 2.5 * cos(angularStepMouse);

	Xvf = e + 100 * cos(angularStepMouse);
	Yvf = f + 100 * sin(angularStepMouse);

}

int Tema1:: Intersect(float Xvf, float Yvf, float translateX, float translateY, float radius) {
	
	float distance = sqrt((Xvf - translateX) * (Xvf - translateX) +
		(Yvf - translateY) * (Yvf - translateY));


	if (distance < radius) {
			return 1;
		} else {

		return 0;
	}

}

int Tema1::Intersect1(float tXarc, float tYarc, float translateX, float translateY, float shurikenSide, float arcSide, int ok1) {

	float distance = sqrt((tXarc - translateX) * (tXarc - translateX) +
		(tYarc - translateY) * (tYarc - translateY));

	if (distance < shurikenSide + arcSide && ok1 == 0) {
		return 1;

	}
	else {
		return 0;
	}
}
