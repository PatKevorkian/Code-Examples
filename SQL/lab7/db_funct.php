<?php

//function to connect to database 
function db_connect() {
    $result = mysqli_connect('localhost', 'kevorkian', '6f8140qr', 'kevorkian');
    if (!$result) {
        throw new Exception('Could not connect to database!');
    } else {
        return $result;
    }
}

//functon to get posts from db 
function get_posts($limit = 0)
{
    //get five most recent posts

    $conn = db_connect();
    $result = $conn->query("select title, body, post_id, dateTime,username FROM `posts` order by `dateTime` desc limit ".$limit.",5");

    if (!$result)
    {
        return false;
    }

    //create an array of the posts
    $posts = array();
    for ($count = 1; $row = $result->fetch_row(); ++$count) {
        foreach($row as $col => $item)
            $posts[$count][$col] = $row[$col];
    }
    return $posts;
}

//function to get comments from db 
function get_comments($id)
{
//get comments

$conn = db_connect();
$result = $conn->query("select name, body from `comments` where post_id = {$id}");

if (!$result)
{
return false;
}

//array of comments created from the result 

$comments = array();
for ($count = 1; $row = $result->fetch_row(); ++$count) {
foreach($row as $col => $item)
$comments[$count][$col] = $row[$col];
}

return $comments;

}
?>