import hyd.engine;
import hyd.entity;
import hyd.input;
import hyd.scene;
import hyd.layer;
import hyd.vector;
import std.stdio;

import weapon;

class Player {
	hyd_ent *player;
	float speed = 0;
	hyd_ip *curr_ip;
	Weapon wep_basic;

	this () {
		uint num = 0;
		hyd_ent **list = hyd_scene_find_ent_list(hyd_engine_get_scene(), "player", &num);
		if (num == 0)
			throw new Exception("Player not found");

		player = list[0];

		list = hyd_scene_find_ent_list(hyd_engine_get_scene(), "wep_basic", &num);
		if (num == 0)
			throw new Exception("wep_basic not found");

		wep_basic = new Weapon(list[0], hyd_ent_create_file("/entities/projectile.ent", null, player.layer), player);

		speed = hyd_ent_get_number_property(player, "speed");
	}

	void update (uint dt) {
		curr_ip = hyd_engine_get_ip();
		float left = cast(float)(hyd_ip_get_value(curr_ip, "left")) / cast(float)(hyd_input_get_max_value());
		float right = cast(float)(hyd_ip_get_value(curr_ip, "right")) / cast(float)(hyd_input_get_max_value());
		float up = cast(float)(hyd_ip_get_value(curr_ip, "up")) / cast(float)(hyd_input_get_max_value());
		float down = cast(float)(hyd_ip_get_value(curr_ip, "down")) / cast(float)(hyd_input_get_max_value());

		float fire = cast(float)(hyd_ip_get_value(curr_ip, "fire"));
		float noise_threshold = 0.25;
		
		if (left > -noise_threshold && left < noise_threshold)
			left = 0;
		if (right > -noise_threshold && right < noise_threshold)
			right = 0;
		if (up > -noise_threshold && up < noise_threshold)
			up = 0;
		if (down > -noise_threshold && down < noise_threshold)
			down = 0;

		float horizontal = right - left;
		float vertical = down - up;

		hyd_ent *l_i;
		for (l_i = player.layer.ent_head.next; l_i != player.layer.ent_head; l_i = l_i.next) {
			HYD_ENT_COLL coll = hyd_ent_coll(player, l_i);

			if (coll & HYD_ENT_COLL.LEFT)
				horizontal += left;
			if (coll & HYD_ENT_COLL.RIGHT)
				horizontal -= right;
			if (coll & HYD_ENT_COLL.TOP)
				vertical += up;
			if (coll & HYD_ENT_COLL.BOTTOM)
				vertical -= down;
		}

		player.pos.x += horizontal * speed * dt;
		player.pos.y += vertical * speed * dt;

		if (fire > 0)
			wep_basic.fire();
		wep_basic.update(dt);
	}

	void draw() {
		wep_basic.draw();
	}
}
