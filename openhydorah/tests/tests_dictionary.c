/*
This file is part of OpenHydorah.

OpenHydorah is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenHydorah is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenHydorah.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "dictionary.h"

START_TEST (test_dictionary)
	Dictionary* dict = NULL;
	int value = 10;
	char* string = "tests";

	AddToDictionary(&dict, "test1", &value);
	AddToDictionary(&dict, "test2", string);

	ck_assert_int_eq(value, *(int*)GetFromDict(dict, "test1"));
	ck_assert_str_eq(string, (char*)GetFromDict(dict, "test2"));
END_TEST

Suite* dictionary_suite (void)
{
	Suite * s = suite_create ("Dictionary");

	TCase* tc_core = tcase_create ("Core");
	tcase_add_test(tc_core, test_dictionary);
	suite_add_tcase(s, tc_core);

	return s;
}
