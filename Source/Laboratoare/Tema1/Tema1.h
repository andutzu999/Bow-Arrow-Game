#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <vector>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;



protected:
	glm::mat3 modelMatrix1, modelMatrix2, modelMatrix3, modelMatrix;
	float scaleX, scaleY;
	float tXarc, tYarc ,value, Xvf, Yvf;
	float angularStepMouse;
	float scX, scY;
	int ok;
	int speed;
	float tXsg;
	float tYsg;
	float aux1, aux2;
	int stop;
	int numar_vieti;
	float arcSide;
	int ok1;
	float pX, pY;
	int l;
	int score;
	

	struct baloane {

		char name[50];
		glm::vec3 corner;
		float balloonSide;
		glm::vec3 color;
		float Ox;
		float Oy;
		float scaleX;
		float scaleY;
	};

	struct shuriken {

		char name[50];
		glm::vec3 corner;
		float shurikenSide;
		glm::vec3 color;
		float Ox;
		float Oy;
		float scaleX;
		float scaleY;
		float angularStep;
		int ok1;

	};

	struct baloane B[50];
	struct shuriken S[50];

	void VarfSageata(float tXarc, float tYarc, float& Xvf, float& Yvf, float angularStepMouse);
	int Intersect(float Xvf, float Yvf, float translateX, float translateY, float radius);
	int Intersect1(float tXarc, float tYarc, float translateX, float translateY, float shurikenSide, float arcSide, int ok1);
};