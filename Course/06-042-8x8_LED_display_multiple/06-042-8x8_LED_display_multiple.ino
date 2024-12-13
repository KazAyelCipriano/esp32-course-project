#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 5;
Max72xxPanel matrix = Max72xxPanel(pinCS, 4, 1);

const int total_pixels_in_smiley=25;
const int total_coordinates_per_pixel=2;
int smiley[total_pixels_in_smiley][total_coordinates_per_pixel] =
{
  {1, 0},
  {2, 0},
  {1, 1},
  {1, 2},
  {2, 1},
  {2, 2},
  {5, 0},
  {6, 0},
  {5, 1},
  {5, 2},
  {6, 1},
  {6, 2},
  {3, 1},
  {3, 2},
  {3, 3},
  {3, 4},
  {4, 4},
  {0, 5},
  {1, 6},
  {2, 7},
  {3, 7},
  {4, 7},
  {5, 7},
  {6, 6},
  {7, 5}
};

void setup() {
  matrix.setIntensity(4);
  matrix.fillScreen(LOW);
  matrix.setPosition(3, 0, 0);
  matrix.setPosition(2, 1, 0);
  matrix.setPosition(1, 2, 0);
  matrix.setPosition(0, 3, 0);
matrix.write();
}

void loop() {

}

void animate_letter(){
  matrix.fillScreen(LOW);

  for (int x_pixel_loc=0; x_pixel_loc<32; x_pixel_loc++)
{
  matrix.drawChar(x_pixel_loc, 0, 'A', HIGH, LOW, 1);
  matrix.write();
  delay(40);
  matrix.drawChar(x_pixel_loc, 0, 'A', LOW, LOW, 1);
  matrix.write();
}

for (int x_pixel_loc=31; x_pixel_loc>-1; x_pixel_loc--)
{
  matrix.drawChar(x_pixel_loc, 0, 'A', HIGH, LOW, 1);
  matrix.write();
  delay(40);
  matrix.drawChar(x_pixel_loc, 0, 'A', LOW, LOW, 1);
  matrix.write();
}
  
}
void animate_pixel(){
matrix.fillScreen(LOW);
for (int x_pixel_loc=0; x_pixel_loc<32; x_pixel_loc++)
{
  matrix.drawPixel(x_pixel_loc, 3, HIGH);
  matrix.write();
  delay(50);
  matrix.drawPixel(x_pixel_loc, 3, LOW);
  matrix.write();
}
for (int x_pixel_loc=31; x_pixel_loc>-1; x_pixel_loc--)
{
  matrix.drawPixel(x_pixel_loc, 3, HIGH);
  matrix.write();
  delay(50);
  matrix.drawPixel(x_pixel_loc, 3, LOW);
  matrix.write();
}
  

}