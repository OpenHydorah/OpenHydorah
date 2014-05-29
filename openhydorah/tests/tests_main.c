#include "tests.h"

int main(int argc, char* argv[])
{
	int number_failed;

	Suite *list = list_suite();
	Suite *texture = texture_suite();
	Suite *entity = entity_suite();
	Suite *sprite = sprite_suite();

	SRunner* sr = srunner_create(list);
	srunner_add_suite(sr, texture);
	srunner_add_suite(sr, entity);
	srunner_add_suite(sr, sprite);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
