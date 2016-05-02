#include "WorldRenderer.h"
#include <vector>
#include <iostream>
#include "glm\glm.hpp"

std::vector<std::vector<glm::vec3>> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;

int getMesh(char* inputFile, std::vector<std::vector<glm::vec3>> & out_vertices, std::vector < glm::vec2 > & out_uvs, std::vector < glm::vec3 > & out_normals){
	std::cout << "Attempting to load file as model " << inputFile << "\n";

	std::vector<std::vector<unsigned int>> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE * file = fopen("heli.obj", "r");
	if (file == NULL){
		std::cout << "Impossible to open the file !\n";
		return 0;
	}
	while (1){
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "v") == 0){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0){
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9){
				std::cout << "File can't be read by the parser : ( Try exporting with other options )\n";
				return 0;
			}

			std::vector<unsigned int> vertexTriangle;
			vertexTriangle.push_back(vertexIndex[0]);
			vertexTriangle.push_back(vertexIndex[1]);
			vertexTriangle.push_back(vertexIndex[2]);
			vertexIndices.push_back(vertexTriangle);

			//uvIndices    .push_back(uvIndex[0]);
			//uvIndices    .push_back(uvIndex[1]);
			//uvIndices    .push_back(uvIndex[2]);

			//std::vector<unsigned int> normalTriangle;
			//normalTriangle.push_back(normalIndex[0]);
			//normalTriangle.push_back(normalIndex[1]);
			//normalTriangle.push_back(normalIndex[2]);
			//normalIndices.push_back(normalTriangle);
		}
	}
	for (unsigned int i = 0; i<vertexIndices.size(); i++){
		std::vector<unsigned int> vertexIndexs = vertexIndices[i];

		//glm::vec3 vertex0 = temp_vertices[ vertexIndexs[3]-1 ];
		glm::vec3 vertex1 = temp_vertices[vertexIndexs[0] - 1];
		glm::vec3 vertex2 = temp_vertices[vertexIndexs[1] - 1];
		glm::vec3 vertex3 = temp_vertices[vertexIndexs[2] - 1];
		std::vector<glm::vec3> vertex;
		vertex.push_back(vertex1); vertex.push_back(vertex2); vertex.push_back(vertex3);
		out_vertices.push_back(vertex);

	}
	return 1;
}

WorldRenderer::WorldRenderer()
{
	this->modelLoader = new ModelLoader();

	//getMesh("heli.obj", vertices, uvs, normals);
}


WorldRenderer::~WorldRenderer()
{
}


void WorldRenderer::RenderWorld(World * world) 
{
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int i = 0; i < this->modelLoader->models->size(); ++i)
	{
		for (int j = 0; j < this->modelLoader->models->at(i)->models->size(); ++j)
		{
			Model * model = this->modelLoader->models->at(i)->models->at(j);
			this->RenderModel(model->tri_count, model->v);
		}
	}


	
	
	/*
	glPushMatrix();
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.5f, 1.0f);
	glScalef(0.05f, 0.05f, 0.05f);
	glTranslatef(5, 0, 0);

	for (unsigned i = 0; i < vertices.size(); i++) {
		std::vector<glm::vec3> vertexGroup = vertices[i];
		glPushMatrix();
		glBegin(GL_TRIANGLES);
		glVertex3f(vertexGroup[0].x, vertexGroup[0].y, vertexGroup[0].z);
		glVertex3f(vertexGroup[1].x, vertexGroup[1].y, vertexGroup[1].z);
		glVertex3f(vertexGroup[2].x, vertexGroup[2].y, vertexGroup[2].z);
		glEnd();
		glPopMatrix();
	}

	glPopMatrix();
	*/
}

void WorldRenderer::RenderModel(int v_count, float * arr)
{
	glPushMatrix();
	glColor3f(0.0f, 0.5f, 1.0f);
	glScalef(0.05f, 0.05f, 0.05f);
	glTranslatef(2, 0, 0);
	//glRotatef(10,0,3,0);
	//glPushMatrix();
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_TRIANGLES, 0, arr);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glPopMatrix();
	
	for (unsigned i = 0; i < v_count; i++) {
		int stt = i * 9;
		glPushMatrix();
		//glEnableClientState(GL_VERTEX_ARRAY);
		//printf("print %i A; %f - %f - %f \n", i, arr[stt + 0], arr[stt + 1], arr[stt + 2]);
		//printf("print %i B; %f - %f - %f \n", i, arr[stt + 3], arr[stt + 4], arr[stt + 5]);
		//printf("print %i C; %f - %f - %f \n", i, arr[stt + 6], arr[stt + 7], arr[stt + 8]);
		//glDrawArrays();

		//glEnableClientState(GL_VERTEX_ARRAY);
		//glVertexPointer(sizeof(float), GL_TRIANGLES, 0, arr);
		//glDrawArrays(GL_TRIANGLES, 0, v_count);
		//glDisableClientState(GL_VERTEX_ARRAY);

		glBegin(GL_TRIANGLES);
		glVertex3f(arr[stt + 0], arr[stt + 1], arr[stt + 2]);
		glVertex3f(arr[stt + 3], arr[stt + 4], arr[stt + 5]);
		glVertex3f(arr[stt + 6], arr[stt + 7], arr[stt + 8]);
		glEnd();
		glPopMatrix();
	}
	
	glPopMatrix();
}
