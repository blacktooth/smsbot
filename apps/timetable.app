#!/bin/bash

JSON_encode ()
{
	JSON_string=`echo { \"sendto\": \"$1\", \"sendwhat\": \"$2\" }`
	echo $JSON_string
}

ttdata='/home/blacktooth/code/smsbot/apps/res/tt.dat'
MSG_INVALID="Invalid day"
today=`date '+%a'` 
req=`echo $SENTTEXT | cut -d ' ' -f 1`
if [[ $req == "" ]]; then
	line=`cat $ttdata | grep -i "$today"`
else
	line=`cat $ttdata | grep -i "$req"`
fi
if [[ $line == "" ]]; then
	JSON_encode "$SENTFROM" "$MSG_INVALID"
	exit 0
fi
sms=`eval echo -n $line`
JSON_encode "$SENTFROM" "$sms"
exit 0
