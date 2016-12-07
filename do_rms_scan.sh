#!/bin/bash

FILE="rmsdata.txt"
if [ -f $FILE ]; then 
    rm $FILE
fi 

for i in {0..7}; do
  echo "Processing ASIC" ${i}"..."

  for j in {0..15}; do
    python select_channel.py ${i} ${j} 1 >/dev/null;

    list=""
    for k in {1..100}; do
        chanstats=`python get_data.py | tail -500 | awk {'print $2'} | perl -e 'use List::Util qw(max min sum); @a=();while(<>){$sqsum+=$_*$_; push(@a,$_)}; $n=@a;$s=sum(@a);$a=$s/@a;$m=max(@a);$mm=min(@a);$std=sqrt($sqsum/$n-($s/$n)*($s/$n));$mid=int @a/2;@srtd=sort @a;if(@a%2){$med=$srtd[$mid];}else{$med=($srtd[$mid-1]+$srtd[$mid])/2;};print "sum:\t$s\navg:\t$a\nstd:\t$std\n\med:\t$med\n\max:\t$m\min:\t$mm";'`
        list="${list}
    `echo ${chanstats} | awk {'print $6'}`"
    done
    
    rmsstats=`echo "${list}" | tail -100 | perl -e 'use List::Util qw(max min sum); @a=();while(<>){$sqsum+=$_*$_; push(@a,$_)}; $n=@a;$s=sum(@a);$a=$s/@a;$m=max(@a);$mm=min(@a);$std=sqrt($sqsum/$n-($s/$n)*($s/$n));$mid=int @a/2;@srtd=sort @a;if(@a%2){$med=$srtd[$mid];}else{$med=($srtd[$mid-1]+$srtd[$mid])/2;};print "sum:\t$s\navg:\t$a\nstd:\t$std\n\med:\t$med\n\max:\t$m\min:\t$mm";'`
    echo ${i} ${j} `echo ${rmsstats} | awk {'print $4'}` `echo ${rmsstats} | awk {'print $6'}` >> $FILE
  done
done
