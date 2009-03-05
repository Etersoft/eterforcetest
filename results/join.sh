#!/bin/sh
echo "Test name     Linux result   Windows result" > Cong.log
join Lin_eterforcetest.log Win_eterforcetest.log | dos2unix -U >> Cong.log
