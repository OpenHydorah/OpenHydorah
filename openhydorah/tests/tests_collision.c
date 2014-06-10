#include "tests.h"
#include "collision.h"
#include <jansson.h>
#include <math.h>

json_t *create_json_obj(int *values, int num) {
	int json_ret;
	json_t *json_obj = json_object();
	json_t *json_points = json_array();
	json_t *json_point_iter;
	json_t *json_num_iter;
	size_t i;

	ck_assert_ptr_ne(json_obj, NULL);
	ck_assert_ptr_ne(json_points, NULL);

	for (i = 0; i < 8; i+=2) {
		json_point_iter = json_array();
		json_num_iter = json_integer(values[i]);

		ck_assert_ptr_ne(json_point_iter, NULL);
		ck_assert_ptr_ne(json_num_iter, NULL);

		json_ret = json_array_append_new(json_point_iter, json_num_iter);
		ck_assert_int_eq(json_ret, 0);
		json_num_iter = json_integer(values[i+1]);
		ck_assert_ptr_ne(json_num_iter, NULL);
		json_ret = json_array_append_new(json_point_iter, json_num_iter);
		ck_assert_int_eq(json_ret, 0);

		json_ret = json_array_append_new(json_points, json_point_iter);
		ck_assert_int_eq(json_ret, 0);
	}

	json_ret = json_object_set(json_obj, "points", json_points);
	ck_assert_int_eq(json_ret, 0);

	return json_obj;
}

START_TEST (test_collision_object)
{
	int values[] = {0,0, 0,2, 2,2, 2,0};
	int ex_area = 2 * 2, ex_radius = 1;
	int area, radius;
	float min, max;
	struct vec2 center;
	struct vec2 axis = {
		.x = 1.0f,
		.y = 0.0f
	};
	struct vec2 pos = {
		.x = 0.0f,
		.y = 0.0f
	};
	json_t *json_obj = create_json_obj(values, 8);
	struct collision_object *coll_obj;
	coll_obj = collision_object_create_json(json_obj, &pos);
	ck_assert_ptr_ne(coll_obj, NULL);

	area = abs(round(coll_obj->area));
	ck_assert_int_eq(ex_area, area);

	radius = round(coll_obj->radius);
	ck_assert_int_eq(ex_radius, radius);

	collision_object_project(coll_obj, axis, &min, &max);
	ck_assert_int_eq(round(min), 0);
	ck_assert_int_eq(round(max), 2);

	collision_object_destroy(coll_obj);
}
END_TEST

START_TEST (test_collision)
{
	struct collision_object *obj1, *obj2;
	struct collision *coll;
	json_t *json_obj;
	int values[] = {0,0, 0,2, 2,2, 2,0};
	struct vec2 pos = {
		.x = 0.0f,
		.y = 0.0f
	};

	json_obj = create_json_obj(values, 8);
	obj1 = collision_object_create_json(json_obj, &pos);
	obj2 = collision_object_create_json(json_obj, &pos);

	ck_assert_ptr_ne(obj1, NULL);
	ck_assert_ptr_ne(obj2, NULL);

	coll = collision_check(obj1, obj2, 0.0f, 0.0f);
	ck_assert_ptr_ne(coll, NULL);

	ck_assert_int_eq(collision_get_intersects(coll), 1);
	ck_assert_int_eq(collision_get_will_intersect(coll), 1);

	collision_destroy(coll);
	collision_object_destroy(obj1);
	collision_object_destroy(obj2);
}
END_TEST

Suite *collision_suite(void)
{
	Suite *s = suite_create("Collision");

	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_collision_object);
	tcase_add_test(tc_core, test_collision);
	suite_add_tcase(s, tc_core);

	return s;
}
