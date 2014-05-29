#include "tests.h"
#include "entity.h"

START_TEST (test_entity)
{
	struct entity *ent = entity_create(NULL, "ent", NULL);
	struct entity *child = entity_create(NULL, "child", ent);

	ck_assert_str_eq(entity_get_name(ent), "ent");
	ck_assert_str_eq(entity_get_name(child), "child");
	ck_assert_ptr_eq(entity_get_parent(ent), NULL);
	ck_assert_ptr_eq(entity_get_parent(child), ent);

	entity_destroy(ent); // destroys 'child'
}
END_TEST

Suite *entity_suite(void)
{
	Suite *s = suite_create("Entity");

	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_entity);
	suite_add_tcase(s, tc_core);

	return s;
}
