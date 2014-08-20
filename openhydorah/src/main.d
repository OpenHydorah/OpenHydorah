import hyd.engine;
import hyd.filesystem;
import hyd.input;
import hyd.entity;
import hyd.scene;
import hyd.collision;
import std.stdio;
import std.string;

import game;

void main() {
	try {
		Game game = new Game();
		game.init();

		game.run();

	} catch (Exception e) {
		writeln(e.msg);
	}
}
