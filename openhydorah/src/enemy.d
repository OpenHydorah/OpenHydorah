import hyd.entity;
import hyd.vector;
import hyd.animation;
import std.math;
import std.stdio;

import player;

class Enemy {
	hyd_ent *enemy;
	Player player;
	float speed;
	float health;
	bool dead = false;

	this (hyd_ent *e) {
		enemy = e;

		speed = hyd_ent_get_number_property(enemy, "speed");
	}
	
	void update (uint dt) {
		health = hyd_ent_get_number_property(enemy, "health");
		if (health <= 0) {
			if (!dead) {
				dead = true;
				enemy.prev.next = enemy.next;
				//enemy.next.prev = enemy.prev;
				//hyd_ent_destroy(enemy);
			}
			return;
		}
		enemy.pos.x -= speed * dt;
		//enemy.pos.y += dy * speed * dt;

		enemy.curr_frame = hyd_anim_get_next(enemy.curr_anim);
	}

	void draw() {
	}
}
