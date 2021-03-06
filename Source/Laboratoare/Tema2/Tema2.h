#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "Camera.h"
#include "Platforme.h"
#include <vector>

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;
	bool isortho;
	float fov, x, y;
	
	

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;
	void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	Vizualizare::Camera *camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
	Mesh * platforma;
	Mesh * dreptunghi_alb;
	Mesh * dreptunghi_rosu;


	struct platforme {

		glm::vec3 color;
		float Ox;
		float Oy;
		float Oz;
		Mesh * platforma;
	};

	struct platforme P[50];
	glm::vec3 CubeColor;
	int nr_placi;
	int cnt;
	int limit;


	float playerSpeed;
	int ok;
	int idx_placa;

	glm::vec3 culori[6];


	int Intersect();
	void playermove(float deltaTimeSeconds);
	void Jump(float deltaTimeSeconds);
	void Land(float deltaTimeSeconds);
	void GenerateToInfinit();
	void CheckColour();
	void Set();

	bool jumped;
	bool up;
	float moveSphereOz, moveSphereOx, moveSphereOy;
	float albOx, albOy, albOz;
	float rosuOx, rosuOy, rosuOz;
	float scaleOx;
	bool blocked;
	int times;
	float aux;
	bool speedSet;
};