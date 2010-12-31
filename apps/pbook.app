#!/bin/bash
#I was very lazy while writing this
list=`echo $SENTTEXT | cut -d ' ' -f 1`
name=`echo $SENTTEXT | cut -d ' ' -f 2`
nick=`echo $SENTTEXT | cut -d ' ' -f 3`
res='/home/blacktooth/code/smsbot/apps/res/'
listfile='/home/blacktooth/code/smsbot/apps/res/pblist'

JSON_encode ()
{
	JSON_string=`echo { \"sendto\": \"$1\", \"sendwhat\": \"$2\" }`
	echo $JSON_string
}

MSG_INVALID="Please mention a valid list, ADDME b5 <Name> <Nick>"
MSG_USER_EXISTS="Hey $nick! You are already in!"
MSG_WELCOME="Hello $nick! Your contact has been successfully added to the list."
if [ `cat $listfile | grep -i "$list"` ] 
	then
		if [ `cat $res$list.cl | grep "$SENTFROM"` ]
			then
				JSON_encode $SENTFROM "$MSG_USER_EXISTS"
				exit 0
		fi	
				
				
		echo $name::$nick::$SENTFROM >> $res$list.cl
		JSON_encode $SENTFROM "$MSG_WELCOME"
		exit 0
	else
		JSON_encode $SENTFROM "$MSG_INVALID"
		exit 0
fi
