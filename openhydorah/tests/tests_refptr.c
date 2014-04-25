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

#include "refptr.h"

void DestroyFunc(void* ptr)
{
	ck_assert_int_eq(*(int*)ptr, 10);
	free(ptr);
}

START_TEST (test_ref_counting)
	int a = 10;
	const int n = 10; // n should be greater than or equal 4
	RefPtr refs[n];
	RefPtr main = CreateRefPtr(&a, DestroyFunc);

	int i = 0;
	for (; i < n; i++)
	{
		refs[i] = CopyRefPtr(main);
	}

	ck_assert_int_eq(main->refSource->refCount, n+1);
	ck_assert_int_eq(refs[0]->refSource->refCount, n+1);

	DestroyRefPtr(&refs[n-1]);
	DestroyRefPtr(&refs[n-2]);
	DestroyRefPtr(&refs[n-3]);

	ck_assert_int_eq(main->refSource->refCount, n-2);
	ck_assert_int_eq(refs[0]->refSource->refCount, n-2);

END_TEST

START_TEST (test_ref_pointer)
	int* a = malloc(sizeof(int));
	*a = 10;
	RefPtr main = CreateRefPtr(a, DestroyFunc);
	RefPtr copy = CopyRefPtr(main);

	ck_assert_ptr_eq(main->ptr, copy->ptr);
	ck_assert_ptr_eq(main->ptr, main->refSource->ptr);
	ck_assert_ptr_eq(copy->ptr, copy->refSource->ptr);

	DestroyRefPtr(&copy);
	DestroyRefPtr(&main);
END_TEST

Suite* refptr_suite (void)
{
	Suite * s = suite_create ("RefPtr");

	TCase* tc_core = tcase_create ("Core");
	tcase_add_test(tc_core, test_ref_counting);
	tcase_add_test(tc_core, test_ref_pointer);
	suite_add_tcase(s, tc_core);

	return s;
}
