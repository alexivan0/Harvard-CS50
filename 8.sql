SELECT name FROM people JOIN stars JOIN movies ON stars.movie_id = movies.id AND stars.person_id = people.id WHERE title = "Toy Story";