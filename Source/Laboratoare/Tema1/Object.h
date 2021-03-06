#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateBalloon(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateViata(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateSageata(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateArc(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
	Mesh* CreateDreptunghi(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);


}
