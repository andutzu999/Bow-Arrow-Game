#include "Object.h"

#include <Core/Engine.h>

Mesh* Object::CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(-length, length, 0), color),
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(-length, 0, 0), color),
		VertexFormat(corner + glm::vec3(-length, -length, 0), color),
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, -length, 0), color),
		VertexFormat(corner + glm::vec3(0, -length, 0), color),

	};

	Mesh* shuriken = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

	if (!fill) {
		shuriken->SetDrawMode(GL_TRIANGLE_FAN);
	}


	shuriken->InitFromData(vertices, indices);
	return shuriken;
}

Mesh* Object::CreateBalloon(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices;

	int segments = 40;

	for (int i = 0; i < segments; i++) {

		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		vertices.emplace_back(VertexFormat(corner + glm::vec3(length * cos(theta), length * sin(theta), 0), color));

	}

	Mesh* balloon = new Mesh(name);
	std::vector<unsigned short> indices;

	vertices.emplace_back(VertexFormat(corner + glm::vec3(0, -length, 0), color));
	vertices.emplace_back(VertexFormat(corner + glm::vec3(-2, -length - 15, 0), color));
	vertices.emplace_back(VertexFormat(corner + glm::vec3(2, -length - 15, 0), color));

	for (int j = 0; j < segments; j++)
		indices.emplace_back(j);

	indices.emplace_back(segments);
	indices.emplace_back(segments +1 );
	indices.emplace_back(segments + 2);


	balloon->SetDrawMode(GL_TRIANGLE_FAN);
	balloon->InitFromData(vertices, indices);
	return balloon;
}

Mesh* Object::CreateSageata(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color), //0
		VertexFormat(corner + glm::vec3(length * 15, 0, 0), color), //1
		VertexFormat(corner + glm::vec3(0, length, 0), color),                  //6

		VertexFormat(corner + glm::vec3(length * 15, -(length * 3), 0), color),  //2
		// coordonatele varfului sagetii
		VertexFormat(corner + glm::vec3(length * 20, (length / 2), 0), color),  //3
		VertexFormat(corner + glm::vec3(length * 15, (length * 4), 0), color),  //4

				VertexFormat(corner + glm::vec3(length * 15, 0, 0), color), //1
		VertexFormat(corner + glm::vec3(length * 15, length, 0), color),        //5
		VertexFormat(corner + glm::vec3(0, length, 0), color),                  //6

	
	};
	Mesh* sageata = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
	sageata->SetDrawMode(GL_TRIANGLES);
	sageata->InitFromData(vertices, indices);
	return sageata;
}

Mesh* Object::CreateArc(std::string name, glm::vec3 leftBottomCorner, float radius, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	float twoPI = 2 * 3.1415926f;
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	
	vertices.emplace_back(VertexFormat(corner + glm::vec3(0, radius, 0), color));
	vertices.emplace_back(VertexFormat(corner, color));
	vertices.emplace_back(VertexFormat(corner + glm::vec3(0, -radius, 0), color));
	indices.emplace_back(0);
	indices.emplace_back(1);
	indices.emplace_back(2);
	int j = 3;

	for (float i = 0.0; i <= 3.14; i += 0.01) {
		vertices.emplace_back(VertexFormat(corner + glm::vec3(sin(i)*radius, cos(i)*radius, 0), color));
		indices.emplace_back(j);
		j++;
	}

	Mesh* arc = new Mesh(name);
	arc->SetDrawMode(GL_LINE_STRIP);
	arc->InitFromData(vertices, indices);
	return arc;

}

Mesh* Object::CreateDreptunghi(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),  //0
		VertexFormat(corner + glm::vec3(0.1, 0, 0), color),  //1
		VertexFormat(corner + glm::vec3(0.1, length, 0), color),  //2

		VertexFormat(corner, color), //0
		VertexFormat(corner + glm::vec3(0.1, length, 0), color),  //2
		VertexFormat(corner + glm::vec3(0, length, 0), color), //3
		
	};

	Mesh* power_bar = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5};

		power_bar->SetDrawMode(GL_TRIANGLES);


	power_bar->InitFromData(vertices, indices);
	return power_bar;
	

}


Mesh* Object::CreateViata(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices;

	int segments = 40;

	for (int i = 0; i < segments; i++) {

		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		vertices.emplace_back(VertexFormat(corner + glm::vec3(length * cos(theta), length * sin(theta), 0), color));

	}

	Mesh* balloon = new Mesh(name);
	std::vector<unsigned short> indices;


	for (int j = 0; j < segments; j++)
		indices.emplace_back(j);



	balloon->SetDrawMode(GL_TRIANGLE_FAN);
	balloon->InitFromData(vertices, indices);
	return balloon;
}





