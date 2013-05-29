/*
Based on code from
 - http://www.seeedstudio.com/wiki/images/4/43/Rainbowduino_for_Arduino1.0.zip
 - http://seeedstudio.com/wiki/Rainbowduino_v3.0
 
 Rainbowduino v3.0 Library examples : 3D Plasma

 * Updates made by: 
   19-May-2013: Fixed color gradient code and gradient traversal code.
   David Crook <david.crook@gmail.com>

*/

#include <Rainbowduino.h>


// HSV to RGB array generated using the following perl script

/*
#!/usr/bin/perl

# Dependencies:
# - Graphics::Color

# Ways to install
#
# (Debian)
# sudo apt-get install libgraphics-color-perl
# 
# (Perl cpanminus)
# sudo cpan App::cpanminus
# sudo /opt/local/libexec/perl5.12/sitebin/cpanm Graphics::Color
#  ^^ but this errored out before completing
#
# (Perl classic CPAN)
# sudo perl -MCPAN -e "shell"
# cpan> install Graphics::Color
#

#HSV2RGB.pl
use Graphics::Color::HSV;
use POSIX qw(ceil floor);

$red="";
$green="";
$blue="";

$SIZE_OF_GRADIENT = 2 ** 6;
$count = 0;

for($hu = 0.0; $hu <360.0 ; $hu=$hu+(360.0/$SIZE_OF_GRADIENT))
{
    $count = $count + 1;

    my $color = Graphics::Color::HSV->new({ hue => $hu, saturation  => 1, value  => 1,});
    $c = $color->to_rgb();
    $r = ceil($c->red * 255);
    $g = ceil($c->green * 255);
    $b = ceil($c->blue * 255);
    
    $red   .= $r . ',';
    $green .= $g . ',';
    $blue  .= $b . ',';

    warn ("count: $count {R,G,B} = { $r , $g , $b }\n");
}

print "unsigned char RED[64] = {$red};";
print "\n";
print "unsigned char GREEN[64] = {$green};";
print "\n";
print "unsigned char BLUE[64] = {$blue};";
print "\n";

if ($count != $SIZE_OF_GRADIENT) {
    warn "Error: miss-sized array on output\n";
}

*/

#define RANDOM_COLOR_JITTER 1

unsigned char RED[64] = {255,255,255,255,255,255,255,255,255,255,255,248,224,200,176,152,128,104,80,56,32,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,32,56,80,104,128,152,176,200,224,248,255,255,255,255,255,255,255,255,255,255,};
unsigned char GREEN[64] = {0,24,48,72,96,120,144,168,192,216,240,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,232,208,184,160,136,112,88,64,40,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
unsigned char BLUE[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,40,64,88,112,136,160,184,208,232,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,240,216,192,168,144,120,96,72,48,24,};

unsigned char grid[5][5][5];
unsigned char plasma[4][4][4];

float plasma_shift_distance = 1.9;


void setup()
{
  Rb.init(); //initialize Rainbowduino driver
  
  randomSeed(analogRead(0));

  /* Pre-compute the offset matrix for the cycling gradient. 
   *
   * - Start with a gradient function: In this example, we use a 5x5x5 (0->4) grid and compute the 
   *   Euclidean distance from a point chosen as the center ({2,2,2}).  This is similar to a spherical
   *   surface mapping.
   * - Once we have our  grid in the 5x5x5 space, use it to interpolate to a 
   *   4x4x4 array that matches the locations of the LED grid points
   *  
   */
  
  // use a spherical function, centered at offset {x,y,z} = {2,2,2} in a 5x5x5 grid
  // we'll interpolate it to a 4x4x4 mapping below
  for(unsigned char x = 0; x < 5; x++)
  {
    for(unsigned char y = 0; y < 5; y++)
    {
      for(unsigned char z = 0; z < 5; z++)
      {
        int center_distance = int( plasma_shift_distance * (sq(x-2) + sq(y-2) + sq(z-2)) );
        grid[x][y][z] = center_distance;      
      }   
    }
  }

  for(unsigned char x = 0; x < 4; x++)
  {
    for(unsigned char y = 0; y < 4; y++)
    {
      for(unsigned char z = 1; z < 5; z++)
      {
        // simple numerical mean interpolation function of the eight surrounding grid points
        plasma[x][y][z-1] =  1 / 8.0 * 
                ( grid[x  ][y  ][z  ] + grid[x+1][y  ][z  ] + 
                  grid[x  ][y+1][z  ] + grid[x+1][y+1][z  ] + 
                  grid[x  ][y  ][z-1] + grid[x+1][y  ][z-1] + 
                  grid[x  ][y+1][z-1] + grid[x+1][y+1][z-1] )  ;
       
        if (RANDOM_COLOR_JITTER) {
          plasma[x][y][z-1] +=  (int(random(10)) - 5);
        }

      }
    }
  } 
  
}

unsigned char x,y,z,colorshift=0;

void loop()
{
for(x=0;x<4;x++)  
{
 for(y=0;y<4;y++)  
 {
  for(z=0;z<4;z++)
    {
      int color = plasma[x][y][z];
      int index = color + colorshift;
     Rb.setPixelZXY(z,x,y, RED[index % 64], GREEN[index % 64], BLUE[index % 64]); //uses R, G and B color bytes
    }
 }
}
 delay(38);
 colorshift=  colorshift + 1;
}

