SELECT name from people where id IN
(Select person_id FROM stars WHERE movie_id IN
(SELECT movie_id from stars WHERE person_id = (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958 ))) AND  name !='Kevin Bacon'