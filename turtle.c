/*
 * C backend to implement turtle graphics
 * Uses GnuPlot as the visualisation tool
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>


#include <libguile.h>

 /* 
  * Using standard Linux error code to indicate we ran to
  * a code path we shouldnt get to
  *
  * Internal software error is exit code 70 
  */

#define EX_SOFTWARE 70     


// Creating global constants WIDTH and HEIGHT for the gnuplot plot
static const int WIDTH = 10;
static const int HEIGHT = 10;

static FILE* global_gnuplot_input;

static double x, y;
static double direction;
static int pendown;

// Function with FILE* return type
static FILE* start_gnuplot()
{

  	FILE* to_gnuplot;

  	// pipe to communicate with gnuplot
  	int pipes[2];

  	// PID for the child process 
  	pid_t pid;


	// Creating the pipe
	if(pipe(pipes) < 0) {
		printf("Pipe creation failed\n");
		exit(1);
	}
  

	if((pid = fork()) < 0) {
		printf("Forking failed\n");
		exit(1);
	}


	// Child process 
  	if(pid == 0) {

		//dup2 forces the second argument to point to the same file as the first argument
		//pipes[0] is the read end of the created pipe
		//STDIN points to the same file
		//based on this if something was meant to read from STDIN it is now forced to read from the pipe
		//we are writing into the pipe from the parent process
		//basically pushing infoprmation to the child process which thinks it reads from STDIN
		dup2(pipes[0], STDIN_FILENO);

		//This substitutes the child process with gnuplot
		//From now on the child process is gnuplot
		//gnuplot reads from stdin started without arguments (NULL)
		//we forced the pipe end to act as stdin so we can write 
		//directly into gnuplot from the parent process
		execlp("gnuplot", NULL);


		/*
		 * If we reached this return that means gnuplot has terminated
		 * We don't intend to send quit command to it so this return should be never executer in the child process
		 */
		return EX_SOFTWARE;     
	}

  to_gnuplot = fdopen(pipes[1], "w");

  fprintf(to_gnuplot, "set multiplot\n");
  fprintf(to_gnuplot, "set parametric\n");
  fprintf(to_gnuplot, "set xrange [-%d:%d]\n", WIDTH, WIDTH);
  fprintf(to_gnuplot, "set yrange [-%d:%d]\n", HEIGHT, HEIGHT);
  fprintf(to_gnuplot, "set size ratio -1\n");
  fprintf(to_gnuplot, "unset xtics\n");
  fprintf(to_gnuplot, "unset ytics\n");
  fflush(to_gnuplot);

  return to_gnuplot;
}




static void draw_line(FILE* output, double x1, double y1, double x2, double y2) 
{
  	fprintf(output, "plot [0:1] %f + %f * t, %f + %f * t notitle\n",x1, x2 - x1, y1, y2 - y1);
  	fflush(output);
}



static void tortoise_reset()
{
  x = y = 0.0;
  direction = 0.0;
  pendown = 1;

  fprintf(global_gnuplot_input, "clear\n");
  fflush(global_gnuplot_input);
}

static void tortoise_pendown()
{
  pendown = 1;
}

static void tortoise_penup()
{
  pendown = 0;
}

static void tortoise_turn(double degrees)
{
  direction += M_PI / 180.0 * degrees;
}

static void tortoise_move(double length)
{
  double newX, newY;

  newX = x + length * cos (direction);
  newY = y + length * sin (direction);

  if (pendown)
    draw_line(global_gnuplot_input, x, y, newX, newY);

  x = newX;
  y = newY;
}


static void* register_functions(void* data)
{
  return NULL;
}



int main(int argc, char* argv[])
{


	int i;


	global_gnuplot_input = start_gnuplot ();

	tortoise_pendown (); /* This is unnecessary, but makes it clearer.  */
  	for (i = 1; i <= 4; ++i)
    	{
      		tortoise_move (3.0);
      		tortoise_turn (90.0);
    	}


	//scm_with_guile(&register_functions, NULL);
	//scm_shell(argc, argv);


	return EXIT_SUCCESS;
}










