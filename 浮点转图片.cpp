#include <iostream>
#include <cmath>
#include <cstdlib>

#define DIM 1000

void pixel_write(int,int);
FILE *fp;

int main()
{
    fp = fopen("image.ppm","wb");
    if (!fp)
    {
        return -1;
    }

    fprintf(fp, "P6\n%d %d\n255\n", DIM, DIM);
    for(int j=0;j<DIM;j++)
    {
        for(int i=0;i<DIM;i++)
        {
            pixel_write(i,j);
        }
    }
    fclose(fp);

    return 0;
}

void pixel_write(int i, int j)
{
    static unsigned char color[3];
    float t = j + i*0.001f;
    memcpy(color, &t, 3);
    fwrite(color, 1, 3, fp);

    // 其实更简单粗爆的方式是
     //fwrite(&t, 1, 3, fp);
}