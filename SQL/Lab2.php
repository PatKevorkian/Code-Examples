<?php
//1. Write a very simple PHP script that sets one variable 
//   to a string value and another to a numeric value.
//   Have the page print out (using echo), both the variables in some sentence


$name = "Patrick";
$age= 20;

echo "Hello ". $name." ! Are you really ". $age. " years old!"; 
echo "<br />";
echo "<br />";
//current date 

$today = date("F j, Y, g:i a"); 
echo $today; 
echo "<br />";
echo "<br />";

//examples of these functions isset, empty(), var_dump 


$varSet = isset($name); 
echo "Results of isset: ". $varSet;
echo "<br />";
echo "<br />";


if (empty($name));
    {
        echo "The var is not empty";
        echo "<br />";
    }
echo "The var's value is ". $name.".";
echo "<br />";
echo "<br />";
 
echo "Results of var_dump: ";
echo var_dump($age);
echo "<br />";

//2. Use two for loops, one nested inside another to create a multiplication table
//   (USE AN HTML TABLE WITH <table> </table> FOR THIS


$rows=7; 
$cols=7;

echo "<br />";
echo "Multiplication table: "; 
echo "<br />";
echo "<table border=\"1\">";
for ($i=1; $i <= $rows; $i++)
{
echo "<tr>";
for ($j=1; $j <= $cols; $j++)
echo "<td>".$i*$j."<td / >";
echo "<tr>";
}
echo "</table>";

?>