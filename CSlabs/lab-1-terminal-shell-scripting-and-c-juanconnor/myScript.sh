#!/bin/sh

# Ansi exit codes for text color
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

# values for relevance distinction
oftenUsed="7" #1 week
sometimesUsed="30" #1 month
# rarely used > sometimesUsed


outputline=""
# loops through each file in the folder and determines whether the relevance of
# the file based on when the file was last read. Color codes the files based on distinction
for file in *
do

	# date of last read
	dateVal=$(stat -c %y $file)
	# current date
	curDate=$(date +"%Y-%m-%d %T")
	# discarding unneeded data
	linelength=$(expr length "$dateVal")
	desiredlength=$((linelength - 5))
	desiredline=$(echo $dateVal | cut -c1-30) #$desiredlength
	# dates converted to seconds	
	curDateSec=$(date +%s -d "$curDate")
	curHeldDate=$(date +%s -d "$desiredline")
	# how long ago the file was last read
	dateDiff=$(( (curDateSec - curHeldDate) / 86400 ))
	
	# printing the file and date of last read

	# often used
	if [ $dateDiff -le $oftenUsed ];
	then
		echo -e "${GREEN}$file $dateVal ${NC}"
	# sometimes used
	elif [ $dateDiff -le $sometimesUsed ]
	then
		echo -e "${YELLOW}$file $dateVal ${NC}"
	# rarely used
	else	
		echo -e "${RED}$file $dateVal ${NC}"
	fi

done


	


