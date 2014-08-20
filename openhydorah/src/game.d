import hyd.engine;
import hyd.filesystem;
import hyd.ui;
import hyd.geom;
import hyd.text;
import hyd.gfx;
import hyd.color;
import hyd.quad;
import hyd.transform;
import hyd.input;
import hyd.entity;
import hyd.editor;
import hyd.scene;
import std.string;
import std.stdio;
import core.runtime;

import intro;
import main_menu;
import player;
import enemy;

class Game {
	uint color;
	hyd_font *font;
	//hyd_text *hello_world;
	hyd_text *text;
	hyd_locale *en_locale;
	hyd_locale *mm_locale;
	hyd_locale *ed_locale;

	Intro intro;
	MainMenu main_menu;
	hyd_program *argb_shdr;
	hyd_program *tex_shdr;
	hyd_program *gray_shdr;
	hyd_transform projection;
	hyd_transform camera;
	hyd_transform gui;
	
	Player player;
	Enemy enemies[];
	bool edit_mode = false;

	this () {
		color = 0xFF0000;
		hyd_transform_ident(&projection);
		hyd_transform_ident(&camera);
		hyd_transform_ident(&gui);
	}

	~this () {
		hyd_engine_destroy();
		hyd_font_destroy(font);
	}

	void init () {
		// hydorah resolution might be 960x480 divided by 3
		auto args = Runtime.cArgs;
		uint w = 960, h = 480;
		if (hyd_engine_init(args.argv, w, h)) {
			throw new Exception("Failed to init hyd engine");
		}

		//hyd_transform_ortho(&projection, 160, 120, 0.0f, 1.0f);
		hyd_transform_ortho(&projection, 960/3, 480/3, 0.0f, 1.0f);
		hyd_transform_ortho(&gui, w, h, 0.0f, 1.0f);

		argb_shdr = hyd_argb_shdr();
		tex_shdr = hyd_tex_shdr();
		gray_shdr = hyd_gray_shdr();

		hyd_quad area = {0,0,800,600};

		hyd_fs_add_path("assets/scenes", "/scenes");
		hyd_fs_add_path("assets/sprites", "/sprites");
		hyd_fs_add_path("assets/entities", "/entities");
		hyd_fs_add_path("assets/graphics", "/graphics");
		hyd_fs_add_path("assets/fonts", "/fonts");
		hyd_fs_add_path("assets/locales", "/locales");

		string scene = "/scenes/test.scene";
		if (hyd_engine_load_scene(scene.toStringz)) {
			throw new Exception("Failed to load scene");
		}

		string preset = "/scenes/keymap.set";
		if (hyd_engine_load_ip(preset.toStringz)) {
			throw new Exception("Failed to load input preset");
		}

		//string font_str = "/fonts/unifont-7.0.01.ttf";
		string font_str = "/fonts/fffgalax.ttf";
		font = hyd_font_create_file(font_str.toStringz);
		if (font == null)
			throw new Exception("Failed to load font " ~ font_str);

		string locale_str = "/locales/en.json";
		if (hyd_engine_load_locale(locale_str.toStringz))
			throw new Exception("Failed to load locale");

		en_locale = hyd_locale_find(hyd_engine_get_locale(), "en");
		if (en_locale == null)
			throw new Exception("Couldn't find locale 'en'");

		ed_locale = hyd_locale_find(en_locale.children, "editor");
		if (ed_locale == null)
			throw new Exception("Couldn't find locale 'editor'");
		
		//hyd_editor_init(&camera, eng.current_scene);
		//main_menu = new MainMenu(eng, en_locale, font);

		player = new Player();

		uint num = 0;
		hyd_ent **list = hyd_scene_find_ent_list(hyd_engine_get_scene(), "eger", &num);
		if (num == 0)
			throw new Exception("Eger not found");

		enemies.length = num;
		for (int i = 0; i < num; i++) {
			enemies[i] = new Enemy(list[i]);
		}
	}

	void run () {
		uint last_time = hyd_engine_get_time();
		uint current_time;
		uint dt;
		while (true) {
			hyd_engine_events();
			if (hyd_engine_get_quit())
				break;

			current_time = hyd_engine_get_time();
			dt = current_time - last_time;
			last_time = current_time;

			hyd_transform_stack_push(projection);
			hyd_transform_stack_push(camera);

			update(dt);

			hyd_engine_begin_draw();

			draw();

			hyd_transform_stack_pop();
			hyd_transform_stack_pop();
			hyd_transform_stack_push(gui);
			ui();
			hyd_transform_stack_pop();

			hyd_engine_end_draw();
		}
	}

	void update (uint dt) {
		player.update(dt);

		for (int i = 0; i < enemies.length; i++)
			enemies[i].update(dt);

		hyd_engine_update(dt);

		//hyd_editor_update();
	}

	void draw () {
		hyd_program_use(tex_shdr);
		
		hyd_engine_draw();
		
		player.draw();
		//hyd_editor_draw();
	}

	void ui () {
		static hyd_color c = {
			1.0f, 1.0f, 1.0f, 1.0f
		};
		//hyd_editor_ui();
		/*static hyd_color c;
		c.r = 0.2f;
		c.g = 0.2f;
		c.b = 0.2f;
		c.a = 1.0f;
		static hyd_quad q;
		q.x1 = 10.0f;
		q.y1 = 10.0f;
		q.x2 = 120.0f;
		q.y2 = 100.0f;
		hyd_program_use(argb_shdr);

		hyd_quad_draw(&q, &c);
		*/
	}
} 
