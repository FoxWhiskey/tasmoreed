#!/bin/bash
# replaces newlines with \n and escapes quotation marks with \"
#
# place the content of the output file into #PRECONFIGURED_SCRIPT
sed -e ':a;N;$!ba;s/\n/\\n/g' -e 's/\"/\\"/g' $1 > ./PRECONFIGURED_SCRIPT