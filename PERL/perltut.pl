use strict;

use warnings;

use diagnostics;

use feature 'say'; #print a new line after print

use feature "switch";

#-----HASHES------------#

# Like dictionary

my %employees = (
    "Sue" => 35,
    "Sam" => 39,
    "Paul" => 43

);

printf("Sue is %d \n",$employees{Sue});
$employees{Frank} = 44;

while(my($k,$v) = each %employees)
{
    say "Key = $k Value = $v";
}