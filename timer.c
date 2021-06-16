#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

uv_timer_t timer;
uv_idle_t idler;
int cnt = 0;
int numberToBreakOn;

void timer_cb (uv_timer_t *handle) {
	if (cnt == numberToBreakOn) {
		uv_idle_stop (&idler);
		uv_timer_stop (handle);
	}else {
		cnt++;
	}
}

void idle_cb (uv_idle_t *handle) {
	system ("clear");

	if (cnt % 3 == 0) {
		printf ("\\");
	}else if (cnt % 3 == 1) {
		printf ("|");
	}else if (cnt % 3 == 2) {
		printf ("/");
	}
	printf (" > %d\n", cnt);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s >>No. for counter<<\n", argv[0]);
        return -1;
    }
	numberToBreakOn = atoi (argv [1]);

	uv_loop_t *loop = uv_default_loop();
	uv_loop_init (loop);

	uv_timer_init (loop, &timer);
	uv_idle_init (loop, &idler);

	uv_timer_start (&timer, timer_cb, 0, 100);
	uv_idle_start (&idler, idle_cb);

	uv_run (loop, UV_RUN_DEFAULT);
	uv_loop_close (loop);

	return 0;
}