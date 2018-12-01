<?php

// including db_funct file to have those functions 
require_once("db_funct.php");

//function that adds the user comment to the database 
function add_comment($post_id) 
{

    $valid_user = $_SESSION['valid_user'];

	//connect to db 
	
    $conn = db_connect();
	
    $query = "INSERT INTO `comments`(`name`, `body`, `post_id`) VALUES ('{$valid_user}', \"{$_POST['comment']}\", {$post_id})";
   

    // if insert failed throw exception 
	
    if (!$conn->query($query)) 
	{
        throw new Exception('Comment could not be inserted.');
    }

    return true;
}

//function that adds the users post to the db 
function add_post() 
{

$valid_user = $_SESSION['valid_user'];
$date = date('Y/m/d H:i:s');
$conn = db_connect();
$query = "INSERT INTO `posts`(`title`, `body`, `username`,`dateTime`) VALUES ('{$_POST['title']}',\"{$_POST['new_post']}\",'{$valid_user}','$date')";


if (!$conn->query($query)) 
{
throw new Exception('Post could not be added');
}

return true;
}


?>