use strict;

use warnings;

use diagnostics;

use feature 'say'; #print a new line after print

use feature "switch";

my %personal_Details;

sub display_details()
{

while(my($k,$v) = each %personal_Details)
{
    print("$k  ->  $v \n");
}
}

say "Enter your name : ";
my $name = <STDIN>;
chomp $name;

$personal_Details{'Name'} = $name ;

say "Enter your Age : ";
my $age  = <STDIN>;
chomp $age;

$personal_Details{'Age'} = $age;

say "Enter your City : ";
my $city  = <STDIN>;
chomp $city;
$personal_Details{'City'} = $city ;

say "Enter Street : ";
my $street  = <STDIN>;
chomp $street;
$personal_Details{'Street'} = $street ;


print "Enter the key whose value is to be updated : ";
my $key = <STDIN>;
chomp $key;
print "Enter the new value for key $key : ";
my $value = <STDIN>;
chomp $value;

$personal_Details{$key} = $value;

display_details();

print "Enter the key of the entry to be deleted : ";
my $del_key = <STDIN>;
chomp $del_key;
delete $personal_Details{$del_key};
display_details();