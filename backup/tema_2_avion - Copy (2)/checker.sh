!/bin/bash

#------------------------------------------------------------------------------
# 
#   CHECKER Tema 2 SDA-AB, 2020 - Arhipeleagul Yao-Zinci
#   
#   Author: Ruben & Smaranda
#
#------------------------------------------------------------------------------
#definire constante
# Exec name
EXEC_NAME=avion

# Teste Normale
# Explicatie: Checker-ul preia datele din fisierul date, compara ce este in rezultate
# cu ce este in out 
FILE_TEST_DATE="Date/date%d.in"
FILE_TEST_REF="Rezultate/rezultate%d.out"
FILE_TEST_OUT="out/out%d.out"
NUM_TESTS=14

# Format: "x=a,y=b,z=c..."
# x, y, z are test indexes
# Each test with an index less or equal to x gets a points.
# Each test with an index less or equal to y gets b points.
POINTS_TEST="1=2,2=3,4=5,7=15,8=20,9=6,10=4,14=10"

# Total score
SCORE_TESTS=0

# Delimitor
DELIM="-------------------------------------------------------------"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Points:
#
# TODO

points=0

 function run_test {
	#definire variabilele locale 
 	points=0
 	msg=""
  	color=$RED

  	  # Convert from Points string to array
  	p_text=`echo $5 | tr ',' ' '`
  	p_arr=($p_text)

  	for x in "${p_arr[@]}";
  	do
  	        tidx=`echo $x | cut -d'=' -f1`
  	        tpts=`echo $x | cut -d'=' -f2`
	
          	if (( $1 <= $tidx )); #daca sunt mai putine argumente iese din functie
          	then
  			points=$tpts
          	        break
          	fi
  	done

  	  # Okay, so this test will get $points if passed.
  	timeout 1 ./$EXEC_NAME $2 $3 > /dev/null 2>&1 | cat #ruleaza executabilul cu timeout 1 = 1 secunda
	
  	diff -Z -q $3 $4 > /dev/null 2>&1 #compar out-ul cu rezultatele
  	if [ $? -eq 0 ]; #daca cele 2 sunt egale
  	then
  		msg="PASSED"
  		color=$GREEN
  	else
  		msg="FAILED"
  		color=$RED
  		points=0
  	fi

  	printf "Test %2d ................................. ${color}%6s${NC} (+%2dpt)\n" $i $msg $points
  }
  #functie care ruleaza toate testele si apoi le aduna punctajele
  function run_tests {
  	for i in `seq 1 1 $1`
  	do
  		printf -v file_date $2 $i
  		printf -v file_out $3 $i
  		printf -v file_ref $4 $i
  		run_test $i $file_date $file_out $file_ref $5
		
  		SCORE_TESTS=$(($SCORE_TESTS+$points))
  	done
  }

  function run_normal_tests {
  	echo $DELIM
  	echo "[TESTE NORMALE]"
  	run_tests $NUM_TESTS $FILE_TEST_DATE $FILE_TEST_OUT $FILE_TEST_REF "$POINTS_TEST"

  	echo
  	printf "TOTAL ........................................... %3spt\n" $SCORE_TESTS 
  	echo
  }
  # arata punctajul total
  function show_total {
  	echo $DELIM
  	echo "[NOTA FINALA]"
	
  	echo
  	printf "NOTA FINALA ..................................... %3spt\n" $(($SCORE_TESTS))
  	echo	
  }

    # Prepare output directory
  rm -rf out/
  mkdir out

    # Build 
  make clean
  make

    # Run normal tests
  echo $DELIM
  echo "Executabil = '$EXEC_NAME'"

  run_normal_tests
  show_total
