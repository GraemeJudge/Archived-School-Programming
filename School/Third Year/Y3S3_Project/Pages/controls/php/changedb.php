<?php


function update(string $tablename, string $wherefield, int $wherefieldValue, string $fieldname, int $newfieldvalue): void {
    $db = new PDO(
        'mysql:host=127.0.0.1;dbname=project6',     // Database name
        'root',                                 // username
        ''                                // Password
    );
    
    // Boilerplate - Return arrays with keys that are the field names in the database - Call the PDO method setAttribute()
    $db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);

    // Use transactions 
    $db->beginTransaction();        // Roll back point
    try {
        // You MUST sanitize the input here from the user to prevent an SQL injection
        // $tablename switch cases

        // Change ANY field in ANY table - requires DIRECTLY changing the query string (this cannot be done using prepared statements - it is not allowed)
        $query = "UPDATE $tablename SET $fieldname = $newfieldvalue WHERE $wherefield = $wherefieldValue";   // The DOUBLE QUOTES here are NECESSARY since we use single quotes for the strings !!!
        $statement = $db->prepare($query); 
        $statement->execute();
        
        // Return number of rows that were updated - If no rows were affected by the update statement then throw error
        $count = $statement->rowCount();

        if($count == 0) {
            throw new Exception('Error - Database unchanged !!!');
        }
        echo "<br/><br/>Success - Database updated<br/><br/>";
        $db->commit(); 
         
    } catch (Exception $e) {
        echo $e->getMessage();
        $db->rollBack(); 
    }
    
}
// Start program
update('elevator_requests', 'ID', 18, 'Cur_Floor', 4);       // Should succeed if nodeID = 1 does not have status = 30 (all values may be passed by a form)
echo '<br/><br/>';

// Show table 
$db = new PDO(
    'mysql:host=127.0.0.1;dbname=project6',     // Database name
    'root',                                 // username
    ''                                // Password
);

// Boilerplate - Return arrays with keys that are the field names in the database - Call the PDO method setAttribute()
$db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);

$query2 = 'SELECT * FROM elevator_requests'; 
$rows = $db->query($query2); 
foreach ($rows as $row) { 
    var_dump($row);
    echo '<br/><br/>';
}


?>
