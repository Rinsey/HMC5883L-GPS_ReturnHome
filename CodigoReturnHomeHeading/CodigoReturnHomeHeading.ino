
#include <Wire.h> //funcion para i2c
#include <HMC5883L.h> //funcion para el magnetometro

float clat=32.577806,clon=-115.434639; //AQUI PONES TUS COORDENADAS, O LA LECTURA DE TU GPS
float hlat=32.538741,hlon=-116.060092; //AQUI VAN LAS COORDENADAS OBJETIVO, A DONDE QUIERES IR jeje

/*
 * 
 *  Coordenadas de ejemplo: (Para que vean que no importa el cuadrante, funciona igual)
 *  FIM (CRODIT): 32.63223035579081, -115.44424512278857
 *  
 *  Cerro prieto: 32.417608, -115.308101
 *  Poblado de La Rumorosa 32.538741,-116.060092
 *  Sacramento, CA: 38.58157, -121.4944
 *  Osaka, JP: 34.69374, 135.50218.
 *  Lima, Perú: -12.04318, -77.02824
 * 
 * 
 */

HMC5883L compass;

void setup()
{
  Serial.begin(9600);

  Serial.println("Initialize HMC5883L");
  
  while (!compass.begin()){
    Serial.println("Checa si tu magnetometro esta conectado");
    delay(500);
  }

  compass.setRange(HMC5883L_RANGE_1_3GA);
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  compass.setDataRate(HMC5883L_DATARATE_30HZ);
  compass.setSamples(HMC5883L_SAMPLES_8);

  //CALIBRACION tuto: https://pirobotblog.wordpress.com/2017/01/25/using-a-hmc5883l-calibration/
  compass.setOffset(0, 0); //EN CASO DE QUE TU MAGNETOMETRO ESTE DESCALIBRADO ESTE ES UN HACK, no es muy fiable pero hace la chamba
  //
}

void loop()
{
  Vector norm = compass.readNormalize();

  // Calculamos la direccion a la que apunta nuestra brujula
  float heading = atan2(norm.YAxis, norm.XAxis);

  /*DECLINACION MAGNETICA QUE NO SE TE PASEEEEEEEEEEEEEEEEEEE
   * Esta parte es muy importante
   * es necesario añadir la declinacion magnetica
   * para aumentar la precision de nuestra brujula
   * float declinationAngle = (AQUI MODIFICAS GRADOS + (AQUI MODIFICAS MINUTOS / 60.0)) / (180 / M_PI);
   * En la siguiente pagina podemos sacar la declinacion
   * Se ve como --> Magnetic Declination: +10°(grados) 43'(minutos)
   * https://www.magnetic-declination.com/
   */
  float declinationAngle = (10.0 + (43.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;

  // Trabajaremos con angulos de 0 a 360 grados, es necesario para que los cuadrantes cuadren con la funcion atan2
  if (heading < 0){
    heading += 2 * PI;
  }
  if (heading > 2 * PI){
    heading -= 2 * PI;
  }

  // Pasamos el dato de la brujula a grados, recordemos que nos arrojan datos en RADIANES MUCHO CUIDADO!
  float headingDegrees = heading * 180/M_PI; 

  get_direction(clat,clon,hlat,hlon,headingDegrees); //VER PESTAÑA CALCULOS PARA SABER QUE ONDA

  delay(1000);
}
