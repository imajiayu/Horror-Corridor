#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "../include/shader_m.h"
#include "../include/model.h"
#include "../include/parameter.h"
#include "../include/Role.h"
#include"../include/Object.h"

enum corridorType //��������
{
	straightCorridor,
	cornerCorridorL,
	cornerCorridorR,
	stairsCorridorU,
	stairsCorridorD
};

enum corridorDir //����
{
	xP,
	zP,
	xN,
	zN
};

const int STAIRS_NUM = 20;

// debug
const char *const corrider_typename[] = {
	"straight",
	"cornerL",
	"cornerR",
	"stairsU",
	"stairsD",
	NULL};

class Corridor
{
public:
	corridorType type; //��������
	corridorDir dir;   //����
	glm::vec3 loc;	   //���½ǵ�����

	glm::vec3 inf;	 //�ӿڵ����½�����
	glm::mat4 model; //�任����
	Shader* shader;	 //��ɫ��
	Model *_model;	 //ģ����
	glm::vec3 lightPos;

	// std::vector<Object> objectList;�����������б�
	Model* lamp_model;
	glm::mat4 lamp_pos; //�Ʊ任����
	glm::mat4 paint_pos1; //���任����1
	glm::mat4 paint_pos2; //���任����2
	glm::mat4 table_pos;
	glm::mat4 horse_pos;
	glm::mat4 bookcase_pos;

	int t1;
	int t2;

	bool is_back;

public:
	Corridor();
	Corridor(Model *corridor_model, corridorType type, corridorDir dir_, glm::mat4 model_); //��������������������
	void render(Role *camera);																																				//��Ⱦǰ�趨λ��
	void setInCorridor(Role *camera);																																				// ��ײ��⣬����������������
	bool isInCorridor(Role *camera);																																				//�Ƿ��ڵ�ǰ����֮��

protected:
	float stairsPos(float stairs_z, float role_z);
};
