#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 5;

Max72xxPanel matrix = Max72xxPanel(pinCS, 1, 1);

const int total_pixels_in_smiley = 25;
const int total_coordinates_per_pixel = 2;
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
    for (int pixel=0; pixel< total_pixels_in_smiley;pixel++)
      matrix.drawPixel(smiley[pixel][0], smiley[pixel][1], HIGH);

  matrix.write();
}

void loop() {
}

void animate_pixel() {

  matrix.fillScreen(LOW);
  for (int x_pixel_loc = 0; x_pixel_loc < 8; x_pixel_loc++)
  {
    matrix.drawPixel(x_pixel_loc, 3, HIGH);
    matrix.write();
    delay(20);
    matrix.drawPixel(x_pixel_loc, 3, LOW);
    matrix.write();
  }
  for (int x_pixel_loc = 7; x_pixel_loc > -1; x_pixel_loc--)
  {
    matrix.drawPixel(x_pixel_loc, 3, HIGH);
    matrix.write();
    delay(60);
    matrix.drawPixel(x_pixel_loc, 3, LOW);
    matrix.write();
  }
}
