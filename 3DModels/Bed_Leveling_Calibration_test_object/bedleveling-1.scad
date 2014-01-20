/**
 * Print designed to check that you bed is level
 *
 * print four small squares in each corner to ensure even print quality and good adhesion.
 */

include <../lib/2d.scad>;

// Define your printers printable area
// If you are using Sprinter firmware then these come directly from configuration.h

X_MAX_LENGTH = 173;
Y_MAX_LENGTH = 163;

// This should be slightly less than your extruder width
border_width = 0.2;

// The height of each line. If your gcodes are empty increase this value.
height = .3;

inner_box_size = 20;
outer_box_size = min(X_MAX_LENGTH,Y_MAX_LENGTH) - 10;
box_difference = outer_box_size - inner_box_size;

gap = 10;



count = outer_box_size / (border_width + gap);

for ( i = [count - 2 : 1: count] )
{
	echo (i);
	echo((border_width + gap) * i);
	translate([((border_width + gap) * (count - i) )/2, ((border_width+ gap) * (count - i))/2, 0])
  	emptySquare(i * (border_width + gap), 1, height);
}

/*
translate ([10,10,0]) testSquare();
translate ([X_MAX_LENGTH - box_offset,10,0]) testSquare();
translate ([10,Y_MAX_LENGTH - box_offset,0]) testSquare();
translate ([X_MAX_LENGTH - box_offset,Y_MAX_LENGTH - box_offset,0]) testSquare();
*/
module testSquare()
{
	translate([box_difference/2,box_difference/2,0])
	cube([inner_box_size,inner_box_size,height]);
	
	
	difference() 
	{
		cube([outer_box_size,outer_box_size,height]);
		translate([border_width,border_width,0])
		cube([outer_box_size - (border_width * 2),outer_box_size - (border_width*2),height]);
	}

}