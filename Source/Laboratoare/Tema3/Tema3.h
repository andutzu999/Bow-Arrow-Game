#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "Camera_1.h"
#include "Platformele.h"
#include <vector>

class Tema3 : public SimpleScene
{
public:
	Tema3();
	~Tema3();

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
	Vizualizare::Camera_1 *camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;


	Mesh * platforma;
	Mesh * dreptunghi_alb;
	Mesh * dreptunghi_rosu;
	Mesh * piramide;
	Mesh * obstacol;

	// structura platforme
	struct platforme {

		glm::vec3 color;
		float Ox;
		float Oy;
		float Oz;
		Mesh * platforma;
	};

	struct platforme P[50];

	// structura piramide
	struct piramide {

		glm::vec3 color;
		float Ox;
		float Oy;
		float Oz;
		Mesh * piramida;
	};

	struct piramide Piramide[50];

	// structura piramide
	struct cuburi {

		glm::vec3 color;
		float Ox;
		float Oy;
		float Oz;
		Mesh * cub;
	};

	struct cuburi C[50];



	// structura piramide
	struct obstacole {

		glm::vec3 color;
		float Ox;
		float Oy;
		float Oz;
		float save;
		Mesh * obstacol;
	};

	struct obstacole Obs[1000000];
	int k;
	bool obstacol_lovit;
	

	glm::vec3 CubeColor;
	int nr_placi;
	int nr_piramide;
	int cnt_placi;
	int cnt_case;
	int limit_placi;
	int limit_case;


	float playerSpeed;
	int ok;
	int idx_placa;

	glm::vec3 culori[6];


	int Intersect();
	bool IntersectPlaci();
	void playermove(float deltaTimeSeconds);
	void Jump(float deltaTimeSeconds);
	void Land(float deltaTimeSeconds);
	void GeneratePlaciToInfinit();
	void GenerateHousesToInfinit();
	void CheckColour();
	void Set();

	bool jumped;
	bool up;
	float moveSphereOz, moveSphereOx, moveSphereOy;
	float scaleOx;
	bool blocked;
	int times;
	float aux;
	bool speedSet;
};