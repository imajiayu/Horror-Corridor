#include "..\include\parameter.h"
#include "..\include\model.h"
Model* straight_model1=NULL;
Model* straight_model = NULL;
Model* cornerL_model = NULL;
Model* cornerR_model = NULL;
Model* stairU_model = NULL;
Model* stairD_model = NULL;
Model* lamp_model = NULL;
Model* paint_model = NULL;
Model* paint_model1 = NULL;
Model* paint_model2 = NULL;
Model* paint_model3 = NULL;
Model* paint_model4 = NULL;
Model* paint_model5 = NULL;
Model* table_model = NULL;
Model* horse_model = NULL;
Model* ghost_model = NULL;
Model* bookcase_model = NULL;
Shader* corridor_shader = NULL;
Shader* lamp_shader = NULL;
Shader* paint_shader = NULL;
vector<Model*> paintList;

//手电筒开关
bool spotLightOff=0;

//控制闪烁
int darkTime = 0;
glm::vec3 pointLightOff;