#include "model.hpp"

#include <stdexcept>
#include <iostream>

model_t::model_t(wow3d_t& irrlicht,const std::string& model):
	wow3d_m(&irrlicht),mesh_m(nullptr),node_m(nullptr),model_m(model),texture_m(""),bumpmap_m(""),
	lighting_m(false),position_m({0,0,0}),rotation_m({0,0,0}),scale_m({1,1,1})
{}

model_t::~model_t()
{
	if(good())
		node_m->remove();
}

bool model_t::good() const
{
	return (wow3d_m!=nullptr&&wow3d_m->good()&&mesh_m!=nullptr&&node_m!=nullptr);
}

vector3df model_t::get_position() const
{
	return position_m;
}

vector3df model_t::get_rotation() const
{
	return rotation_m;
}

vector3df model_t::get_scale() const
{
	return scale_m;
}

void model_t::set_lighting(const bool& on)
{
	lighting_m=on;

	if(good())
		node_m->setMaterialFlag(irr::video::EMF_LIGHTING,lighting_m);
}

void model_t::set_texture(const std::string& texture)
{
	texture_m=texture;

	if(good())
	{
		if(texture_m!="")
		{
			irr::video::ITexture* texture=wow3d_m->driver->getTexture(texture_m.c_str());

			if(texture==nullptr)
				throw std::runtime_error("Invalid texture file - \""+texture_m+"\".");

			node_m->setMaterialTexture(0,texture);
		}
		else
		{
			node_m->setMaterialTexture(0,nullptr);
		}
	}
}

void model_t::set_bumpmap(const std::string& bumpmap)
{
	bumpmap_m=bumpmap;

	if(good())
	{
		if(bumpmap_m!="")
		{
			irr::video::ITexture* bumpmap=wow3d_m->driver->getTexture(bumpmap_m.c_str());

			if(bumpmap==nullptr)
				throw std::runtime_error("Invalid bumpmap file - \""+bumpmap_m+"\".");

			wow3d_m->driver->makeNormalMapTexture(bumpmap,9.0f);
			node_m->setMaterialTexture(1,bumpmap);
			node_m->setMaterialType(irr::video::EMT_NORMAL_MAP_SOLID);
		}
		else
		{
			node_m->setMaterialTexture(1,nullptr);
		}
	}
}

void model_t::set_position(const vector3df& position)
{
	position_m=position;

	if(good())
		node_m->setPosition(position_m);
}

void model_t::set_rotation(const vector3df& rotation)
{
	rotation_m=rotation;

	if(good())
		node_m->setRotation(rotation_m);
}

void model_t::set_scale(const vector3df& scale)
{
	scale_m=scale;

	if(good())
		node_m->setScale(scale_m);
}

void model_t::set_scale(const float& scale)
{
	set_scale({scale,scale,scale});
}

void model_t::load()
{
	if(wow3d_m!=nullptr&&wow3d_m->good())
	{
		if(model_m=="")
			throw std::runtime_error("Invalid model file - \""+model_m+"\".");

		mesh_m=wow3d_m->scene->getMesh(model_m.c_str());

		if(mesh_m==nullptr)
			throw std::runtime_error("Invalid model file - \""+model_m+"\".");

		node_m=wow3d_m->scene->addAnimatedMeshSceneNode(mesh_m);

		if(node_m==nullptr)
			throw std::runtime_error("Could not create scene node with mesh - \""+model_m+"\".");

		set_texture(texture_m);
		set_bumpmap(bumpmap_m);
		set_lighting(lighting_m);
		set_position(position_m);
		set_rotation(rotation_m);
		set_scale(scale_m);
	}
}