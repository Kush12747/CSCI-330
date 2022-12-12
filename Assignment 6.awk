BEGIN {
	#prints the top heading of the table
	print "\tWord Count"
	print "--------------------"
	FS=" ";
}

{
	#counts the frequency of the words and stores the value
	for (i = 1; i < NF; i++)
	{
		gsub(/[.,;:()]/,"") #implemented extra credit here and in line 13
		tolower($i)
		words[$i]++
	}
}

END {
	
	#loop through the words to get total count and check conditions that
	#match >= 3 characters and >= 5 letters onto the screen
	for (i in words) 
	{ 
		totalCount += words[i]
        if (words[i] >= 3 && length(i) >= 5)
			print "    ", i, "\t", words[i]
    }
    
    #prints bottom footer of the table
	print "----------------------"
	print "Number of words: ", totalCount
}
