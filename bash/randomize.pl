#! /usr/bin/perl

# Time-stamp: <2001-07-25 12:43:12 ccurley randomize>

# randomize: a perl script to take stdin input, randomize it, and ship
# it out stdout. Suitable for shell scripts. Auto-detect and handle 0
# delimited arguments.

# Copyright 2003 through the last date of modification Charles Curley
# except for the subroutine fisher_yates_shuffle. fisher_yates_shuffle
# Copyright (c) 1998 Tom Christiansen, Nathan Torkington and O'Reilly
# & Associates, Inc.

# This program is free software; you can redistribute it and/or modify
# it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.

# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License
# along
# with this program; if not, write to the Free Software Foundation,
# Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

# You can also contact the Free Software Foundation at
# http://www.fsf.org/

# For more information contact the author, Charles Curley, at
# http://www.charlescurley.com/.

# I wrote this so I could use ImageMagick's display program to set my
# root window every so often with one of several images, chosen at
# random. The key line of the script looks like this:

# find <path> -iname "*.jpg" -print0 | randomize | xargs -0 display
# -delay 60000 -window root

# fisher_yates_shuffle ( \@array ) : generate a random
# permutation. From Perl Cookbook, Christiansen & Torkington,
# O'Reilly, 1999, page 122.

sub fisher_yates_shuffle {
	    my $array = shift;
	        my $i;
		    for ($i = @$array; --$i; ) {
			            my $j = int rand ($i+1);
				            next if $i == $j;
					            @$array[$i,$j] = @$array[$j,$i];
						        }
}

while (<STDIN>) {
	    chomp;
	        push (@array, $_);
}


# If the size of the array is one, then we have one line, presumably 0
# delimited. ($#array returns the last valid index, not the size. perl
# being 0 based, the size is one larger.) You produce this with find
# by using the -print0 option. It's good for file and directory names
# with (ugh) spaces in them.

if ($#array == 0) {
	    $string = @array[0];
	        @array = split (/\0/,$string);
		    $zeros = 1;
}


fisher_yates_shuffle (\@array);

# If the input was zero-delimited, the output will be also. Use "xargs
# -0" to further process the results.

if ($zeros) {
	    $string = join ("\0", @array);
	        print "$string\n";
} else {
	    foreach $item (@array) {
		            print "$item\n";
			        }
}

