#!/bin/bash
JSON_encode ()
{
	JSON_string=`echo { \"sendto\": \"$1\", \"sendwhat\": \"$2\" }`
	echo $JSON_string
}
descfile='/home/blacktooth/code/smsbot/apps/res/app_desc.txt'
message=`cat $descfile`
JSON_encode "$SENTFROM" "$message"
exit 0
