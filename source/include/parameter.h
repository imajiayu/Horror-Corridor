#pragma once
#include "..\include\model.h"
#include "..\include\shader.h"
#include <GLFW/glfw3.h>
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

extern Model* straight_model1;
extern Model* straight_model;
extern Model* cornerL_model;
extern Model* cornerR_model;
extern Model* stairU_model;
extern Model* stairD_model;
extern Model* lamp_model;
extern Model* paint_model;
extern Model* paint_model1;
extern Model* paint_model2;
extern Model* paint_model3;
extern Model* paint_model4;
extern Model* paint_model5;
extern Model* table_model;
extern Model* horse_model;
extern Model* ghost_model;
extern Model* bookcase_model;
extern Shader* corridor_shader;
extern Shader* lamp_shader;
extern Shader* paint_shader;
extern vector<Model*> paintList;