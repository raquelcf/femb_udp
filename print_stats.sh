#!/bin/sh

python get_data.py | tail -500 | awk {'print $2'} | perl -e 'use List::Util qw(max min sum); @a=();while(<>){$sqsum+=$_*$_; push(@a,$_)}; $n=@a;$s=sum(@a);$a=$s/@a;$m=max(@a);$mm=min(@a);$std=sqrt($sqsum/$n-($s/$n)*($s/$n));$mid=int @a/2;@srtd=sort @a;if(@a%2){$med=$srtd[$mid];}else{$med=($srtd[$mid-1]+$srtd[$mid])/2;};print "sum:\t$n\navg:\t$a\nstd:\t$std\n\med:\t$med\n\max:\t$m\min:\t$mm";'

#| head -3 | tail -1 | awk {'print $2'}`

