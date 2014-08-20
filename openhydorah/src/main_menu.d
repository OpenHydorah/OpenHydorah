import hyd.text;
import hyd.ui;
import hyd.engine;
import hyd.texture;
import hyd.geom;
import std.stdio;

class MainMenu {
	hyd_locale *locale;
	hyd_tex *bg;
	hyd_engine *eng;
	hyd_font *font;

	this(hyd_engine *e, hyd_locale *l, hyd_font *f) {
		eng = e;
		font = f;

		locale = hyd_locale_find(l.children, "main_menu");
		if (locale == null)
			throw new Exception("Couldn't find locale 'main_menu'");

		if (hyd_locale_render(locale, font))
			throw new Exception("Couldn't render main_menu locale");

		bg = hyd_tex_create_file("/graphics/backgrounds/bck_portada_01.png");
		if (bg == null)
			throw new Exception("Couldn't load bck_portada_01.png");
	}

	~this() {
		hyd_tex_destroy(bg);
	}

	void draw () {
		SDL_Rect full;
		full.x = 0;
		full.y = 0;
		full.w = 600;
		full.h = 480;

		//hyd_tex_draw(bg, eng.renderer, bg.size, full);
	}

	void ui() {
		/*uint scr_mid = 600 / 2;

		SDL_Point text_pos;
		text_pos.x = scr_mid - 40;
		text_pos.y = 60;

		hyd_text *t = hyd_locale_find_text(locale, "start");
		hyd_text_draw(eng.renderer, t, text_pos);
		if (hyd_ui_btn(text_pos.x, text_pos.y, text_pos.x + t.src.w, text_pos.y + t.src.h)
				== hyd_btn_state.DOWN_L)
			writeln("start");

		t = hyd_locale_find_text(locale, "options");
		text_pos.y += t.src.h + 5;
		hyd_text_draw(eng.renderer, t, text_pos);
		if (hyd_ui_btn(text_pos.x, text_pos.y, text_pos.x + t.src.w, text_pos.y + t.src.h)
				== hyd_btn_state.DOWN_L)
			writeln("options");

		t = hyd_locale_find_text(locale, "exit");
		text_pos.y += t.src.h + 5;
		hyd_text_draw(eng.renderer, t, text_pos);
		if (hyd_ui_btn(text_pos.x, text_pos.y, text_pos.x + t.src.w, text_pos.y + t.src.h)
				== hyd_btn_state.DOWN_L)
			eng.quit = true;
			*/
	}
}
