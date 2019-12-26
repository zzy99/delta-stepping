# ============================================================================
#  genSources.pl
# ============================================================================

#  Author(s)       (c) 2005-2006 Camil Demetrescu, Andrew Goldberg
#  License:        See the end of this file for license information
#  Created:        Nov 11, 2005

#  Last changed:   $Date: 2006/02/16 20:53:42 $
#  Changed by:     $Author: demetres $
#  Revision:       $Revision: 1.3 $

#  9th DIMACS Implementation Challenge: Shortest Paths
#  http://www.dis.uniroma1.it/~challenge9

#  Generic random sources generator
#  Creates a suite of single-source shortest path
#  problem-specific auxiliary files.

#  Usage: > perl genSources.pl gr-file ss-file num-sources seed
# ============================================================================

# check arguments:
if (scalar(@ARGV) < 3) {
    print "Usage: > perl genSources.pl gr-file ss-file num-sources seed\n";
    exit;
}

# fetch arguments:
$grfile    = $ARGV[0];
$ssfile    = $ARGV[1];
$numsrc    = $ARGV[2];
$seed      = $ARGV[3];

# header:
print "\n* 9th DIMACS Implementation Challenge: Shortest Paths\n";
print   "* http://www.dis.uniroma1.it/~challenge9\n";
print   "* Generic random sources generator\n";

#init seed
srand ($seed);

# open graph file
open GRFILE, "$grfile" or die "Cannot open $grfile for read :$!";

print "\n>> Generating ss instances for graph $grfile\n";

# get number of nodes of the graph
$found = 0;
loop: while(<GRFILE>) {
    @line = split /\s/, $_;
    if ($line[0] eq "p") {
        $n = $line[2];
        $m = $line[3];
        $found = 1;
        last loop;
    }
}

close GRFILE;

if ($found == 0) {
    print "Error: graph does not contain a problem line\n";
    exit;
}

printf ">> Graph has %d nodes and %d arcs.\n", $n, $m;

printf ">> Generating file %s [seed %s] ...\n",$ssfile, $seed;

# open file in write mode
open FILE, ">$ssfile" or die "Cannot open $ssfile for write :$!";

# write file header
print FILE "c 9th DIMACS Implementation Challenge: Shortest Paths\n";
print FILE "c http://www.dis.uniroma1.it/~challenge9\n";
print FILE "c\n";
print FILE "c ss problem instance for a graph with $n nodes\n";
print FILE "c seed = $seed\n";
print FILE "p aux sp ss $numsrc\n";
print FILE "c file contains $numsrc source lines\n";
print FILE "c\n";

# write $numsrc random sources to the file
for ( $i = 0; $i < $numsrc; ++$i ) {
  $src = 1 + int(rand($n));            
  print FILE "s $src\n";
}

# close file
close FILE;


# ============================================================================
# Copyright (C) 2005-2006 Camil Demetrescu, Andrew Goldberg

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

