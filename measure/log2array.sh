#!/bin/sh
FILEOUT=etalon_measure.c
echo "struct { char *name; int ms; int res; } et_measure[] = {" > $FILEOUT
cat eterforcetest.log | dos2unix -U | \
while read a b c; do
	echo "{ \"$a\", ${b} }," >>$FILEOUT
done
echo "{ 0, 0 }" >>$FILEOUT
echo "};" >>$FILEOUT
