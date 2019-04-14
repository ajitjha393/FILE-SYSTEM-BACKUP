use strict;

use warnings;

use diagnostics;

use feature 'say'; #print a new line after print

use feature "switch";

#---Let us define stack of max size -----#

my @my_stack;

sub stack_Push{
    return push @my_stack , @_;    
}

sub stack_Pop{
    return pop @my_stack    
}
sub display{
    print join(", ",@my_stack),"\n";
}


stack_Push(2); display();
stack_Push(6);display();
stack_Push(5);display();
stack_Pop();display();
stack_Push(4);display();
stack_Pop();display();
