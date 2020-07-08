#include "navier-stokes/centered.h"
#include "two-phase.h"

#define MAX_LEVEL 7

double sep;

// e.g.
// $ flow 0.4 50
// Top 40% is occupied by a fluid with viscosity 50 times that of the bottom fluid.

int main (int argc, char *argv[]) {
  init_grid(1 << MAX_LEVEL);

  sep = atof(argv[1]); // where the interface is

  // Set up fluids. (doing this in init doesn't work)

  rho1 = 1.;
  mu1 = 1.;

  // Top fluid with parametrised viscosity
  rho2 = 1.;
  mu2 = atof(argv[2]);

  run();
}

event init(t = 0) {
  // flow out of the right -> into the left
  periodic(right);

  // the top is the 
  fraction (f, y-sep);

  // initially velocity is 0 everywhere
  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }
  
  // boundary conditions
  u.t[top] = dirichlet(1.);
  u.t[bottom] = dirichlet(0.);
}

// event animationU (t += 0.00001; t <= 0.005) {
//   view ();
//   clear();
//   squares ("u.x", spread = -1, linear = true, map = cool_warm );
//   draw_vof ("f", lc = {0.0,0.0,0.0}, lw=1);
//   // box();
//   save ("HorizontalVelocity.mp4");
// }

// event logfile (t += 0.00001; t <= 0.005) {
//   // compute the speed
//   scalar speed[]; 
//   foreach ()
//     // modulo floating point errors speed = u.x, but its cheating to assume that
//     speed[] = norm(u); // l2
//   // generate statistics
//   stats s = statsf(speed);

//   // log to file
//   FILE * fp = fopen("flow.log", "a");
//   fprintf (fp, "%g %d %g %g %g %g %g\n", t, i, dt, s.sum, s.max, s.min, interpolate(speed, 0., 0.3));
//   // last one is speed at interface
//   fclose(fp);
// }

event logfile (t = 1e+8) { // large t should approximate steady state solution.
  FILE * fp = fopen("flow.log", "a");
  fprintf (fp, "%g %g %g\n", sep, mu2, interpolate(u.x, 0., sep));
  fclose(fp);
}