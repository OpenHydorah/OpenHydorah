#include "tests.h"
#include "property.h"

START_TEST (test_property_number)
{
	struct property *p = property_create_number(1.0f, "p");

	ck_assert_str_eq(p->name, "p");
	ck_assert_int_eq((int)p->value.n, 1);

	property_destroy(p);
}
END_TEST

START_TEST (test_property_bool)
{
	struct property *p = property_create_bool(1, "p");

	ck_assert_str_eq(p->name, "p");
	ck_assert_int_eq(p->value.b, 1);

	property_destroy(p);
}
END_TEST

START_TEST (test_property_string)
{
	struct property *p = property_create_string("value", "p");

	ck_assert_str_eq(p->name, "p");
	ck_assert_str_eq(p->value.s, "value");

	property_destroy(p);
}
END_TEST

Suite *property_suite(void)
{
	Suite *s = suite_create("Property");

	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_property_number);
	tcase_add_test(tc_core, test_property_bool);
	tcase_add_test(tc_core, test_property_string);
	suite_add_tcase(s, tc_core);

	return s;
}
