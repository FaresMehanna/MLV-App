#include <stdint.h>
#include <stdlib.h>
#include <string.h>


/***************************** Blackbody stuff ********************************/

/* Planck's law, wavelength in meters, T in kelvin */
double Planck_law(double wavelength, double T)
{
    double c = 299792458; /* Speed of light */
    double h = 6.626070040 * pow(10,-34); /* Planck constant */
    double k = 1.38064852 * pow(10, -23); /* Boltzman constant */
    
    double E = (2*h*pow(c,2)) / pow(wavelength,5)
             * 1 / (exp((h*c)/(wavelength*k*T))-1);

    return E;
}

/* From http://www.cvrl.org/, 2006 colour matching functions */
static double xyz_match[] = {
390,2.952420E-03,4.076779E-04,1.318752E-02,
395,7.641137E-03,1.078166E-03,3.424588E-02,
400,1.879338E-02,2.589775E-03,8.508254E-02,
405,4.204986E-02,5.474207E-03,1.927065E-01,
410,8.277331E-02,1.041303E-02,3.832822E-01,
415,1.395127E-01,1.712968E-02,6.568187E-01,
420,2.077647E-01,2.576133E-02,9.933444E-01,
425,2.688989E-01,3.529554E-02,1.308674E+00,
430,3.281798E-01,4.698226E-02,1.624940E+00,
435,3.693084E-01,6.047429E-02,1.867751E+00,
440,4.026189E-01,7.468288E-02,2.075946E+00,
445,4.042529E-01,8.820537E-02,2.132574E+00,
450,3.932139E-01,1.039030E-01,2.128264E+00,
455,3.482214E-01,1.195389E-01,1.946651E+00,
460,3.013112E-01,1.414586E-01,1.768440E+00,
465,2.534221E-01,1.701373E-01,1.582342E+00,
470,1.914176E-01,1.999859E-01,1.310576E+00,
475,1.283167E-01,2.312426E-01,1.010952E+00,
480,7.593120E-02,2.682271E-01,7.516389E-01,
485,3.836770E-02,3.109438E-01,5.549619E-01,
490,1.400745E-02,3.554018E-01,3.978114E-01,
495,3.446810E-03,4.148227E-01,2.905816E-01,
500,5.652072E-03,4.780482E-01,2.078158E-01,
505,1.561956E-02,5.491344E-01,1.394643E-01,
510,3.778185E-02,6.248296E-01,8.852389E-02,
515,7.538941E-02,7.012292E-01,5.824484E-02,
520,1.201511E-01,7.788199E-01,3.784916E-02,
525,1.756832E-01,8.376358E-01,2.431375E-02,
530,2.380254E-01,8.829552E-01,1.539505E-02,
535,3.046991E-01,9.233858E-01,9.753000E-03,
540,3.841856E-01,9.665325E-01,6.083223E-03,
545,4.633109E-01,9.886887E-01,3.769336E-03,
550,5.374170E-01,9.907500E-01,2.323578E-03,
555,6.230892E-01,9.997775E-01,1.426627E-03,
560,7.123849E-01,9.944304E-01,8.779264E-04,
565,8.016277E-01,9.848127E-01,5.408385E-04,
570,8.933408E-01,9.640545E-01,3.342429E-04,
575,9.721304E-01,9.286495E-01,2.076129E-04,
580,1.034327E+00,8.775360E-01,1.298230E-04,
585,1.106886E+00,8.370838E-01,8.183954E-05,
590,1.147304E+00,7.869950E-01,5.207245E-05,
595,1.160477E+00,7.272309E-01,3.347499E-05,
600,1.148163E+00,6.629035E-01,2.175998E-05,
605,1.113846E+00,5.970375E-01,1.431231E-05,
610,1.048485E+00,5.282296E-01,9.530130E-06,
615,9.617111E-01,4.601308E-01,6.426776E-06,
620,8.629581E-01,3.950755E-01,0.000000E+00,
625,7.603498E-01,3.351794E-01,0.000000E+00,
630,6.413984E-01,2.751807E-01,0.000000E+00,
635,5.290979E-01,2.219564E-01,0.000000E+00,
640,4.323126E-01,1.776882E-01,0.000000E+00,
645,3.496358E-01,1.410203E-01,0.000000E+00,
650,2.714900E-01,1.083996E-01,0.000000E+00,
655,2.056507E-01,8.137687E-02,0.000000E+00,
660,1.538163E-01,6.033976E-02,0.000000E+00,
665,1.136072E-01,4.425383E-02,0.000000E+00,
670,8.281010E-02,3.211852E-02,0.000000E+00,
675,5.954815E-02,2.302574E-02,0.000000E+00,
680,4.221473E-02,1.628841E-02,0.000000E+00,
685,2.948752E-02,1.136106E-02,0.000000E+00,
690,2.025590E-02,7.797457E-03,0.000000E+00,
695,1.410230E-02,5.425391E-03,0.000000E+00,
700,9.816228E-03,3.776140E-03,0.000000E+00,
705,6.809147E-03,2.619372E-03,0.000000E+00,
710,4.666298E-03,1.795595E-03,0.000000E+00,
715,3.194041E-03,1.229980E-03,0.000000E+00,
720,2.205568E-03,8.499903E-04,0.000000E+00,
725,1.524672E-03,5.881375E-04,0.000000E+00,
730,1.061495E-03,4.098928E-04,0.000000E+00,
735,7.400120E-04,2.860718E-04,0.000000E+00,
740,5.153113E-04,1.994949E-04,0.000000E+00,
745,3.631969E-04,1.408466E-04,0.000000E+00,
750,2.556624E-04,9.931439E-05,0.000000E+00,
755,1.809649E-04,7.041878E-05,0.000000E+00,
760,1.287394E-04,5.018934E-05,0.000000E+00,
765,9.172477E-05,3.582218E-05,0.000000E+00,
770,6.577532E-05,2.573083E-05,0.000000E+00,
775,4.708916E-05,1.845353E-05,0.000000E+00,
780,3.407653E-05,1.337946E-05,0.000000E+00,
785,2.469630E-05,9.715798E-06,0.000000E+00,
790,1.794555E-05,7.074424E-06,0.000000E+00,
795,1.306345E-05,5.160948E-06,0.000000E+00,
800,9.565993E-06,3.788729E-06,0.000000E+00,
805,7.037621E-06,2.794625E-06,0.000000E+00,
810,5.166853E-06,2.057152E-06,0.000000E+00,
815,3.815429E-06,1.523114E-06,0.000000E+00,
820,2.837980E-06,1.135758E-06,0.000000E+00,
825,2.113325E-06,8.476168E-07,0.000000E+00,
830,1.579199E-06,6.345380E-07,0.000000E+00
};

/* Get colour of a blackbody emitter at temperature in Kelvin in XYZ. */
void BlackBody_to_XYZ(double temperature, double * XYZ_out)
{
    long double X = 0l, Y = 0l, Z = 0l;

    /* Calculate at 5nm intervals (as the colour match data is) */
    for (int w = 0; w < 88; ++w)
    {
        double wavelength = xyz_match[w*4];
        double radiation = Planck_law(temperature, wavelength/1000000000.0);
        X += radiation * xyz_match[w*4+1];
        Y += radiation * xyz_match[w*4+2];
        Z += radiation * xyz_match[w*4+3];
    }

    XYZ_out[0] = (double)(X/Y);
    XYZ_out[1] = (double)(Y/Y);
    XYZ_out[2] = (double)(Z/Y);
}


/*********************************** D curve **********************************/

void XYZ_to_xyY(double * XYZ, double * xyY)
{
    xyY[0] = XYZ[0] / (XYZ[0]+XYZ[1]+XYZ[2]);
    xyY[1] = XYZ[1] / (XYZ[0]+XYZ[1]+XYZ[2]);
    xyY[2] = XYZ[1];
}

void xyY_to_XYZ(double * xyY, double * XYZ)
{
    XYZ[0] = (xyY[0]*xyY[2]) / xyY[1];
    XYZ[1] = xyY[2];
    XYZ[2] = ((1.0-xyY[0]-xyY[1])*xyY[2]) / xyY[1];
}


/* Get Daylight curve illuminant for a temerature */
void Kelvin_Daylight_to_XYZ(double temperature, double * XYZ_out)
{
    double XYZ[3];
    double xyY[3];

    /* Generate colour of a pure blackbody at this temperature */
    BlackBody_to_XYZ(temperature, XYZ);

    /* Convert to xyY */
    XYZ_to_xyY(XYZ, xyY);

    /* Now that we know x for this temperature we can get correct y for D curve
     * https://en.wikipedia.org/wiki/Standard_illuminant#Illuminant_series_D */
    double y = 2.870*xyY[0] - 3.000*xyY[0]*xyY[0] - 0.275;

    /* Blend between original y coordinate and D between 3800-4300, as D value
     * is only valid above 4000 */
    double blend_fac = ((temperature-3800.0)/500.0);
    blend_fac = MAX(MIN(blend_fac, 1.0), 0.0);

    xyY[1] = xyY[1]*(1.0-blend_fac) + y*blend_fac;

    /* Now convert back to XYZ */
    xyY_to_XYZ(xyY, XYZ);

    /* return */
    for (int i = 0; i < 3; ++ i) XYZ_out[i] = XYZ[i];
}



void rgb2hsv(double * rgb_in, double * hsv_out)
{
    double      min, max, delta;

    min = rgb_in[0] < rgb_in[1] ? rgb_in[0] : rgb_in[1];
    min = min  < rgb_in[2] ? min  : rgb_in[2];

    max = rgb_in[0] > rgb_in[1] ? rgb_in[0] : rgb_in[1];
    max = max  > rgb_in[2] ? max  : rgb_in[2];

    hsv_out[2] = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        hsv_out[1] = 0;
        hsv_out[0] = 0; // undefined, maybe nan?
        return;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        hsv_out[1] = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        hsv_out[1] = 0.0;
        hsv_out[0] = 1;                            // its now undefined
        return;
    }
    if( rgb_in[0] >= max )                           // > is bogus, just keeps compilor happy
        hsv_out[0] = ( rgb_in[1] - rgb_in[2] ) / delta;        // between yellow & magenta
    else
    if( rgb_in[1] >= max )
        hsv_out[0] = 2.0 + ( rgb_in[2] - rgb_in[0] ) / delta;  // between cyan & yellow
    else
        hsv_out[0] = 4.0 + ( rgb_in[0] - rgb_in[1] ) / delta;  // between magenta & cyan

    hsv_out[0] *= 60.0;                              // degrees

    if( hsv_out[0] < 0.0 )
        hsv_out[0] += 360.0;

    return;
}


void hsv2rgb(double * hsv_in, double * out_rgb)
{
    double      hh, p, q, t, ff;
    long        i;

    if(hsv_in[1] <= 0.0000001) {       // < is bogus, just shuts up warnings
        out_rgb[0] = hsv_in[2];
        out_rgb[1] = hsv_in[2];
        out_rgb[2] = hsv_in[2];
        return;
    }

    hh = hsv_in[0];
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = hsv_in[2] * (1.0 - hsv_in[1]);
    q = hsv_in[2] * (1.0 - (hsv_in[1] * ff));
    t = hsv_in[2] * (1.0 - (hsv_in[1] * (1.0 - ff)));

    switch(i) {
    case 0:
        out_rgb[0] = hsv_in[2];
        out_rgb[1] = t;
        out_rgb[2] = p;
        break;
    case 1:
        out_rgb[0] = q;
        out_rgb[1] = hsv_in[2];
        out_rgb[2] = p;
        break;
    case 2:
        out_rgb[0] = p;
        out_rgb[1] = hsv_in[2];
        out_rgb[2] = t;
        break;

    case 3:
        out_rgb[0] = p;
        out_rgb[1] = q;
        out_rgb[2] = hsv_in[2];
        break;
    case 4:
        out_rgb[0] = t;
        out_rgb[1] = p;
        out_rgb[2] = hsv_in[2];
        break;
    case 5:
    default:
        out_rgb[0] = hsv_in[2];
        out_rgb[1] = p;
        out_rgb[2] = q;
        break;
    }
}