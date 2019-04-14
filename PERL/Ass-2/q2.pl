use strict;

use warnings;

use diagnostics;

use feature 'say'; #print a new line after print

use feature "switch";



my @my_queue;

sub queue_Enqueue{
    return push @my_queue , @_;    
}

sub queue_Dequeue{
    return shift @my_queue;    
}

sub display{
    print join(", ",@my_queue),"\n";
}

queue_Enqueue(2); display();
queue_Enqueue(6); display();
queue_Enqueue(5); display();
queue_Dequeue(); display();
queue_Enqueue(4); display();
queue_Dequeue(); display();

