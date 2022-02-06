#/bin/bash


echo "Preparing tuxedo config"

#
# cleanup
#
rm TLOG myspace 2>/dev/null

#
# cleanup ipcs
#
ipcs -m | grep user1 | awk '{print $2}' | xargs -i ipcrm -m {}
ipcs -s | grep user1 | awk '{print $2}' | xargs -i ipcrm -s {}


echo "\n\n" | (
tmloadcf -y -b30000 ubbconfig

# Create tlog:
echo crdl -z `pwd`/TLOG -b 2000 | tmadmin

# Q config:
# According to: https://github.com/PacktPublishing/Modernizing-Oracle-Tuxedo-Applications-with-Python/blob/main/Chapter11/run.sh
#  Thanks to Aivars K.
#
export QMCONFIG=/tuxapp/conf/myspace
echo "crdl $QMCONFIG 0 4000" | qmadmin 
echo "qspc MYSPACE 33211 2000 3 5 5 100 ERROR y 16" | qmadmin
echo -e "qopen MYSPACE\nqcr ERROR time none 0 0 100% 0% ''" | qmadmin 
echo -e "qopen MYSPACE\nqcr TLOG time none 3 5 100% 0% ''" | qmadmin 

)

