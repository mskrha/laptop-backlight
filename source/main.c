#include <stdio.h>

#define	CUR	"/sys/class/backlight/intel_backlight/actual_brightness"
#define	MAX	"/sys/class/backlight/intel_backlight/max_brightness"

int get(char *name) {
	int v;
	FILE *f;

	f = fopen(name, "r");
	if (f == NULL) {
		perror("fopen");
		return -1;
	}

	if (fscanf(f, "%d", &v) != 1) {
		perror("fscanf");
		fclose(f);
		return -1;
	}

	fclose(f);

	return v;
}

int main(int argc, char **argv) {
	int c, m;

	c = get(CUR);
	if (c < 0) {
		return -1;
	}

	m = get(MAX);
	if (m < 0) {
		return -1;
	}

	printf("%d%%\n", c * 100 / m);

	return 0;
}
