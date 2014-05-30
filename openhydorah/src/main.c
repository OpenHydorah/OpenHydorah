#include "engine.h"
#include "property.h"
#include <stdio.h>

int main(int argc, const char *argv[])
{
	struct engine *engine = engine_create();
	if (engine == NULL)
		goto fail;

	if (engine_init(engine, argv) != 0)
		goto fail;

	if (engine_load_mod(engine, "mods/hydorah/libhydorah.so") != 0)
		goto fail;

	if (engine_run(engine) != 0)
		goto fail;

success:
	engine_destroy(engine);
	return 0;
fail:
	engine_destroy(engine);
	return 1;
}
