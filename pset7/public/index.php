<?php

    // configuration
    require("../includes/config.php"); 

    $rows = query("Select symbol, shares FROM portfolio WHERE id = ?", $_SESSION["id"]);    
    
    foreach ($rows as $row)
    {
        print("<tr>");
        print("<tr>{$row["symbol"]}</td>");
        print("<tr>{$row["shares"]}</td>");
        print("<tr>");
    }

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio"]);

?>
