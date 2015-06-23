#ifndef WOW3D_MODEL_HPP
#define WOW3D_MODEL_HPP

#include <irrlicht/irrlicht.h>
#include "wow3d.hpp"
#include <string>

class model_t
{
	public:
		model_t(wow3d_t& irrlicht,const std::string& model);
		virtual ~model_t();
		model_t(const model_t& copy)=delete;
		model_t& operator=(const model_t& copy)=delete;

		virtual bool good() const;

		virtual vector3df get_position() const;
		virtual vector3df get_rotation() const;
		virtual vector3df get_scale() const;

		virtual void set_lighting(const bool& on);
		virtual void set_texture(const std::string& texture);
		virtual void set_bumpmap(const std::string& bumpmap);
		virtual void set_position(const vector3df& position);
		virtual void set_rotation(const vector3df& rotation);
		virtual void set_scale(const vector3df& scale);
		virtual void set_scale(const float& scale);

		virtual void load();

	private:
		wow3d_t* wow3d_m;
		irr::scene::IAnimatedMesh* mesh_m;
		irr::scene::IAnimatedMeshSceneNode* node_m;
		std::string model_m;
		std::string texture_m;
		std::string bumpmap_m;
		bool lighting_m;
		vector3df position_m;
		vector3df rotation_m;
		vector3df scale_m;
};

#endif