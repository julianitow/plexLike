USE plexLike;

DROP TABLE IF EXISTS users;

CREATE TABLE IF NOT EXISTS users (
    id INT(3) unsigned NOT NULL AUTO_INCREMENT,
    username VARCHAR(100),
    password BINARY(20),
    PRIMARY KEY(id)
)