double* parseArguments(int argc, char* argv[], double* ret) {

  double xmin = -2;
  double xmax = 2;
  double ymin = -2;
  double ymax = 2;

  if(argc<=4) {
    printf("Not enugh Arguments Entered using default area. \n ");
    printf("x: %f to %f and y: %f to %f \n", xmin, xmax, ymin, ymax);
  }
  else {
    if (atof(argv[1]) < atof(argv[2])) {
      xmin = atof(argv[1]);
      xmax = atof(argv[2]);
    }
    else {
      printf("xMin: %f have to be smaler than xMax= %f", atof(argv[1]), atof(argv[2]));
    }

    if (atof(argv[3]) < atof(argv[4])) {
      ymin = atof(argv[3]);
      ymax = atof(argv[4]);
    }
    else {
      printf("yMin: %f have to be smaler than yMax= %f", atof(argv[3]), atof(argv[4]));
    }

    printf("x: %f to %f and y: %f to %f \n", xmin, xmax, ymin, ymax);
    // TODO Check if arguments is valid
    // That is min < max
  }

  ret[0] = xmin;
  ret[1] = xmax;
  ret[2] = ymin;
  ret[3] = ymax;

  return(ret);
}