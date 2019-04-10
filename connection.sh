if ping -c1 google.com &> /dev/null
then
	echo "net";
	sudo date -s "$(curl -s --head http://google.com | grep ^Date: | sed 's/Date: //g')"
else
	echo "nonet";
fi
