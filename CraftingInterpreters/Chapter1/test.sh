
FILE=./main
if [ -f $FILE ]; then
  echo "Testing...."
else  
  echo "main not compiled, run make"
fi

# Test One
$output="$(./main ADD Hello ADD World! PRINT)"
echo $output