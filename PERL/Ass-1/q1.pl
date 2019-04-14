use strict;

use warnings;

use diagnostics;

use feature 'say'; #print a new line after print


say "Enter a number : "; 
my $number =  <STDIN>;
chomp $number;

#---METHOD-1-----#

say "Using if else ---------> ";
if($number % 2 == 0)
{
    say "$number is an even number \n"; 
}
else 
{
    say "$number is an odd number \n";
}

#----METHOD-2------#

say "Using Unless --------->";
unless($number%2 == 0)
{
   say "$number is an odd number\n";
}
else
{
    say "$number is an even number \n";
}
