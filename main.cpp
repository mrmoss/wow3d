#include "wow3d.hpp"
#include "model.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

wow3d_t wow(640,480,false);
std::vector<model_t*> models;

void create_ship()
{
	model_t* model=new model_t(wow,"media/space_cruiser_4.obj");

	if(model==nullptr)
		throw std::runtime_error("Could not allocate memory for ship!");

	models.push_back(model);
	model->set_texture("media/space_cruiser_4_color.png");
	//model->set_bumpmap("media/space_cruiser_4_bump.png");
	//model->set_lighting(true);
	model->load();
}

void loop(const double& dt,const wow3d_event_receiver_t& event)
{
	if(event.key_down[KEY_KEY_W])
		wow.set_position(wow.get_position()+vector3df(0,0,500*dt));
	if(event.key_down[KEY_KEY_S])
		wow.set_position(wow.get_position()-vector3df(0,0,500*dt));
}

int main()
{
	try
	{
		wow.set_title("Hello world!");
		wow.show_cursor(true);
		wow.setup();
		wow.set_position({0,0,-100});
		wow.set_target({0,0,0});
		wow.set_up({0,1,0});
		create_ship();
		wow.loop(loop);
	}
	catch(std::exception& error)
	{
		std::cout<<"Error:  "<<error.what()<<std::endl;
	}
	catch(...)
	{
		std::cout<<"Unknown error."<<std::endl;
	}

	for(auto ii:models)
		delete ii;

	models.clear();

	wow.stop();

	return 0;
}