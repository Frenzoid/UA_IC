#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <vector>
using namespace std;

struct pix
{
	unsigned char b, g, r;
} pixel;

vector<pix> pixelArray;

unsigned char Cabecera[54];
int b = *(int *)&Cabecera[18]; //

ifstream in;
ofstream out, out1;

int main(int argc, char *argv[])
{

	if (argc == 2)
	{
		string original = argv[1];
		string shadow = "shadowed_" + original;

		char infile[30];
		strcpy(infile, argv[1]);
		char outfile[30];
		strcpy(outfile, shadow.c_str());

		in.open(infile, ios::in | ios::binary);

		if (!in.is_open())		{
			cout << "ERROR: no se encuentra la imagen indicada" << endl;
			return 0;
		}

		in.read((char *)(&Cabecera), sizeof(Cabecera));
		out.open(outfile, ios::out | ios::binary);
		out.write((char *)(&Cabecera), sizeof(Cabecera));
		unsigned t0, t1;

		int width;
		memcpy(&width, &Cabecera[18], sizeof(width));
		cout << width << endl;

		int height;
		memcpy(&height, &Cabecera[22], sizeof(height));
		cout << height << endl;

		int h = 0;
		t0 = clock();

		while (!in.eof())
		{
			in.read((char *)(&pixel), sizeof(pixel));
			pixelArray.push_back(pixel);
			h++;
		}

		int fila = 0;
		int columna = 0;

		for (int i = 0; i <= h; i++)
		{
			pixel = pixelArray[i];

			fila = i / width;
			columna = i - (fila * width);

			cout << "columna: " << columna << "fila: " << fila << endl;

			if (fila == 0 && columna == 0)
			{
				pixel.r = (pixel.r + pixelArray[i + 1].r + pixelArray[i + width].r + pixelArray[i + width + 1].r) / 4;
				pixel.b = (pixel.b + pixelArray[i + 1].b + pixelArray[i + width].b + pixelArray[i + width + 1].b) / 4;
				pixel.g = (pixel.g + pixelArray[i + 1].g + pixelArray[i + width].g + pixelArray[i + width + 1].g) / 4;
			}
			else if (fila == 0 && columna == width)
			{

				pixel.r = (pixel.r + pixelArray[i - 1].r + pixelArray[i + width].r + pixelArray[i + width - 1].r) / 4;
				pixel.b = (pixel.b + pixelArray[i - 1].b + pixelArray[i + width].b + pixelArray[i + width - 1].b) / 4;
				pixel.g = (pixel.g + pixelArray[i - 1].g + pixelArray[i + width].g + pixelArray[i + width - 1].g) / 4;
			}
			else if (fila == height && columna == 0)
			{

				pixel.r = (pixel.r + pixelArray[i + 1].r + pixelArray[i - width].r + pixelArray[i + width + 1].r) / 4;
				pixel.b = (pixel.b + pixelArray[i + 1].b + pixelArray[i - width].b + pixelArray[i + width + 1].b) / 4;
				pixel.g = (pixel.g + pixelArray[i + 1].g + pixelArray[i - width].g + pixelArray[i + width + 1].g) / 4;
			}
			else if (fila == height && columna == width)
			{

				pixel.r = (pixel.r + pixelArray[i - 1].r + pixelArray[i - width].r + pixelArray[i - width - 1].r) / 4;
				pixel.b = (pixel.b + pixelArray[i - 1].b + pixelArray[i - width].b + pixelArray[i - width - 1].b) / 4;
				pixel.g = (pixel.g + pixelArray[i - 1].g + pixelArray[i - width].g + pixelArray[i - width - 1].g) / 4;
			}
			else if (fila == 0)
			{
				pixel.r = (pixel.r + pixelArray[i - 1].r + pixelArray[i + 1].r + pixelArray[i + width].r + pixelArray[i + width - 1].r + pixelArray[i + width + 1].r) / 6;
				pixel.g = (pixel.g + pixelArray[i - 1].g + pixelArray[i + 1].g + pixelArray[i + width].g + pixelArray[i + width - 1].g + pixelArray[i + width + 1].g) / 6;
				pixel.b = (pixel.b + pixelArray[i - 1].b + pixelArray[i + 1].b + pixelArray[i + width].b + pixelArray[i + width - 1].b + pixelArray[i + width + 1].b) / 6;
			}
			else if (fila == height)
			{
				pixel.r = (pixel.r + pixelArray[i - 1].r + pixelArray[i + 1].r + pixelArray[i - width].r + pixelArray[i - width - 1].r + pixelArray[i - width + 1].r) / 6;
				pixel.g = (pixel.g + pixelArray[i - 1].g + pixelArray[i + 1].g + pixelArray[i - width].g + pixelArray[i - width - 1].g + pixelArray[i - width + 1].g) / 6;
				pixel.b = (pixel.b + pixelArray[i - 1].b + pixelArray[i + 1].b + pixelArray[i - width].b + pixelArray[i - width - 1].b + pixelArray[i - width + 1].b) / 6;
			}
			else if (columna == 0)
			{
				pixel.r = (pixel.r + pixelArray[i + 1].r + pixelArray[i - width].r + pixelArray[i + width].r + pixelArray[i - width + 1].r + pixelArray[i + width + 1].r) / 6;
				pixel.g = (pixel.g + pixelArray[i + 1].g + pixelArray[i - width].g + pixelArray[i + width].g + pixelArray[i - width + 1].g + pixelArray[i + width + 1].g) / 6;
				pixel.b = (pixel.b + pixelArray[i + 1].b + pixelArray[i - width].b + pixelArray[i + width].b + pixelArray[i - width + 1].b + pixelArray[i + width + 1].b) / 6;
			}
			else if (columna == width)
			{
				pixel.r = (pixel.r + pixelArray[i - 1].r + pixelArray[i - width].r + pixelArray[i + width].r + pixelArray[i - width - 1].r + pixelArray[i + width - 1].r) / 6;
				pixel.g = (pixel.g + pixelArray[i - 1].g + pixelArray[i - width].g + pixelArray[i + width].g + pixelArray[i - width - 1].g + pixelArray[i + width - 1].g) / 6;
				pixel.b = (pixel.b + pixelArray[i - 1].b + pixelArray[i - width].b + pixelArray[i + width].b + pixelArray[i - width - 1].b + pixelArray[i + width - 1].b) / 6;
			}
			else
			{
				pixel.r = (pixel.r + pixelArray[i - 1].r + pixelArray[i + 1].r + pixelArray[i - width].r + pixelArray[i + width].r + pixelArray[i - width - 1].r + pixelArray[i + width - 1].r + pixelArray[i - width + 1].r + pixelArray[i + width + 1].r) / 9;
				pixel.g = (pixel.g + pixelArray[i - 1].g + pixelArray[i + 1].g + pixelArray[i - width].g + pixelArray[i + width].g + pixelArray[i - width - 1].g + pixelArray[i + width - 1].g + pixelArray[i - width + 1].g + pixelArray[i + width + 1].g) / 9;
				pixel.b = (pixel.b + pixelArray[i - 1].b + pixelArray[i + 1].b + pixelArray[i - width].b + pixelArray[i + width].b + pixelArray[i - width - 1].b + pixelArray[i + width - 1].b + pixelArray[i - width + 1].b + pixelArray[i + width + 1].b) / 9;
			}


			out.write((char *)(&pixel), sizeof(pixel));
		}

        t1 = clock();

		double time = (double(t1 - t0) / CLOCKS_PER_SEC);
		cout << "Tiempo total: " << time << endl;

		in.close();
		out.close();
	}
	else
	{
		cout << "ERROR: argumentos incorrectos." << endl;
        cout << "USO: ./difuminador 'imagen.bmp'" << endl;
	}
}