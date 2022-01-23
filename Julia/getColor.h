//Max taken as arg instead
const uint16_t maxiter = 500;

        /* Old Color Scheme */
        //RGB
        //unsigned char color[6];
        //color[0] = k*3 >> 8;
        //color[1] = k*3 & 255;
        //color[2] = k*2 >> 8;
        //color[3] = k*2 & 255;
        //color[4] = k >> 8;
        //color[5] = k & 255;



int * getColorTree(int k){

  int * color = malloc(3*sizeof(int));

  if (k >= maxiter) {
    /* interior */
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
  }
  else{
    /* Exterior */
    int colorNum = k % 7;

    switch(colorNum){
        case 0:
            /* brown */
            color[0] = 86;
            color[1] = 70;
            color[2] = 25;
            break;
        case 1:
            /* brown */
            color[0] = 106;
            color[1] = 90;
            color[2] = 35;
            break;
        case 2:
            /* Dark Green */
            color[0] = 47;
            color[1] = 67;
            color[2] = 14;
            break;
        case 3:
            /* Light Yellow */
            color[0] = 244;
            color[1] = 243;
            color[2] = 14;
            break;
        case 4:
            /* Blue */
            color[0] = 8;
            color[1] = 13;
            color[2] = 38;
            break;
        case 5:
            /* Blue */
            color[0] = 28;
            color[1] = 48;
            color[2] = 44;
            break;
        case 6:
            /* Blue */
            color[0] = 48;
            color[1] = 58;
            color[2] = 54;
            break;
    }
  }
  return color;
}


int * getColor(int k){

  int * color = malloc(3*sizeof(int));

  if (k >= maxiter) {
    /* interior */
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
  }
  else{
    /* Exterior */
    int colorNum = k % 16;

    switch(colorNum){
        case 0:
            /* brown */
            color[0] = 66;
            color[1] = 30;
            color[2] = 15;
            break;
        case 1:
            /* Dark blue */
            color[0] = 25;
            color[1] = 7;
            color[2] = 26;
            break;
        case 2:
            /* Blue */
            color[0] = 9;
            color[1] = 1;
            color[2] = 47;
            break;
        case 3:
            /* Blue */
            color[0] = 4;
            color[1] = 4;
            color[2] = 73;
            break;
        case 4:
            /* Blue */
            color[0] = 0;
            color[1] = 7;
            color[2] = 100;
            break;
        case 5:
            /* Blue */
            color[0] = 12;
            color[1] = 44;
            color[2] = 138;
            break;
        case 6:
            /* Light Blue */
            color[0] = 24;
            color[1] = 82;
            color[2] = 177;
            break;
        case 7:
            /* Light Blue */
            color[0] = 57;
            color[1] = 125;
            color[2] = 209;
            break;
        case 8:
            /* Light Blue */
            color[0] = 134;
            color[1] = 181;
            color[2] = 229;
            break;
        case 9:
            /* Light Blue */
            color[0] = 211;
            color[1] = 236;
            color[2] = 248;
            break;
        case 10:
            /* Light Red */
            color[0] = 241;
            color[1] = 233;
            color[2] = 191;
            break;
        case 11:
            /* Orange */
            color[0] = 248;
            color[1] = 201;
            color[2] = 95;
            break;
        case 12:
            /* Orange */
            color[0] = 255;
            color[1] = 170;
            color[2] = 0;
            break;
        case 13:
            /* Orange */
            color[0] = 204;
            color[1] = 128;
            color[2] = 0;
            break;
        case 14:
            /* Orange Brown */
            color[0] = 153;
            color[1] = 87;
            color[2] = 0;
            break;
        case 15:
            /* Brown */
            color[0] = 106;
            color[1] = 52;
            color[2] = 3;
            break;
    }
  }
  return color;
}