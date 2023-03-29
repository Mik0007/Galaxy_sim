#include "BMP_image_generator.h"
#include "Gravitazione.h"
#include "Custom_data_IO.h"
#include "Utility.h"
#include<ctime>
#include<omp.h>
using namespace std;

const int height = 1500;
const int width = 1500;


void bordini_bianchi(unsigned char image[height][width][BYTES_PER_PIXEL], 
	unsigned char image2[height][width][BYTES_PER_PIXEL])
{
	//mette i bordi alle immagini
    int i = 0;
    
    while (i < height)
	{
		image[i][0][0] = (unsigned char) 255;
		image[i][0][1] = (unsigned char) 255;
		image[i][0][2] = (unsigned char) 255;
		
		image2[i][0][0] = (unsigned char) 255;
		image2[i][0][1] = (unsigned char) 255;
		image2[i][0][2] = (unsigned char) 255;
		
		image[i][width-1][0] = (unsigned char) 255;
		image[i][width-1][1] = (unsigned char) 255;
		image[i][width-1][2] = (unsigned char) 255;
		
		image2[i][width-1][0] = (unsigned char) 255;
		image2[i][width-1][1] = (unsigned char) 255;
		image2[i][width-1][2] = (unsigned char) 255;
		
		i++;
	}
    
    i = 0;
    while (i < width)
	{
		image[0][i][0] = (unsigned char) 255;
		image[0][i][1] = (unsigned char) 255;
		image[0][i][2] = (unsigned char) 255;
		
		image2[0][i][0] = (unsigned char) 255;
		image2[0][i][1] = (unsigned char) 255;
		image2[0][i][2] = (unsigned char) 255;
		
		image[height-1][i][0] = (unsigned char) 255;
		image[height-1][i][1] = (unsigned char) 255;
		image[height-1][i][2] = (unsigned char) 255;
		
		image2[height-1][i][0] = (unsigned char) 255;
		image2[height-1][i][1] = (unsigned char) 255;
		image2[height-1][i][2] = (unsigned char) 255;
		
		image2[height/2][i][0] = (unsigned char) 255;
		image2[height/2][i][1] = (unsigned char) 255;
		image2[height/2][i][2] = (unsigned char) 255;
		
		i++;
	}
}

void update_images(unsigned char image[height][width][BYTES_PER_PIXEL], 
	unsigned char image2[height][width][BYTES_PER_PIXEL], float bounds[6],
	int totbodies, body3D* Galaxy, int T = 0, int N = 1)
{
	float scale = (bounds[1] - bounds[0])/height;
	float scale_z = (bounds[5] - bounds[4])/(height / 2);
    int x, y, z;
    
    for (int i = 0; i < totbodies; i++)
	{		
		x = (Galaxy[i].getpos()[0] / scale) - (bounds[0] / scale);
		y = (Galaxy[i].getpos()[1] / scale) - (bounds[2] / scale);
 		z = (Galaxy[i].getpos()[2] / scale_z) - (bounds[4] / scale_z);
		
	    if(not (x >= width || x < 0 || y >= height || y < 0)) 
		{
			// image xy
			image[y][x][0] = (unsigned char) 255;
			image[y][x][2] = (unsigned char) 255;
			image[y][x][1] = (unsigned char) 255 * T / N;
			
			if(not (z >= height/2 || z < 0 )) 
			{
				// image xz e yz
				image2[z][x][0] = (unsigned char) 255;
				image2[z][x][1] = (unsigned char) 255;
				image2[z +height/2][y][1] = (unsigned char) 255;
				image2[z +height/2][y][2] = (unsigned char) 255;
			
				image2[z][x][2] = (unsigned char) 255 * T / N;
				image2[z +height/2][y][0] = (unsigned char) 255 * T / N;
			}
		}
	}
}


void render_image(unsigned char image[height][width][BYTES_PER_PIXEL], 
	unsigned char image2[height][width][BYTES_PER_PIXEL], 
	float bounds[6])
{	
	//T -> counter, N -> steps da fare, 
	//skip -> steps che salta prima di scrivere su file,
	//servono tra un po'
    int T = 0;
    int N = 4001;
    int skip = 20;
    
	//Qui dichiaro un po' di cose
	float Time = 6*3600;
    int Num_bodies = 800;
    
	float massa = 1.2*pow(10, 26);
	float massatot = massa * Num_bodies;
	int totbodies = Num_bodies + 1;
    
    //Qui creo l'array e metto i dati della stella centrale
    body3D Galaxy[totbodies];	
    float pos[3] = {0,0,0};
    float Mb = 2*pow(10, 30);
    Galaxy[0].set_param(Mb, pos, pos, &Time);
    massatot += Mb;
    
    //Riempio l'array con dati random
    rand_normal_distribution(Galaxy, totbodies, massatot, massa, &Time);

	//Oppure con i dati già registrati
	//n del file da cui caricare i dati
    int load = 2000;
	//binary_import( "Data/Binary_Data/orbiting_data" + to_string(load) + ".dat" , 
	//				Galaxy, totbodies, massatot, massa, &Time, true);
	//T++;
    
    Galaxy[0].set_Cost(massa, Mb);
    
    //Piccolo recap
    cout << "\nPiccolo recap:" 
		 << "\nDimensioni immagine:\t" << height << " x " << width
    	 << "\nMassa stella centrale:\t" << Mb << " kg"
    	 << "\nMassa singoli corpi:\t" << massa << " kg"
    	 << "\nN corpi:\t\t" << Num_bodies
    	 << "\nMassa totale:\t\t" << massatot << " kg\n"
    	 << "\nDelta tempo:\t\t" << Time << " s"
    	 << "\nSteps totali:\t\t" << N
    	 << "\nTempo simulazione:\t" << N*Time << " s,\t\t" << N*Time / (3600*24) << " giorni,\n\t\t\t"
		 << N*Time / (3600*24*7) << " settimane,\t" << N*Time / (3600*24*366) << " anni\n";
    
	float N2 = N + (load * skip);
	cout << "\nTempo simulazione tot:\t" << N2*Time << " s,\t\t" << N2*Time / (3600*24) << " giorni,\n\t\t\t"
		 << N2*Time / (3600*24*7) << " settimane,\t" << N2*Time / (3600*24*366) << " anni\n";
    
    //mostro i punti iniziali
	update_images(image, image2, bounds, totbodies, Galaxy);
	
    filewriter pen("Data/Binary_Data/energy.dat", true);
    
    omp_set_num_threads(8);
    
    cout << "\nInizio dei calcoli...\n";
    
    //Questo serve per stimare il tempo rimanente
    clock_t timer0, timer;
    timer0 = clock();
    
    //Mo iniziano i calcoli pesanti
    while(T < N)
    {
    	//Calcolo le forze col corpo centrale
    	#pragma omp parallel for
    	for (int j = 1; j < totbodies; j++)
    		Galaxy[j].evaluate_force(&(Galaxy[0]), false);
    		
    	//Calcolo le forze tra tutti i corpi, a 2 a 2
    	#pragma omp parallel for
    	for (int i = 1; i < totbodies; i++)
    	{    		
    		for (int j = i+1; j < totbodies; j++)
    		{
				Galaxy[j].evaluate_force(&(Galaxy[i]), true);
			}
		}
    				
    	//Aggiorno le posizioni dei corpi
    	#pragma omp parallel for
	    for (int i = 0; i < totbodies; i++)
	    {
	    	Galaxy[i].update();
		}
	    
	    
	    //Mi fa vedere a che punto sono
	    if (T%150 == 0)
	    {
	    	timer = clock();
	    	float t = (timer - timer0) / CLOCKS_PER_SEC;
	    	float perc = 100*T/N;
	    	
	    	cout << "\nStatus:\t" << (int) perc << "%"
				 << "\n\tTempo trascorso: \t" << (int) t/60 << " min,\t" << (int) t%60 << " sec\n";
				 
			//t rimanente = ( t / T ) * (N - T) = t * ( (N - T)/T ) = t * ( (N/T) - 1 )
//			t *= (N - T)/T;
////			cout << "\n" << CLOCKS_PER_SEC;
//			cout << "\tTempo rimanente: \t" << (int) t/60 << " min,\t" << (int) t%60 << " sec\n";
//			cout << "\n" << evaluate_p_energy(Galaxy, totbodies) 
//				 << ", " << evaluate_k_energy(Galaxy, totbodies);
		}
		
		if (T%50 == 0)
		{
			#pragma omp parallel for
			for (int i = 1; i < totbodies; i++)
				Galaxy[i].update_polar_coord();
		}
			

    	
		if(T%skip == 0)
		{
			//Esporto le posizioni su un file binario
			binary_export(	"Data/Binary_Data/orbiting_data" + to_string((int) load + T/skip) + ".dat",
							Galaxy, totbodies);
			
			pen.en_write(evaluate_p_energy(Galaxy, totbodies), 
						 evaluate_k_energy(Galaxy, totbodies));
		}
		
		if(T%5 == 0)
		{
			//Stampo sulle immagini le posizioni
			update_images(image, image2, bounds, totbodies, Galaxy, T, N);
		}
			
		T++;
	}
	
	timer = clock();
	float t = (timer - timer0) / CLOCKS_PER_SEC;
	float perc = 100*T/N;
	
	cout << "\nTempo totale: \t" << (int) t/60 
		 << " min,\t" << (int) t%60 << " sec\n\n";
	
	pen.close();
	
	//Esporto le velocità finali su un file binario
	binary_export("Data/Binary_Data/vel_finali.dat", Galaxy, totbodies, true);
}

int main ()
{
	beginning: 
	
	cout << "Running...\n\n";
	
	//x_i, x_f, y_i, y_f, z_i, z_f
	float n = 2.2*pow(10, 12);
	float h = 6*pow(10, 10);
	float bounds[6] = {-n, n, -n, n, -h, h};
	
    //generating image
    static unsigned char image[height][width][BYTES_PER_PIXEL];
    char* imageFileName = (char*) "Data/Galaxy_xy_04.bmp";
    
    static unsigned char image2[height][width][BYTES_PER_PIXEL];
    char* imageFileName2 = (char*) "Data/Galaxy_z_04.bmp";
	
	bordini_bianchi(image, image2);
	
	render_image(image, image2, bounds);
    
    generateBitmapImage((unsigned char*) image, height, width, imageFileName);
    generateBitmapImage((unsigned char*) image2, height, width, imageFileName2);

    printf("\n\nImage generated!!\n\n");
    system("PAUSE");
    cout << "\n";
    goto beginning;
}


