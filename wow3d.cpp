#include "wow3d.hpp"

bool wow3d_event_receiver_t::OnEvent(const irr::SEvent& event)
{
	if(event.EventType==irr::EET_KEY_INPUT_EVENT)
	{
		if(!key_down[event.KeyInput.Key]&&event.KeyInput.PressedDown)
			key_pressed[event.KeyInput.Key]=true;

		if(key_down[event.KeyInput.Key]&&!event.KeyInput.PressedDown)
			key_released[event.KeyInput.Key]=true;

		key_down[event.KeyInput.Key]=event.KeyInput.PressedDown;
	}

	if(event.EventType==irr::EET_MOUSE_INPUT_EVENT)
	{
		switch(event.MouseInput.Event)
		{
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
			{
				if(!mouse_down[0])
					mouse_pressed[0]=true;

				mouse_down[0]=true;
				break;
			}

			case irr::EMIE_LMOUSE_LEFT_UP:
			{
				if(mouse_down[0])
					mouse_released[0]=true;

				mouse_down[0]=false;
				break;
			}

			case irr::EMIE_MMOUSE_PRESSED_DOWN:
			{
				if(!mouse_down[1])
					mouse_pressed[1]=true;

				mouse_down[1]=true;
				break;
			}

			case irr::EMIE_MMOUSE_LEFT_UP:
			{
				if(mouse_down[1])
					mouse_released[1]=true;

				mouse_down[1]=false;
				break;
			}

			case irr::EMIE_RMOUSE_PRESSED_DOWN:
			{
				if(!mouse_down[2])
					mouse_pressed[2]=true;

				mouse_down[2]=true;
				break;
			}

			case irr::EMIE_RMOUSE_LEFT_UP:
			{
				if(mouse_down[2])
					mouse_released[2]=true;

				mouse_down[2]=false;
				break;
			}

			case irr::EMIE_MOUSE_MOVED:
			{
				mouse_x=event.MouseInput.X;
				mouse_y=event.MouseInput.Y;
				break;
			}

			case irr::EMIE_MOUSE_WHEEL:
			{
				mouse_wheel=event.MouseInput.Wheel;
				break;
			}

			default:
				break;
		}
	}

	return false;
}

wow3d_event_receiver_t::wow3d_event_receiver_t()
{
	clear();
}

void wow3d_event_receiver_t::clear()
{
	for(size_t ii=0;ii<irr::KEY_KEY_CODES_COUNT;++ii)
	{
		key_down[ii]=false;
		key_pressed[ii]=false;
		key_released[ii]=false;
	}

	for(size_t ii=0;ii<3;++ii)
	{
		mouse_down[ii]=false;
		mouse_pressed[ii]=false;
		mouse_released[ii]=false;
	}

	mouse_x=0;
	mouse_y=0;
	mouse_wheel=0;
}

void wow3d_event_receiver_t::reset()
{
	for(size_t ii=0;ii<irr::KEY_KEY_CODES_COUNT;++ii)
	{
		key_pressed[ii]=false;
		key_released[ii]=false;
	}

	for(size_t ii=0;ii<3;++ii)
	{
		mouse_pressed[ii]=false;
		mouse_released[ii]=false;
	}

	mouse_wheel=0;
}

wow3d_t::wow3d_t(const uint32_t& width,const uint32_t& height,const bool& fullscreen):
	device(nullptr),driver(nullptr),scene(nullptr),camera_m(nullptr),event_m(),
	title_m("Title"),width_m(width),height_m(height),fullscreen_m(fullscreen),
	cursor_m(false),position_m({0,0,0}),target_m({0,0,0}),up_m({0,1,0}),old_time_m(0)
{}

wow3d_t::~wow3d_t()
{
	stop();
}

bool wow3d_t::good() const
{
	return (device!=nullptr&&driver!=nullptr&&scene!=nullptr&&camera_m!=nullptr);
}

vector3df wow3d_t::get_position() const
{
	return position_m;
}

vector3df wow3d_t::get_target() const
{
	return target_m;
}

vector3df wow3d_t::get_up() const
{
	return up_m;
}

void wow3d_t::set_title(const std::string& title)
{
	title_m=title;

	if(good())
	{
		std::wstring wtitle(title_m.begin(),title_m.end());
		device->setWindowCaption(wtitle.c_str());
	}
}

void wow3d_t::show_cursor(const bool& show)
{
	cursor_m=show;

	if(good())
		device->getCursorControl()->setVisible(cursor_m);
}

void wow3d_t::set_position(const vector3df& position)
{
	position_m=position;

	if(good())
		camera_m->setPosition(position_m);
}

void wow3d_t::set_target(const vector3df& target)
{
	target_m=target;

	if(good())
		camera_m->setTarget(target_m);
}

void wow3d_t::set_up(const vector3df& up)
{
	up_m=up;

	if(good())
		camera_m->setUpVector(up_m);
}

void wow3d_t::setup()
{
	if(!good())
	{
		device=irr::createDevice(irr::video::EDT_OPENGL,{width_m,height_m},16,
			fullscreen_m,true,false,&event_m);

		if(device==nullptr)
		{
			stop();
			return;
		}

		driver=device->getVideoDriver();
		scene=device->getSceneManager();

		if(driver==nullptr||scene==nullptr)
		{
			stop();
			return;
		}

		camera_m=scene->addCameraSceneNode(0,position_m,target_m);

		if(camera_m==nullptr)
		{
			stop();
			return;
		}

		set_title(title_m);
		show_cursor(cursor_m);
		set_position(position_m);
		set_target(target_m);
		set_up(up_m);
	}
}

void wow3d_t::stop()
{
	if(driver)
		driver->endScene();

	if(scene)
		scene->clear();

	if(device)
	{
		device->drop();
		device=nullptr;
		driver=nullptr;
		scene=nullptr;
		camera_m=nullptr;
	}
}

void wow3d_t::loop(loop_function_t loop_func)
{
	if(good())
	{
		while(device->run())
		{
			double new_time=device->getTimer()->getTime();
			double dt=(new_time-old_time_m)/1000.0;
			old_time_m=new_time;

			loop_func(dt,event_m);

			event_m.reset();
			driver->beginScene(true,true,{255,100,101,140});
			scene->drawAll();
			driver->endScene();
		}
	}
}