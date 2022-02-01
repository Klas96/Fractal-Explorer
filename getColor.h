//Max taken as arg instead
const uint16_t maxiter = 500;


// ICE and FIRE Pallet
int * getColorIceFireTheme(int k){

  int * color = malloc(3*sizeof(int));

  if (k >= maxiter) {
    /* interior */
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
  }
  else{
    /* Exterior */
    int colorNum = k % 10;

    switch(colorNum){
        case 0:
            /* Red */
            color[0] = 255;
            color[1] = 70;
            color[2] = 59;
            break;
        case 1:
            /* Red */
            color[0] = 255;
            color[1] = 0;
            color[2] = 59;
            break;
        case 2:
            color[0] = 255;
            color[1] = 50;
            color[2] = 79;
            /* Light Brown */
            //color[0] = 206;
            //color[1] = 191;
            //color[2] = 135;
            break;
        case 3:
            /* brown */
            color[0] = 237;
            color[1] = 135;
            color[2] = 91;
            //color[0] = 35;
            //color[1] = 1;
            //color[2] = 14;
            break;
        case 4:
            /* Light Greey */

            color[0] = 245;
            color[1] = 150;
            color[2] = 99;
            //color[0] = 255;
            //color[1] = 0;
            //color[2] = 59;
            //color[0] = 197;
            //color[1] = 196;
            //color[2] = 157;
            break;
        case 5:
            /* Light Yellow */

            color[0] = 255;
            color[1] = 0;
            color[2] = 59;
            //color[0] = 255;
            //color[1] = 0;
            //color[2] = 59;
            //color[0] = 161;
            //color[1] = 162;
            //color[2] = 186;
            break;
        case 6:
            /* Dark Green */
            color[0] = 139;
            color[1] = 116;
            color[2] = 207;
            break;
        case 7:
            /* brown */
            color[0] = 69;
            color[1] = 52;
            color[2] = 125;
            break;
        case 8:
            /* brown */
            color[0] = 90;
            color[1] = 54;
            color[2] = 175;
            break;
        case 9:
            /* brown */
            color[0] = 121;
            color[1] = 117;
            color[2] = 181;
            break;
    }
  }
  return color;
}





int * getColorTreeTheme(int k){

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

//Wikipedia Pallet
int * getColorWikiTheme(int k){

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

int * getColor(int k) {

    int * color = malloc(3*sizeof(int));

    switch (7) {
        case 1:
            color = getColorTreeTheme(k);
            break;

        case 2:
            color = getColorIceFireTheme(k);
            break;

        case 3:
            color = getColorTreeTheme(k);
            break;

        default:
            color = getColorWikiTheme(k);
    }

    return color;
}