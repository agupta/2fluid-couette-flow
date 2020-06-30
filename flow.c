#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "view.h"

#define MAX_LEVEL 6

int main () {
  init_grid(1 << MAX_LEVEL);
  origin(-0.5, -0.5);

  // set up fluids, doing this in init doesn't work

  // Fluid 1 is water
  rho1 = 1.;
  mu1 = 1.;

  // Fluid 2 is oil
  rho2 = 0.9;
  mu2 = 56.2;

  run();
}

event init(t = 0) {
  // flow out of the right -> into the left
  periodic(right);

  // top 20% is oil
  fraction (f, 0.3 - y);

  // initially velocity is 0 everywhere
  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }
  
  // boundary conditions
  u.t[top] = dirichlet(1.);
  u.t[bottom] = dirichlet(0.);
}

event animationU (t += 0.00001; t <= 0.005) {
  view ();
  clear();
  squares ("u.x", spread = -1, linear = true, map = cool_warm );
  draw_vof ("f", lc = {0.0,0.0,0.0}, lw=1);
  // box();
  save ("HorizontalVelocity.mp4");
}

event logfile (t += 0.00001; t <= 0.005) {
  // compute the speed
  scalar speed[]; 
  foreach ()
    // modulo floating point errors speed = u.x, but its cheating to assume that
    speed[] = norm(u); // l2
  // generate statistics
  stats s = statsf(speed);

  // log to file
  FILE * fp = fopen("flow.log", "a");
  fprintf (fp, "%g %d %g %g %g %g %g\n", t, i, dt, s.sum, s.max, s.min, interpolate(speed, 0., 0.3));
  // last one is speed at interface
  fclose(fp);
}