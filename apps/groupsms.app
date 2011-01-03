#!/usr/bin/python
import os, json
"""
	pblist has all the available lists.
"""
listfile = file("/home/blacktooth/code/smsbot/apps/res/pblist")
groups = listfile.readlines()
listfile.close()
"""
	Get the request info from the environment.	
"""
sentfrom = [os.environ.data["SENTFROM"]]
senttext = os.environ.data["SENTTEXT"]
"""
	All default responses
"""
MSG_NOGRP = "No such group!"
MSG_EMPTYGRP = "Group is empty!"
MSG_NOACCESS = "You dont belong to this group!"
MSG_FOOTER = "You can reply to this by MA b5 <message>"
"""
	Function to print compact JSON encoding of numbers and message.
"""
def print_JSON( numbers, message ):
	number_string = ""
	for number in numbers:
		number_string += ','+number
	data = [ { 'sendwhat' : message, 'sendto' : number_string.lstrip(",") } ] 
	JSON_string = json.dumps(data)
	print JSON_string.lstrip("[").rstrip("]")

def open_pbfile():
	pbfile = file("/home/blacktooth/code/smsbot/apps/res/"+pblist+".cl")
	contacts = pbfile.readlines()
	pbfile.close()
	return contacts
"""
	Get the nickname of the sender.
"""
def get_nick( number, pblist ):
	contacts = open_pbfile()
	nick = False
	for contact in contacts:
		number = contact.rstrip("\n").split("::")[2]
		if number == sentfrom[0]:
			nick = contact.split("::")[1]
	return nick		
"""
	
"""
def get_numbers( nick, pblist ):
	contacts = open_pbfile()
	numbers = []
	for contact in contacts:
		number = contact.rstrip("\n").split("::")[2]
		if not number == sentfrom[0]:
			numbers.append(number)
	return numbers	
"""
	Check if the group exists or not.
"""
pblist = senttext.partition(" ")[0].lower()
if not groups.count(pblist+"\n"):
	print_JSON( sentfrom, MSG_NOGRP )
	exit()

nick = get_nick ( sentfrom[0], pblist)
if not nick:
	print_JSON( sentfrom, MSG_NOACCESS )
	exit()
"""
	All ready to go. Message everyone in the group.
"""
print_JSON( get_numbers( nick, pblist ), nick+" says "+senttext.partition(" ")[2]+" --"+MSG_FOOTER )
