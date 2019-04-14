use strict;

use warnings;

use diagnostics;

use feature 'say'; #print a new line after print

use feature "switch";

say <<"END";
1. ADD
2. SUB
3. MUl
4. DIV
5. MOD
6. POW
END

print "Enter a operation : ";
my $my_string = <STDIN>;
chomp $my_string;

given($my_string)
{
    when(1)
    {
        print "Enter  num 1  : ";
        my $num1 = <STDIN>;
        chomp $num1;
        print "Enter  num 2  : ";
        my $num2 = <STDIN>;
        chomp $num2;
        say "$num1 + $num2 = ",$num1 + $num2 ; 
    }
    when(2)
    {
        print "Enter  num 1  : ";
        my $num1 = <STDIN>;
        chomp $num1;
        print "Enter  num 2  : ";
        my $num2 = <STDIN>;
        chomp $num2;
        say "$num1 - $num2 = ",$num1 - $num2 ;
    }
    when(3)
    {
        print "Enter  num 1  : ";
        my $num1 = <STDIN>;
        chomp $num1;
        print "Enter  num 2  : ";
        my $num2 = <STDIN>;
        chomp $num2;
        say "$num1 * $num2 = ",$num1 * $num2 ;
    }
    when(4)
    {
        print "Enter  Numerator  : ";
        my $num1 = <STDIN>;
        chomp $num1;
        print "Enter  Denominator : ";
        my $num2 = <STDIN>;
        chomp $num2;
        say "$num1 / $num2 = ",$num1 / $num2 ;
    }
    when(5)
    {
        print "Enter  Numerator  : ";
        my $num1 = <STDIN>;
        chomp $num1;
        print "Enter  Denominator : ";
        my $num2 = <STDIN>;
        chomp $num2;
        say "$num1 % $num2 = ",$num1 % $num2 ;
    }
    when(6)
    {
        print "Enter  the Base : ";
        my $num1 = <STDIN>;
        chomp $num1;
        print "Enter  the Exponent : ";
        my $num2 = <STDIN>;
        chomp $num2;
        say "$num1 ^ $num2 = ",$num1 ** $num2 ;
    }
    default
    {say "Invalid input";}


}