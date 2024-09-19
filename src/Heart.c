#include <math.h>
#include <stdio.h>
#include <unistd.h>

int main(){

	float t = 0;
	while (1) {

		printf("\x1b[2j\x1b[?25l");
		float zb[100 * 40] = {0};
		float maxz = 0, c = cos(t), s = sin(t);
		for (float y = -0.5; y <= 0.5f; y+= 0.01f){
			// Для ефекту сердцебиття;
			float r = 0.14f + 0.05f * pow(0.5f + 0.5f * sin(t * 6 + y * 2), 8);
			// float r = 0.14f;
			for (float x = -0.5; x <= 0.5f; x+= 0.01f){

				float z = -x * x - pow(1.2f * y - fabs(x) * 2 / 3, 2) + r;
				if (z < 0){
					continue;
				}
				z = sqrt(z) / (2 - y);
				for (float tz = -z; tz <= z; tz += z / 6){
					// Для повороту;
					float nx = x * c - tz * s;
					float nz = x * s + tz * c;

					// Для перспективи;
					float p = 1 + nx / 2;

					int vx = lroundf((nx * p + 0.5f) * 80 + 10);
					int vy = lroundf((-y * p + 0.5f) * 39 + 2);

					if (vx >= 0 && vx < 100 && vy >= 0 && vy < 40) {
						int idx = vx + vy * 100;
						if (zb[idx] <= nz){
							zb[idx] = nz;
							if (maxz <= nz){
								maxz = nz;
							}
						}
					}
				}
			}
		}

		printf("\x1b[H");
		 for (int i = 0; i < 100 * 40; i++){
			putchar(i % 100 ? " .,-~:;=!*#$@@" [lroundf(zb[i] / maxz * 13)] : 10);
			// putchar(i % 100 ? "@@$#*!=;:~-,. " [lroundf(zb[i] / maxz * 13)] : 10);
		}

		t += 0.003f;
		usleep(3000);
	}
	return 0;
}