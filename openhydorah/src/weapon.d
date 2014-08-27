import hyd.entity;
import hyd.engine;
import hyd.vector;
import std.container;
import std.algorithm;
import std.range;
import std.stdio;
import std.math;

import projectile;

class Weapon {
	hyd_ent *ent;
	hyd_ent *proj_ent;
	hyd_ent *owner;
	DList!(Projectile) projectiles;
	uint last_shot = 0, shot_delay = 100;

	this (hyd_ent *e, hyd_ent *p, hyd_ent *o) {
		ent = e;
		proj_ent = p;
		owner = o;
		shot_delay = cast(uint)round(hyd_ent_get_number_property(ent, "delay"));
	}

	~this() {
	}

	void fire() {
		uint curr_time = hyd_engine_get_time();
		if (curr_time - last_shot >= shot_delay) {
			last_shot = curr_time;

			hyd_v2 dir = {1,0};
			Projectile p = new Projectile(hyd_ent_copy(proj_ent), owner, dir);
			p.ent.pos = hyd_ent_get_pos(ent);

			projectiles.insert(p);
		}
	}

	void update(uint dt) {
		for (auto r = projectiles[]; !r.empty; ) {
			auto p = r.front;
			p.update(dt);
			if (p.past_delay) {
				r = projectiles.linearRemove(r.take(1));
			}
			else
				r.popFront();
		}
	}

	void draw () {
		foreach (p; projectiles) {
			p.draw();
		}
	}
}
