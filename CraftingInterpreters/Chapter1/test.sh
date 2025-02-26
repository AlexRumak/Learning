
FILE=./challenge3
if [ -f $FILE ]; then
  echo "Testing...."
else  
  echo "challenge3 not compiled, run make"
fi

# Test One
$output="$(./challenge3 ADD Hello ADD World! PRINT)"
echo $output