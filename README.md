# Linjeföljanderobot - PI kontroller
En PI kontroller för att styra vår linjeföljande robot.
Roboten får signaler från sina sensorer och använder
dessa för att styra sina motorer.
## Algotitm
1. Läs värden från sensorerna (0 eller 1)
2. Använd värdena för att ge ett fel -1, 0, 1 där -1 är vänster och +1 är höger
3. Integrera felet
   1. Ta summan av alla fel
4. Multiplicera felet med en konstant och addera med integralen multiplicerad med en konstant
5. Det nya värdet ska ligga mellan -1 och 1
6. Översätt värdet till instruktioner för motorerna (-1 står vänstra motorn stilla o.s.v)
7. Börja om från 1
### Funktioner
1. En funktion som läser värden från sensorerna
   1. Behöver felhantera om båda sensorerna ger 1
   2. Översätt till -1, 0, 1
2. Integrera felet
   1. ta summan av alla felvärden
3. PI funktion (addera k*e + c*I) = -1<0<1
4. Kör motorerna (kör motorerna med ett värde mellan -1 och 1)