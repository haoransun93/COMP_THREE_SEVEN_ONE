#include "ModelLoader.h"

ModelLoader::ModelLoader()
{
	this->models = new std::vector<ModelRoot *>();
	this->LoadModel("Models/knight.obj");	

	for (int i = 0; i < this->models->size(); ++i)
	{
		for (int j = 0; j < this->models->at(i)->models->size(); ++j)
		{
			this->models->at(i)->models->at(j)->PostProcess();
		}
	}
}

ModelLoader::~ModelLoader()
{

}

void ModelLoader::LoadModel(char * inputFile)
{
	ModelRoot * modelRoot = new ModelRoot();

	std::cout << "Attempting to load file as model " << inputFile << "\n";
	FILE * file = fopen(inputFile, "r");
	if (file == NULL){
		std::cout << "Impossible to open the file !\n";
		return;
	}	

	char * title;
	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);

		if (lineHeader[0] == 'm' &&
			lineHeader[1] == 't' &&
			lineHeader[2] == 'l' &&
			lineHeader[3] == 'l' &&
			lineHeader[4] == 'i' &&
			lineHeader[5] == 'b')
		{
			std::string mtl_file(lineHeader);

			//load mtl and also texture;		
		}
		else if (lineHeader[0] == 'o')
		{
			title = lineHeader;
			break;
		}
	}

	int offset_v = 1;
	int offset_vt = 1;
	int offset_vn = 1;

	while (1){
		Model * model = new Model();

		int * finished = new int();
		*finished = 0;

		char * temp = LoadModelComponent(file, model, finished, offset_v, offset_vt, offset_vn);
		if (*finished == 0)
		{
			model->component = temp;
			modelRoot->models->push_back(model);
		}
		else 
		{
			model->component = temp;
			modelRoot->models->push_back(model);
			break;
		}
	}

	this->models->push_back(modelRoot);
}

char * ModelLoader::LoadModelComponent(FILE * file, Model * model, int * finished, int & offset_v, int & offset_vt, int & offset_vn)
{
	model->offset_v = offset_v;
	model->offset_vt = offset_vt;
	model->offset_vn = offset_vn;
	model->normals = new std::vector<glm::vec3>();
	model->uvs = new std::vector <glm::vec2>();
	model->vertices = new std::vector<glm::vec3>();

	model->face_v = new std::vector<glm::ivec3>();
	model->face_vn = new std::vector <glm::ivec3>();
	model->face_vt = new std::vector<glm::ivec3>();

	char * lineTitle = new char[128];
	char * title;
	int i = 0;
	while (1)
	{
		i++;
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);

		if (res == EOF)
		{
			*finished = 1;
			break;
		}
		if (i == 1)
		{
			memcpy(lineTitle, lineHeader, sizeof(char) * 128);
		}
		//title
		else if (lineHeader[0] == 'o' && lineHeader[1] != 'f')
		{
			break;
		}
		//vertex
		else if (lineHeader[0] == 'v' && lineHeader[1] != 't' && lineHeader[1] != 'n'){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			model->vertices->push_back(vertex);
			offset_v++;
		}
		//texture vt
		else if (lineHeader[0] == 'v' && lineHeader[1] == 't'){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			model->uvs->push_back(uv);
			offset_vt++;
		}
		//normals
		else if (lineHeader[0] == 'v' && lineHeader[1] == 'n'){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			model->normals->push_back(normal);
			offset_vn++;
		}
		//face
		else if (lineHeader[0] == 'f')
		{
			glm::ivec3 v, vt, vn;
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &v.x, &vt.x, &vn.x, &v.y, &vt.y, &vn.y, &v.z, &vt.z, &vn.z);
			if (matches != 9){
				std::cout << "File can't be read by the parser : ( Try exporting with other options )\n";
				break;
			}

			model->face_v->push_back(v);
			model->face_vt->push_back(vt);
			model->face_vn->push_back(vn);
		}
		//s off
		else if (lineHeader[0] == 's')
		{
			int x = 0;
		}
		else 
		{
		
		}
	}
	/*
	for (unsigned int i = 0; i<vertexIndices.size(); i++)
	{
		std::vector<unsigned int> vertexIndexs = vertexIndices[i];

		//glm::vec3 vertex0 = temp_vertices[ vertexIndexs[3]-1 ];
		glm::vec3 vertex1 = temp_vertices[vertexIndexs[0] - 1];
		glm::vec3 vertex2 = temp_vertices[vertexIndexs[1] - 1];
		glm::vec3 vertex3 = temp_vertices[vertexIndexs[2] - 1];
		std::vector<glm::vec3> vertex;
		vertex.push_back(vertex1); vertex.push_back(vertex2); vertex.push_back(vertex3);
		out_vertices.push_back(vertex);
	}*/

	model->tri_count = model->face_v->size();

	return lineTitle;
	
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

int ModelLoader::LoadTexture(const char * imagepath){

	unsigned char header[124];

	FILE *fp;

	// try to open the file
	fp = fopen(imagepath, "rb");
	if (fp == NULL){
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
		return 0;
	}

	// verify the type of file
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		return 0;
	}

	// get the surface desc
	fread(&header, 124, 1, fp);

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);


	unsigned char * buffer;
	unsigned int bufsize;
	// how big is it going to be including all mipmaps?
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);

	//close the file pointer
	fclose(fp);

	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	// load the mipmaps
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if (width < 1) width = 1;
		if (height < 1) height = 1;

	}

	free(buffer);

	return textureID;
}
