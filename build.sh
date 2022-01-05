
date=`date -I`


mkdir target/debug/$date
cp data target/debug/$date/data -r

gcc src/main.c -o target/debug/$date/Anbray -lm -lraylib -lpthread

./target/debug/$date/Anbray