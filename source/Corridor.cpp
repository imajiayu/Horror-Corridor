#include "../include/Corridor.h"
Corridor::Corridor() 
{

}
Corridor::Corridor(Model *corridor_model, corridorType type_, corridorDir dir_, glm::mat4 model_) : is_back(false)
{
	// shader = new Shader("./source/shaders/corridor.vs", "./source/shaders/corridor.fs"); //内存泄漏了
	shader = corridor_shader;
	_model = corridor_model;
	switch (type_)
	{
	case straightCorridor:
		inf = glm::vec3(model_ * glm::vec4(glm::vec3(0, 0, -10), 1));
		lightPos = glm::vec3(model_ * glm::vec4(1, 2.4, -5, 1));
		lamp_pos = glm::translate(model_, glm::vec3(1, 2.4, -5));
		paint_pos1 = glm::translate(model_, glm::vec3(0, 1, -7));
		paint_pos2 = glm::translate(model_, glm::vec3(1.9, 1, -3));
		bookcase_pos=glm::translate(model_, glm::vec3(0, 0, -2));
		break;
	case cornerCorridorL:
		inf = glm::vec3(model_ * glm::vec4(glm::vec3(-8, 0, -8), 1));
		lightPos = glm::vec3(model_ * glm::vec4(1, 2.4, -9, 1));
		lamp_pos = glm::translate(model_, glm::vec3(1, 2.4, -9));
		paint_pos1 = glm::translate(model_, glm::vec3(0, 1, -7));
		paint_pos2 = glm::translate(model_, glm::vec3(-5, 1, -8));
		paint_pos2 = glm::rotate(paint_pos2, glm::radians(90.f), glm::vec3(0, 1, 0));

		
		table_pos = glm::translate(model_, glm::vec3(0.3, 0, -9.9));
		table_pos = glm::rotate(table_pos, glm::radians(90.f), glm::vec3(0, 1, 0));
		table_pos = glm::scale(table_pos, glm::vec3(0.3));

		horse_pos=glm::translate(model_, glm::vec3(1, 0.87, -9.75));
		horse_pos = glm::scale(horse_pos, glm::vec3(1));
		break;
	case cornerCorridorR:
		inf = glm::vec3(model_ * glm::vec4(glm::vec3(10, 0, -10), 1));
		lightPos = glm::vec3(model_ * glm::vec4(1, 2.4, -9, 1));
		lamp_pos = glm::translate(model_, glm::vec3(1, 2.4, -9));
		paint_pos1 = glm::translate(model_, glm::vec3(0, 1, -7));
		paint_pos2 = glm::translate(model_, glm::vec3(5, 1, -10));
		paint_pos2 = glm::rotate(paint_pos2, glm::radians(90.f), glm::vec3(0, 1, 0));


		table_pos = glm::translate(model_, glm::vec3(0.3, 0, -9.9));
		table_pos = glm::rotate(table_pos, glm::radians(90.f), glm::vec3(0, 1, 0));
		table_pos = glm::scale(table_pos, glm::vec3(0.3));

		horse_pos = glm::translate(model_, glm::vec3(1, 0.87, -9.75));
		horse_pos = glm::scale(horse_pos, glm::vec3(1));
		break;
	case stairsCorridorU:
		inf = glm::vec3(model_ * glm::vec4(glm::vec3(0, 4.8, -10), 1));
		lightPos = glm::vec3(model_ * glm::vec4(1, 4.8, -5, 1));
		lamp_pos = glm::translate(model_, glm::vec3(1, 4.8, -5));
		lamp_pos = glm::rotate(lamp_pos, glm::radians(30.0f), glm::vec3(1, 0, 0));
		paint_pos1 = glm::translate(model_, glm::vec3(0, 5.3, -7));
		paint_pos2 = glm::translate(model_, glm::vec3(1.9, 3.3, -3));
		break;
	case stairsCorridorD:
		inf = glm::vec3(model_ * glm::vec4(glm::vec3(0, -4.8, -10), 1));
		lightPos = glm::vec3(model_ * glm::vec4(1, -4.8, -5, 1));
		lamp_pos = glm::translate(model_, glm::vec3(1, 0, -5));
		lamp_pos = glm::rotate(lamp_pos, glm::radians(-30.0f), glm::vec3(1, 0, 0));
		paint_pos1 = glm::translate(model_, glm::vec3(0, -2, -7));
		paint_pos2 = glm::translate(model_, glm::vec3(1.9, 0, -3));
		break;
	}
	type = type_;
	dir = dir_;
	model = model_;
	loc = glm::vec3(model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	t1 = rand() % 6;
	t2=rand() % 6;

}

void Corridor::render(Role* camera)
{
	/*
		把走廊中的所有物体渲染一遍
		*/

		//渲染走廊
	shader->use();
	// vs
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	shader->setMat4("model", this->model);
	// fs
	shader->setVec3("viewPos", camera->Position);
	shader->setInt("material.diffuse", 0);
	shader->setInt("material.normalMap", 1);//因为只贴了2张图，所以normalmap是1！！
	shader->setInt("material.specular", 2);//无镜面贴图
	shader->setFloat("material.shininess", 32.0f);

	shader->setVec3("pointLight.position", lightPos);
	shader->setVec3("pointLight.ambient", 0.10f, 0.10f, 0.10f);
	shader->setVec3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
	shader->setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
	shader->setFloat("pointLight.constant", 2.0f);
	shader->setFloat("pointLight.linear", 0.09);
	//shader->setFloat("pointLight.quadratic", 0.032);
	shader->setFloat("pointLight.quadratic", 0.08);

	// spotLight
	shader->setVec3("spotLight.position", camera->Position);
	shader->setVec3("spotLight.direction", camera->Front);
	shader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	shader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	shader->setFloat("spotLight.constant", 1.0f);
	shader->setFloat("spotLight.linear", 0.09);
	shader->setFloat("spotLight.quadratic", 0.032);
	shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(8.0f)));
	shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	extern bool spotLightOff;
	shader->setVec3("spotLightOff", glm::vec3(spotLightOff));

	extern glm::vec3 pointLightOff;
	shader->setVec3("lightOff", pointLightOff);

	_model->Draw(*shader);

	//渲染灯
	Lamp aLamp(lamp_model, lamp_pos);
	aLamp.render(camera);

	Paint aPaint1(paintList.at(t1), paint_pos1);
	aPaint1.shader->use();
	aPaint1.shader->setVec3("pointLight.position", lightPos);

	Paint aPaint2(paintList.at(t2), paint_pos2);
	aPaint2.shader->use();
	aPaint2.shader->setVec3("pointLight.position", lightPos);

	aPaint1.render(camera);
	aPaint2.render(camera);


	if (this->type == cornerCorridorL || this->type == cornerCorridorR)
	{
			Paint aTable(table_model, table_pos);
			aTable.render(camera);

			Paint ahorse(horse_model, glm::rotate(horse_pos,float(sin(4 * glfwGetTime())*glm::radians(12.f)),glm::vec3(0,0,1)));
			ahorse.render(camera);
	}
	/*
	if (this->type == straightCorridor)
	{
		Lamp aBookcase(bookcase_model, bookcase_pos);
		aBookcase.render(camera);
	}
	*/
}

void Corridor::setInCorridor(Role *camera)
{
	glm::vec3 &pos = camera->Position;
	float _height = camera->height;
	float _width = camera->width;
	float dis1, dis2, dis3, dis4;
	if (this->type == straightCorridor || this->type == stairsCorridorD || this->type == stairsCorridorU)
	{
		switch (dir)
		{
		case xP:
			// if (loc.x < camera->Position.x && camera->Position.x < loc.x + 10 && loc.z < camera->Position.z && camera->Position.z < loc.z + 2)
			if (pos.z - _width / 2 < loc.z)
			{
				pos.z = loc.z + _width / 2;
			}
			else if (pos.z + _width / 2 > loc.z + 2)
			{
				pos.z = loc.z + 2 - _width / 2;
			}
			if (this->type != straightCorridor)
				pos.y = (loc.y + stairsPos(inf.y - loc.y, fabs(pos.x - loc.x) / 10 * (inf.y - loc.y)) + camera->height);
			break;
		case zP:
			// if (loc.z < camera->Position.z && camera->Position.z < loc.z + 10 && loc.x - 2 < camera->Position.x && camera->Position.x < loc.x)
			if (pos.x - _width / 2 < loc.x - 2)
			{
				pos.x = loc.x - 2 + _width / 2;
			}
			else if (pos.x + _width / 2 > loc.x)
			{
				pos.x = loc.x - _width / 2;
			}
			if (this->type != straightCorridor)
				pos.y = (loc.y + stairsPos(inf.y - loc.y, fabs(pos.z - loc.z) / 10 * (inf.y - loc.y)) + camera->height);
			// pos.y = (loc.y + fabs(pos.z - loc.z) * ((inf.y - loc.y) / 10) + camera->height);
			break;
		case xN:
			if (pos.z - _width / 2 < loc.z - 2)
			{
				pos.z = loc.z - 2 + _width / 2;
			}
			else if (pos.z + _width / 2 > loc.z)
			{
				pos.z = loc.z - _width / 2;
			}
			if (this->type != straightCorridor)
				pos.y = (loc.y + stairsPos(inf.y - loc.y, fabs(pos.x - loc.x) / 10 * (inf.y - loc.y)) + camera->height);
			break;
		case zN:
			if (pos.x - _width / 2 < loc.x)
			{
				pos.x = loc.x + _width / 2;
			}
			else if (pos.x + _width / 2 > loc.x + 2)
			{
				pos.x = loc.x + 2 - _width / 2;
			}
			if (this->type != straightCorridor)
				pos.y = (loc.y + stairsPos(inf.y - loc.y, fabs(pos.z - loc.z) / 10 * (inf.y - loc.y)) + camera->height);
			break;
		}
	}
	// 2种转弯统一，使用判断左右的方法来做
	else if (this->type == cornerCorridorL)
	{
		switch (dir)
		{
		case xP:
			dis1 = loc.z - (pos.z - _width / 2);
			dis2 = loc.x + 8 - (pos.x - _width / 2);
			dis3 = (pos.z + _width / 2) - (loc.z + 2);
			dis4 = (pos.x + _width / 2) - (loc.x + 10);
			if (dis1 > 0 && dis2 > 0)
			{
				if (dis1 < dis2)
				{
					pos.z = loc.z + _width / 2;
				}
				else
				{
					pos.x = loc.x + 8 + _width / 2;
				}
			}
			// else if (dis1 > 0)
			// {
			// 	pos.z = loc.z + _width / 2;
			// }
			// else if (dis2 > 0)
			// {
			// 	pos.x = loc.x + 8 + _width / 2;
			// }
			if (dis3 > 0)
			{
				pos.z = loc.z + 2 - _width / 2;
			}
			if (dis4 > 0)
			{
				pos.x = loc.x + 10 - _width / 2;
			}

			break;
		case zP:
			dis1 = pos.x + _width / 2 - loc.x;
			dis2 = loc.z + 8 - (pos.z - _width / 2);
			dis3 = loc.x - 2 - (pos.x - _width / 2);
			dis4 = (pos.z + _width / 2) - (loc.z + 10);
			if (dis1 > 0 && dis2 > 0)
			{
				if (dis1 < dis2)
				{
					pos.x = loc.x - _width / 2;
				}
				else
				{
					pos.z = loc.z + 8 + _width / 2;
				}
			}
			// else if (dis1 > 0)
			// {
			// 	pos.x = loc.x + 2 - _width / 2;
			// }
			// else if (dis2 > 0)
			// {
			// 	pos.z = loc.z + 8 + _width / 2;
			// }
			if (dis3 > 0)
			{
				pos.x = loc.x - 2 + _width / 2;
			}
			if (dis4 > 0)
			{
				pos.z = loc.z + 10 - _width / 2;
			}

			break;
		case xN:
			dis1 = pos.z + _width / 2 - loc.z;
			dis2 = pos.x + _width / 2 - (loc.x - 8);
			dis3 = loc.z - 2 - (pos.z - _width / 2);
			dis4 = loc.x - 10 - (pos.x - _width / 2);
			if (dis1 > 0 && dis2 > 0)
			{
				if (dis1 < dis2)
				{
					pos.z = loc.z - _width / 2;
				}
				else
				{
					pos.x = loc.x - 8 - _width / 2;
				}
			}
			// else if (dis1 > 0)
			// {
			// 	pos.z = loc.z + 2 - _width / 2;
			// }
			// else if (dis2 > 0)
			// {
			// 	pos.x = loc.x - 8 - _width / 2;
			// }
			if (dis3 > 0)
			{
				pos.z = loc.z - 2 + _width / 2;
			}
			if (dis4 > 0)
			{
				pos.x = loc.x - 10 + _width / 2;
			}

			break;
		case zN:
			dis1 = loc.x - (pos.x - _width / 2);
			dis2 = pos.z + _width / 2 - (loc.z - 8);
			dis3 = pos.x + _width / 2 - (loc.x + 2);
			dis4 = loc.z - 10 - (pos.z - _width / 2);
			if (dis1 > 0 && dis2 > 0)
			{
				if (dis1 < dis2)
				{
					pos.x = loc.x + _width / 2;
				}
				else
				{
					pos.z = loc.z - 8 - _width / 2;
				}
			}
			// else if (dis1 > 0)
			// {
			// 	pos.x = loc.x + _width / 2;
			// }
			// else if (dis2 > 0)
			// {
			// 	pos.z = loc.z - 8 - _width / 2;
			// }
			if (dis3 > 0)
			{
				pos.x = loc.x + 2 - _width / 2;
			}
			if (dis4 > 0)
			{
				pos.z = loc.z - 10 + _width / 2;
			}

			break;
		}
	}
	else if (this->type == cornerCorridorR)
	{
		switch (dir)
		{
		case xP:
			dis1 = (pos.z + _width / 2) - (loc.z + 2);
			dis2 = loc.x + 8 - (pos.x - _width / 2);
			dis3 = loc.z - (pos.z - _width / 2);
			dis4 = (pos.x + _width / 2) - (loc.x + 10);
			if (dis1 > 0 && dis2 > 0)
			{
				if (dis1 < dis2)
				{
					pos.z = loc.z + 2 - _width / 2;
				}
				else
				{
					pos.x = loc.x + 8 + _width / 2;
				}
			}
			// else if (dis1 > 0)
			// {
			// 	pos.z = loc.z + 2 - _width / 2;
			// }
			// else if (dis2 > 0)
			// {
			// 	pos.x = loc.x + 8 + _width / 2;
			// }
			if (dis3 > 0)
			{
				pos.z = loc.z + _width / 2;
			}
			if (dis4 > 0)
			{
				pos.x = loc.x + 10 - _width / 2;
			}

			break;
		case zP:
			dis1 = loc.x - 2 - (pos.x - _width / 2);
			dis2 = loc.z + 8 - (pos.z - _width / 2);
			dis3 = pos.x + _width / 2 - loc.x;
			dis4 = (pos.z + _width / 2) - (loc.z + 10);
			if (dis1 > 0 && dis2 > 0)
			{
				if (dis1 < dis2)
				{
					pos.x = loc.x - 2 + _width / 2;
				}
				else
				{
					pos.z = loc.z + 8 + _width / 2;
				}
			}
			// else if (dis1 > 0)
			// {
			// 	pos.x = loc.x + _width / 2;
			// }
			// else if (dis2 > 0)
			// {
			// 	pos.z = loc.z + 8 + _width / 2;
			// }
			if (dis3 > 0)
			{
				pos.x = loc.x - _width / 2;
			}
			if (dis4 > 0)
			{
				pos.z = loc.z + 10 - _width / 2;
			}

			break;
		case xN:
			dis1 = loc.z - 2 - (pos.z - _width / 2);
			dis2 = pos.x + _width / 2 - (loc.x - 8);
			dis3 = pos.z + _width / 2 - loc.z;
			dis4 = loc.x - 10 - (pos.x - _width / 2);
			if (dis1 > 0 && dis2 > 0)
			{
				if (dis1 < dis2)
				{
					pos.z = loc.z - 2 + _width / 2;
				}
				else
				{
					pos.x = loc.x - 8 - _width / 2;
				}
			}
			// else if (dis1 > 0)
			// {
			// 	pos.z = loc.z + _width / 2;
			// }
			// else if (dis2 > 0)
			// {
			// 	pos.x = loc.x - 8 - _width / 2;
			// }
			if (dis3 > 0)
			{
				pos.z = loc.z - _width / 2;
			}
			if (dis4 > 0)
			{
				pos.x = loc.x - 10 + _width / 2;
			}

			break;
		case zN:
			dis1 = pos.x + _width / 2 - (loc.x + 2);
			dis2 = pos.z + _width / 2 - (loc.z - 8);
			dis3 = loc.x - (pos.x - _width / 2);
			dis4 = loc.z - 10 - (pos.z - _width / 2);
			if (dis1 > 0 && dis2 > 0)
			{
				if (dis1 < dis2)
				{
					pos.x = loc.x + 2 - _width / 2;
				}
				else
				{
					pos.z = loc.z - 8 - _width / 2;
				}
			}
			// else if (dis1 > 0)
			// {
			// 	pos.x = loc.x + 2 - _width / 2;
			// }
			// else if (dis2 > 0)
			// {
			// 	pos.z = loc.z - 8 - _width / 2;
			// }
			if (dis3 > 0)
			{
				pos.x = loc.x + _width / 2;
			}
			if (dis4 > 0)
			{
				pos.z = loc.z - 10 + _width / 2;
			}

			break;
		}
	}
	if (this->type == straightCorridor || this->type == cornerCorridorL || this->type == cornerCorridorR)
		pos.y = loc.y + camera->height;
}

bool Corridor::isInCorridor(Role *camera)
{
	if (this->type == straightCorridor || this->type == stairsCorridorD || this->type == stairsCorridorU)
	{
		switch (dir)
		{
		case xP:
			if (loc.x < camera->Position.x && camera->Position.x < loc.x + 10)
				return true;
			break;
		case zP:
			if (loc.z < camera->Position.z && camera->Position.z < loc.z + 10)
				return true;
			break;
		case xN:
			if (loc.x - 10 < camera->Position.x && camera->Position.x < loc.x)
				return true;
			break;
		case zN:
			if (loc.z - 10 < camera->Position.z && camera->Position.z < loc.z)
				return true;
			break;
		}
	}
	else if (this->type == cornerCorridorL)
	{
		switch (dir)
		{
		case xP:
			if (loc.x < camera->Position.x && loc.z - 8 < camera->Position.z)
				return true;
			break;
		case zP:
			if (loc.z < camera->Position.z && camera->Position.x < loc.x + 8)
				return true;
			break;
		case xN:
			if (camera->Position.x < loc.x && camera->Position.z < loc.z + 8)
				return true;
			break;
		case zN:
			if (camera->Position.z < loc.z && loc.x - 8 < camera->Position.x)
				return true;
			break;
		}
	}
	else
	{
		switch (dir)
		{
		case xP:
			if (loc.x < camera->Position.x && camera->Position.z < loc.z + 10)
				return true;
			break;
		case zP:
			if (loc.z < camera->Position.z && loc.x - 10 < camera->Position.x)
				return true;
			break;
		case xN:
			if (camera->Position.x < loc.x && loc.z - 10 < camera->Position.z)
				return true;
			break;
		case zN:
			if (camera->Position.z < loc.z && camera->Position.x < loc.x + 10)
				return true;
			break;
		}
	}
	return false;
}

float Corridor::stairsPos(float stairs_z, float role_z)
{
	float stair_h = stairs_z / STAIRS_NUM;
	int num = role_z / stair_h;
	if (role_z > (2 * num + 1) * stair_h / 2)
	{
		return (num + 1) * stair_h;
	}
	else
	{
		return 2 * role_z - (num * stair_h);
	}
}
