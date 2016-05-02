#include "Model.h"


Model::Model()
{
}


Model::~Model()
{
}


void Model::PostProcess()
{
	this->v = new float[this->tri_count * 9];
	this->vt = new float[this->tri_count * 9];
	this->vn = new float[this->tri_count * 9];

	for (int i = 0; i < this->tri_count; ++i)
	{
		int stt = i * 9;

		glm::vec3 * tri;
		glm::vec2 * two;

		//vertex

		printf("print %i ; %i - %i - %i \n", i, this->face_v->at(i).x, this->face_v->at(i).y, this->face_v->at(i).z);

		tri = &this->vertices->at(this->face_v->at(i).x - this->offset_v);
		this->v[stt + 0] = tri->x;
		this->v[stt + 1] = tri->y;
		this->v[stt + 2] = tri->z;
		printf("print %i A; %f - %f - %f \n", i, this->v[stt + 0], this->v[stt + 1], this->v[stt + 2]);

		tri = &this->vertices->at(this->face_v->at(i).y - this->offset_v);
		this->v[stt + 3] = tri->x;
		this->v[stt + 4] = tri->y;
		this->v[stt + 5] = tri->z;
		printf("print %i B; %f - %f - %f \n", i, this->v[stt + 3], this->v[stt + 4], this->v[stt + 5]);

		tri = &this->vertices->at(this->face_v->at(i).z - this->offset_v);
		this->v[stt + 6] = tri->x;
		this->v[stt + 7] = tri->y;
		this->v[stt + 8] = tri->z;
		printf("print %i C; %f - %f - %f \n", i, this->v[stt + 6], this->v[stt + 7], this->v[stt + 8]);
		/*
		//texture
		two = &this->uvs->at(this->face_vt->at(i).x - this->offset_vt);
		this->vt[stt + 0] = tri->x;
		this->vt[stt + 1] = tri->y;
		this->vt[stt + 2] = 0.0f;

		two = &this->uvs->at(this->face_vt->at(i).y - this->offset_vt);
		this->vt[stt + 3] = tri->x;
		this->vt[stt + 4] = tri->y;
		this->vt[stt + 5] = 0.0f;

		two = &this->uvs->at(this->face_vt->at(i).z - this->offset_vt);
		this->vt[stt + 6] = tri->x;
		this->vt[stt + 7] = tri->y;
		this->vt[stt + 8] = 0.0f;

		//normal
		tri = &this->normals->at(this->face_vn->at(i).x - this->offset_vn);
		this->vn[stt + 0] = tri->x;
		this->vn[stt + 1] = tri->y;
		this->vn[stt + 2] = tri->z;

		tri = &this->normals->at(this->face_vn->at(i).y - this->offset_vn);
		this->vn[stt + 3] = tri->x;
		this->vn[stt + 4] = tri->y;
		this->vn[stt + 5] = tri->z;

		tri = &this->normals->at(this->face_vn->at(i).z - this->offset_vn);
		this->vn[stt + 6] = tri->x;
		this->vn[stt + 7] = tri->y;
		this->vn[stt + 8] = tri->z;
		*/
	}
}