#ifndef WOW3D_HPP
#define WOW3D_HPP

#include <irrlicht/irrlicht.h>
#include <cstdint>
#include <functional>
#include <string>

using irr::core::vector3df;
using irr::KEY_LBUTTON;
using irr::KEY_RBUTTON;
using irr::KEY_CANCEL;
using irr::KEY_MBUTTON;
using irr::KEY_XBUTTON1;
using irr::KEY_XBUTTON2;
using irr::KEY_BACK;
using irr::KEY_TAB;
using irr::KEY_CLEAR;
using irr::KEY_RETURN;
using irr::KEY_SHIFT;
using irr::KEY_CONTROL;
using irr::KEY_MENU;
using irr::KEY_PAUSE;
using irr::KEY_CAPITAL;
using irr::KEY_KANA;
using irr::KEY_HANGUEL;
using irr::KEY_HANGUL;
using irr::KEY_JUNJA;
using irr::KEY_FINAL;
using irr::KEY_HANJA;
using irr::KEY_KANJI;
using irr::KEY_ESCAPE;
using irr::KEY_CONVERT;
using irr::KEY_NONCONVERT;
using irr::KEY_ACCEPT;
using irr::KEY_MODECHANGE;
using irr::KEY_SPACE;
using irr::KEY_PRIOR;
using irr::KEY_NEXT;
using irr::KEY_END;
using irr::KEY_HOME;
using irr::KEY_LEFT;
using irr::KEY_UP;
using irr::KEY_RIGHT;
using irr::KEY_DOWN;
using irr::KEY_SELECT;
using irr::KEY_PRINT;
using irr::KEY_EXECUT;
using irr::KEY_SNAPSHOT;
using irr::KEY_INSERT;
using irr::KEY_DELETE;
using irr::KEY_HELP;
using irr::KEY_KEY_0;
using irr::KEY_KEY_1;
using irr::KEY_KEY_2;
using irr::KEY_KEY_3;
using irr::KEY_KEY_4;
using irr::KEY_KEY_5;
using irr::KEY_KEY_6;
using irr::KEY_KEY_7;
using irr::KEY_KEY_8;
using irr::KEY_KEY_9;
using irr::KEY_KEY_A;
using irr::KEY_KEY_B;
using irr::KEY_KEY_C;
using irr::KEY_KEY_D;
using irr::KEY_KEY_E;
using irr::KEY_KEY_F;
using irr::KEY_KEY_G;
using irr::KEY_KEY_H;
using irr::KEY_KEY_I;
using irr::KEY_KEY_J;
using irr::KEY_KEY_K;
using irr::KEY_KEY_L;
using irr::KEY_KEY_M;
using irr::KEY_KEY_N;
using irr::KEY_KEY_O;
using irr::KEY_KEY_P;
using irr::KEY_KEY_Q;
using irr::KEY_KEY_R;
using irr::KEY_KEY_S;
using irr::KEY_KEY_T;
using irr::KEY_KEY_U;
using irr::KEY_KEY_V;
using irr::KEY_KEY_W;
using irr::KEY_KEY_X;
using irr::KEY_KEY_Y;
using irr::KEY_KEY_Z;
using irr::KEY_LWIN;
using irr::KEY_RWIN;
using irr::KEY_APPS;
using irr::KEY_SLEEP;
using irr::KEY_NUMPAD0;
using irr::KEY_NUMPAD1;
using irr::KEY_NUMPAD2;
using irr::KEY_NUMPAD3;
using irr::KEY_NUMPAD4;
using irr::KEY_NUMPAD5;
using irr::KEY_NUMPAD6;
using irr::KEY_NUMPAD7;
using irr::KEY_NUMPAD8;
using irr::KEY_NUMPAD9;
using irr::KEY_MULTIPLY;
using irr::KEY_ADD;
using irr::KEY_SEPARATOR;
using irr::KEY_SUBTRACT;
using irr::KEY_DECIMAL;
using irr::KEY_DIVIDE;
using irr::KEY_F1;
using irr::KEY_F2;
using irr::KEY_F3;
using irr::KEY_F4;
using irr::KEY_F5;
using irr::KEY_F6;
using irr::KEY_F7;
using irr::KEY_F8;
using irr::KEY_F9;
using irr::KEY_F10;
using irr::KEY_F11;
using irr::KEY_F12;
using irr::KEY_F13;
using irr::KEY_F14;
using irr::KEY_F15;
using irr::KEY_F16;
using irr::KEY_F17;
using irr::KEY_F18;
using irr::KEY_F19;
using irr::KEY_F20;
using irr::KEY_F21;
using irr::KEY_F22;
using irr::KEY_F23;
using irr::KEY_F24;
using irr::KEY_NUMLOCK;
using irr::KEY_SCROLL;
using irr::KEY_LSHIFT;
using irr::KEY_RSHIFT;
using irr::KEY_LCONTROL;
using irr::KEY_RCONTROL;
using irr::KEY_LMENU;
using irr::KEY_RMENU;
using irr::KEY_OEM_1;
using irr::KEY_PLUS;
using irr::KEY_COMMA;
using irr::KEY_MINUS;
using irr::KEY_PERIOD;
using irr::KEY_OEM_2;
using irr::KEY_OEM_3;
using irr::KEY_OEM_4;
using irr::KEY_OEM_5;
using irr::KEY_OEM_6;
using irr::KEY_OEM_7;
using irr::KEY_OEM_8;
using irr::KEY_OEM_AX;
using irr::KEY_OEM_102;
using irr::KEY_ATTN;
using irr::KEY_CRSEL;
using irr::KEY_EXSEL;
using irr::KEY_EREOF;
using irr::KEY_PLAY;
using irr::KEY_ZOOM;
using irr::KEY_PA1;
using irr::KEY_OEM_CLEAR;

class wow3d_event_receiver_t:public irr::IEventReceiver
{
	private:
		friend class wow3d_t;

		wow3d_event_receiver_t();

		virtual bool OnEvent(const irr::SEvent& event);

		void clear();
		void reset();

	public:
		bool key_down[irr::KEY_KEY_CODES_COUNT];
		bool key_pressed[irr::KEY_KEY_CODES_COUNT];
		bool key_released[irr::KEY_KEY_CODES_COUNT];
		bool mouse_down[3];
		bool mouse_pressed[3];
		bool mouse_released[3];
		double mouse_x;
		double mouse_y;
		double mouse_wheel;
};

typedef std::function<void(const double& dt,const wow3d_event_receiver_t& event)> loop_function_t;

class wow3d_t
{
	public:
		irr::IrrlichtDevice* device;
		irr::video::IVideoDriver* driver;
		irr::scene::ISceneManager* scene;

		wow3d_t(const uint32_t& width,const uint32_t& height,const bool& fullscreen);
		virtual ~wow3d_t();
		wow3d_t(const wow3d_t& copy)=delete;
		wow3d_t& operator=(const wow3d_t& copy)=delete;

		virtual bool good() const;

		virtual vector3df get_position() const;
		virtual vector3df get_target() const;
		virtual vector3df get_up() const;

		virtual void set_title(const std::string& title);
		virtual void show_cursor(const bool& show);
		virtual void set_position(const vector3df& position);
		virtual void set_target(const vector3df& target);
		virtual void set_up(const vector3df& up);

		virtual void setup();
		virtual void stop();
		virtual void loop(loop_function_t loop_func);

	private:
		irr::scene::ICameraSceneNode* camera_m;
		wow3d_event_receiver_t event_m;
		std::string title_m;
		uint32_t width_m;
		uint32_t height_m;
		bool fullscreen_m;
		bool cursor_m;
		vector3df position_m;
		vector3df target_m;
		vector3df up_m;
		double old_time_m;
};

#endif