
//Funcion para calcular la dirección a casa usando coordenadas actuales y coordenadas del punto de retorno
float calc_heading(float lat1, float lon1, float lat2, float lon2)
 {
   float a,c;
   float heading,diflon;
 
   lat1 = radians(lat1);
   lat2 = radians(lat2);              //Es recomendable trabajar en radianes, en esta parte convertimos latitudes.
   diflon = radians((lon2)-(lon1));   //Aqui la diferencia de longitudes en radianes.
   
   a = sin(diflon)*cos(lat2); //poquito de trigonometría :c todos los calculos los pueden comprobar en symbolab.
   c = cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(diflon);
   a = atan2(a,c); //Esta funcion nos ahorra el tener que identificar los cuadrantes :D
   
   heading = degrees(a); //Conversion a grados

   if(heading < 0){heading+=360; } //Queremos trabajar con angulos absolutos de 0 a 360 grados!!!!
   return heading; //mandamos lo que calculamos
 }

float calcular_distancia(float lat1, float lon1, float lat2, float lon2){//Esta funcion es para calcular la distancia entre los dos puntos
                                                                      
  float diflon,diflat,dist;
  float a,c;
  int radioTierra = 6371000;

  //Estoy utilizando la fórmula del Haversine! 
  diflat= radians((lat2)-(lat1));
  diflon = radians((lon2)-(lon1));   
  
  a = sq(sin(diflat/2))+cos(lat1)*cos(lat2)*sq(sin(diflon/2));
  c = 2*atan2(sqrt(a),sqrt(1-a));
  dist = c*radioTierra;
 
  return dist; //distancia entre los puntos 
}

void get_direction(float lat1, float lon1, float lat2, float lon2, float currentAngle){
  float heading = calc_heading(lat1,lon1,lat2,lon2);
  float distance = calcular_distancia(lat1,lon1,lat2,lon2);
     
     Serial.print("Angulo objetivo : "); Serial.print(heading,4);
     Serial.print("  Angulo brújula : "); Serial.print(currentAngle,4);
     Serial.print("  Diferencia en grados :"); Serial.print(abs(currentAngle-heading));
     Serial.print("  Distancia :"); Serial.println(distance);
}
