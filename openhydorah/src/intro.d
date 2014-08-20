import hyd.engine;
import hyd.texture;
import hyd.geom;

class Intro {
	hyd_tex *bg;
	hyd_engine *eng;

	this (hyd_engine *e) {
		eng = e;
		bg = hyd_tex_create_file("/graphics/backgrounds/intro_back.png");
		if (bg == null)
			throw new Exception("Failed to load intro_back.png");
	}

	~this () {
		hyd_tex_destroy(bg);
	}

	void draw () {
		SDL_Rect dest;
		dest.x = 0;
		dest.x = 0;
		dest.w = 600;
		dest.h = 480;
		//hyd_tex_draw(bg, eng.renderer, bg.size, dest);
	}
}
