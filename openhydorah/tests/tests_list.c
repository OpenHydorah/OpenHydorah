#include "tests.h"
#include "list.h"

struct test_struct {
	int data;
	struct list test_list;
};

START_TEST (test_list_create)
{
	struct test_struct test = {
		.data = 10
	};

	list_init(&test.test_list);
}
END_TEST

START_TEST (test_list_iterate)
{
	struct test_struct t1 = {
		.data = 10
	};

	struct test_struct t2 = {
		.data = 20
	};

	struct test_struct t3 = {
		.data = 30
	};

	list_init(&t1.test_list);
	list_init(&t2.test_list);
	list_init(&t3.test_list);

	struct list test_list;
	struct list test2_list;
	list_init(&test_list);
	list_init(&test2_list);

	list_append(&t1.test_list, &test_list);
	list_append(&t2.test_list, &test_list);

	int count = 0;
	struct list *iter;

	list_for_each(iter, &test_list)
	{
		count++;
	}

	ck_assert_int_eq(count, 2);
	struct test_struct *iter2;
	count = 0;

	list_for_each_entry(iter2, &test_list, test_list)
	{
		count += iter2->data;
	}

	ck_assert_int_eq(count, 30);

	list_append(&t1.test_list, &test2_list);
	list_append(&t3.test_list, &test2_list);
	count = 0;

	list_for_each_entry(iter2, &test2_list, test_list)
	{
		count += iter2->data;
	}

	ck_assert_int_eq(count, 40);
}
END_TEST

Suite *list_suite (void)
{
	Suite *s = suite_create("List");

	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_list_create);
	tcase_add_test(tc_core, test_list_iterate);
	suite_add_tcase(s, tc_core);

	return s;
}
