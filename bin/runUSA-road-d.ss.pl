# ============================================================================
#  runUSA-road-d.ss.pl
# ============================================================================

#  Author(s)       (c) 2006 Camil Demetrescu, Andrew Goldberg
#  License:        See the end of this file for license information
#  Created:        Feb 15, 2006

#  Last changed:   $Date: 2006/10/30 08:09:39 $
#  Changed by:     $Author: demetres $
#  Revision:       $Revision: 1.3 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

#  USA-road-d family experiment driver
#  runs the ss solver on instances in the USA-road-d family

#  Usage: > perl runUSA-road-d.ss.pl
# ============================================================================

# param setup:
#$RESFILE   = "../bin/USA-road-d.ss.res";
$PREFIX    = "../data/USA-road-d";
$SOLVER    = "../bin/parallel.exe";
#$SOLVER    = "../bin/parallel-check.exe";
#$SOLVER    = "../bin/serial.exe";

$GRAPH     = "$PREFIX.%s.gr";
$AUX       = "$PREFIX.%s.ss";

# header:
print "\n* 9th DIMACS Implementation Challenge: Shortest Paths\n";
print   "* http://www.dis.uniroma1.it/~challenge9\n";
print   "* USA-road-d family ss core experiment\n";

# cleanup result file
#open FILE, ">$RESFILE" or die "Cannot open $RESFILE for write :$!";
#close FILE;

# generation subroutine
sub DORUN {

    # graph instance (e.g., CTR, BAY, etc.)
    $EXT = $_[0];

    $graphname = sprintf $GRAPH, $EXT;
    $auxname   = sprintf $AUX, $EXT;

    print "\n* Running ss solver on graph $graphname\n";

    # run experiment and collect stdout
    system ("../bin/parallel.exe","$EXT","d")
}

# run benchmark code
&DORUN("NY");
&DORUN("NE");
&DORUN("CTR");


# ============================================================================
# Copyright (C) 2006 Camil Demetrescu, Andrew Goldberg

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public
# License along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
# ============================================================================

