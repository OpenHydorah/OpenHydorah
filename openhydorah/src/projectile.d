import hyd.entity;
import hyd.engine;
import hyd.collision;
import hyd.vector;
import std.stdio;
import std.range;

class Projectile {
	hyd_ent *owner;
	hyd_ent *ent;
	uint s_delay = 3000;
	uint s_last = 0;
	float speed;
	float damage;
	bool past_delay = false;
	hyd_v2 direction;

	this (hyd_ent *e, hyd_ent *o, hyd_v2 dir) {
		ent = e;
		owner = o;
		direction = dir;
		speed = hyd_ent_get_number_property(e, "speed");
		if (speed == 0)
			writeln("Projectile's speed is 0");
		damage = hyd_ent_get_number_property(e, "damage");
		s_last = hyd_engine_get_time();
	}

	~this() {
		//hyd_ent_destroy(ent);
	}

	void update(uint dt) {
		if (collides())
			return;
		uint curr_time = hyd_engine_get_time();
		ent.pos.x += direction.x * speed * dt;
		ent.pos.y += direction.y * speed * dt;

		if ( curr_time - s_last >= s_delay) {
			s_last = curr_time;
			past_delay = true;
		}
	}

	void draw () {
		hyd_ent_draw(ent);
	}

	bool collides() {
		hyd_ent *l_i;
		for (l_i = ent.layer.ent_head.next; l_i != ent.layer.ent_head; l_i = l_i.next) {
			if (l_i == owner)
				continue;
			HYD_ENT_COLL coll = hyd_ent_coll(ent, l_i);

			if (coll != HYD_ENT_COLL.NONE) {
				past_delay = true;
				float h = hyd_ent_get_number_property(l_i, "health");
				hyd_ent_set_number_property(l_i, h - damage, "health");
				return true;
			}
		}
		return false;
	}
}
