use strict;

use warnings;

use diagnostics;

use feature 'say'; #print a new line after print

print "Enter a string : ";
my $my_string = <STDIN>;
chomp $my_string;

if($my_string eq reverse $my_string)
{
    say "Entered String is Palindrome  \n";
}
else
{
    say "Entered String is not a Palindrome  \n";
}